#include "SocketSession.h"
#include "Logger.h"
#include "../ServiceMap/ServiceMap.h"

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <memory>

SocketSession::SocketSession(const std::string& clientIP, uint16_t port, uint16_t clientFd)
{
    fd_ = clientFd;
    events_ = EPOLLERR | EPOLLHUP | EPOLLIN | EPOLLOUT | EPOLLET;
    clientAddr_ = clientIP + ":" + std::to_string(port);
    name_ = fmt::format("SocketSession clientAddr {}", clientAddr_);
    INFO("New socket session create");
    
}

SocketSession::~SocketSession()
{
    auto& map = ServiceMap::GetInstance();
    map.RemoveThisSession(this);
    INFO("socket session erase");
}

int SocketSession::OnEpollEvent(uint32_t events)
{
    if (events & (EPOLLERR | EPOLLHUP))
    {
        ERROR("error: clientAddr {} EPOLLERR | EPOLLHUP error", clientAddr_);
        return -1;
    }
    if (events & EPOLLIN)
    {
        // 采用边缘模式, 需要while true持续读取
        while (true)
        {
            // 当发送过来的数据大于fd缓存区, 需要持续的等待完整的数据
            auto len = read(fd_, recvBuf_ + recvEnd_, MAX_BUF - recvEnd_);
            if (len == -1)
            {
                // 当fd上所有数据都读完后, 返回
                if (errno == EAGAIN)
                {
                    return 0;
                }
                // read出现错误
                else
                {
                    ERROR("error: clientAddr {} read len == -1 error", clientAddr_);
                    return -1;
                }
            }
            // 客户端断开了连接
            if (len == 0)
            {
                INFO("clientAddr {} disconnected", clientAddr_);
                return -1;
            }
            recvEnd_ += len;
            // 正常接收消息到buf, 进行解包判断(TODO 包的拆分)
            int result = 0;
            // 这个do while用于处理一个read得出多个包的情况，进行拆分，若read得到不完整的包，则继续read
            do
            {
                SocketPacket packet;
                packet.SetSocketPacket(recvBuf_ + recvStart_, recvEnd_ - recvStart_);
                // socket数据包解出request数据包
                result = packet.Decode();
                // 1.包不合法, 断开连接
                if (result == -1)
                {
                    ERROR("error: clientAddr {} invalid SocketPacket", clientAddr_);
                    recvStart_ = recvEnd_;
                }
                // 2.包未读完, 继续读取
                else if (result == 0)
                {
                    INFO("continue read");
                    // std::cout << "continue read..." << std::endl;
                }
                // 3.解析出一个请求包
                else
                {
                    recvStart_ += result;
                    auto requestPacket = packet.GetRequestPacket();
                    int processResult = ProcessRequestPacket(requestPacket.first, requestPacket.second);
                    if (processResult != 0)
                    {
                        ERROR("error: clientAddr {} process requestPacket failed, result: {}", clientAddr_, processResult);
                        return -1;
                    }
                }
            } while (result > 0 && recvEnd_ - recvStart_ > 0);

            memcpy(recvBuf_, recvBuf_ + recvStart_, recvEnd_ - recvStart_);
            recvEnd_ -= recvStart_;
            recvStart_ = 0;
            // 从这里继续调用read读取
        }
    }
    if (events & EPOLLOUT)
    {
        int result = SendResponse();
        if (result != 0)
        {
            ERROR("error: SendResponse error");
            return result;
        }
        return 0;
    }
    else
    {
        ERROR("error: clientAddr {} error epoll event", clientAddr_);
        return -1;
    }
}

int SocketSession::ProcessRequestPacket(const char* requestPacketStart, uint32_t requestPacketLen)
{
    INFO("clientAddr {} Processing request packet", clientAddr_);
    
    RequestPacketHead head;
    memset(&head, 0, sizeof(RequestPacketHead));
    // 直接强转, 解析业务请求数据包头
    memcpy(&head, requestPacketStart, sizeof(RequestPacketHead));
    const char* requestDataStart = requestPacketStart + sizeof(RequestPacketHead);
    int result = 0;
    uint32_t gatewayReqId = 0;
    switch (head.requestType)
    {
        case RequestType::ReqLogin:
            LoginReq loginReq;
            memcpy(&loginReq, requestDataStart, sizeof(LoginReq));
            INFO("clientAddr {}, ReqLogin, DebugInfo: {}", clientAddr_, loginReq.DebugInfo());
            ServiceMap::GetInstance().AddNewSession(loginReq.loginString, this);
            gatewayReqId = ServiceMap::GetInstance().AddNewReq(head.requestId, this);

            result = tradeSession_.ProcessLoginReq(loginReq, gatewayReqId);
            if (result != 0)
            {
                ERROR("error: ProcessLoginReq failed, loginStr: {}", loginReq.loginString);
                return -1;
            }
            return 0;
        case RequestType::ReqOrderInsert:
            OrderInsertReq orderInsertReq;
            memcpy(&orderInsertReq, requestDataStart, sizeof(OrderInsertReq));
            INFO("clientAddr {}, ReqOrderInsert, info: {}", clientAddr_, orderInsertReq.DebugInfo());
            gatewayReqId = ServiceMap::GetInstance().AddNewReq(head.requestId, this);

            result = tradeSession_.ProcessOrderInsertReq(orderInsertReq, gatewayReqId);
            if (result != 0)
            {
                ERROR("error: ProcessOrderInsertReq failed, loginStr: {}", loginReq.loginString);
                return -1;
            }
            return 0;
        case RequestType::ReqOrderCancel:
            OrderCancelReq orderCancelReq;
            memcpy(&orderCancelReq, requestDataStart, sizeof(OrderCancelReq));
            INFO("clientAddr {}, ReqOrderCancel, info: {}", clientAddr_, orderCancelReq.DebugInfo());
            gatewayReqId = ServiceMap::GetInstance().AddNewReq(head.requestId, this);

            result = tradeSession_.ProcessOrderCancelReq(orderCancelReq, gatewayReqId);
            if (result != 0)
            {
                ERROR("error: ProcessOrderCancelReq failed, loginStr: {}", loginReq.loginString);
                return -1;
            }
            return 0;
        case RequestType::ReqQryAsset:
            QryAssetReq qryAssetReq;
            memcpy(&qryAssetReq, requestDataStart, sizeof(QryAssetReq));
            INFO("clientAddr {}, ReqQryAsset, info: {}", clientAddr_, qryAssetReq.DebugInfo());
            gatewayReqId = ServiceMap::GetInstance().AddNewReq(head.requestId, this);
            
            result = tradeSession_.ProcessQryAssetReq(qryAssetReq, gatewayReqId);
            if (result != 0)
            {
                ERROR("error: ProcessQryAssetReq failed, loginStr: {}", loginReq.loginString);
                return -1;
            }
            return 0;
        case RequestType::ReqQryPosition:
            QryPositionReq qryPositionReq;
            memcpy(&qryPositionReq, requestDataStart, sizeof(QryPositionReq));
            INFO("clientAddr {}, ReqQryPosition, info: {}", clientAddr_, qryPositionReq.DebugInfo());
            gatewayReqId = ServiceMap::GetInstance().AddNewReq(head.requestId, this);

            result = tradeSession_.ProcessQryPositionReq(qryPositionReq, gatewayReqId);
            if (result != 0)
            {
                ERROR("error: ProcessQryPositionReq failed, loginStr: {}", loginReq.loginString);
                return -1;
            }
            return 0;
        case RequestType::ReqQryOrder:
            QryOrderReq qryOrderReq;
            memcpy(&qryOrderReq, requestDataStart, sizeof(QryOrderReq));
            INFO("clientAddr {}, ReqQryOrder, info: {}", clientAddr_, qryOrderReq.DebugInfo());
            gatewayReqId = ServiceMap::GetInstance().AddNewReq(head.requestId, this);

            result = tradeSession_.ProcessQryOrderReq(qryOrderReq, gatewayReqId);
            if (result != 0)
            {
                ERROR("error: ProcessQryOrderReq failed, loginStr: {}", loginReq.loginString);
                return -1;
            }
            return 0;
        case RequestType::ReqQryTrade:
            QryTradeReq qryTradeReq;
            memcpy(&qryTradeReq, requestDataStart, sizeof(QryTradeReq));
            INFO("clientAddr {}, ReqQryTrade, info: {}", clientAddr_, qryTradeReq.DebugInfo());
            gatewayReqId = ServiceMap::GetInstance().AddNewReq(head.requestId, this);

            result = tradeSession_.ProcessQryTradeReq(qryTradeReq, gatewayReqId);
            if (result != 0)
            {
                ERROR("error: ProcessQryTradeReq failed, loginStr: {}", loginReq.loginString);
                return -1;
            }
            return 0;
        case RequestType::None:
            ERROR("error: clientAddr {}, requestType parse error", clientAddr_);
            return -1;
        default:
            ERROR("error: clientAddr {}, requestType parse error", clientAddr_);
            return -1;
    }
}

void SocketSession::ProcessResponseData(ResponseType type, const ErrorMessage& errorMessage, uint32_t reqId, char* responseDataStart, uint32_t responseDataLen)
{
    INFO("Processing response to clientAddr {}, ResponseType: {}", clientAddr_, type);
    // 构造业务回报数据包头
    ResponsePacketHead head;
    memset(&head, 0, sizeof(ResponsePacketHead));
    head.responseType = type;
    head.errorMessage = errorMessage;
    head.requestId = reqId;
    SocketPacket packet;
    packet.SetResponsePacket((char*)&head, responseDataStart, responseDataLen);
    auto packetLen = packet.Encode(sendBuf_ + sendEnd_, MAX_BUF - sendEnd_);
    sendEnd_ += packetLen;

    int result = SendResponse();
    if (result != 0)
    {
        ERROR("error: SocketSession SendResponse failed");
    }
    
}

int SocketSession::SendResponse()
{
    if (sendEnd_ == 0) return 0;
    int result = 0;
    size_t sendLen = 0;     // 已发送长度
    ssize_t len = 0;
    do
    {
        len = send(fd_, sendBuf_ + sendLen, sendEnd_ - sendLen, 0);
        if (len <= 0)
        {
            if (errno == EAGAIN) break;
            else
            {
                ERROR("error: clientAddr {} send len == -1", clientAddr_);
                result = -1;
                break;
            }
        }
        else
        {
            sendLen += len;
        }
    } while (sendLen < sendEnd_);
    // do while顺利完成, sendBuf全部发送
    if (sendLen == sendEnd_) sendEnd_ = 0;
    // send函数返回负数, 将sendBuf剩余字节拷贝至开头
    else if (sendLen < sendEnd_)
    {   
        memmove(sendBuf_, sendBuf_ + sendLen, sendEnd_ - sendLen);
        sendEnd_ -= sendLen;
        ERROR("error: copy remain sendBuf");
    }
    else ERROR("error: sendLen > sendEnd_");
    INFO("Send response to clientAddr {}", clientAddr_);
    return result;
}