// 对客户端fd的封装, 用于处理客户端请求
#pragma once

#include "../Reactor/EventHandler.h"
#include "../Packet/SocketPacket.h"
#include "TradeSession.h"   

#include <string>

using namespace TradeGateway;

class SocketSession : public EventHandler
{
public:
    static const size_t MAX_BUF = 65536 * 60;
public:
    SocketSession(const std::string& clientIP, uint16_t port, uint16_t clientFd);
    ~SocketSession() override;
    int OnEpollEvent(uint32_t events) override;

private:
    // request数据包进行解包， 解出request请求数据, 进行业务处理
    int ProcessRequestPacket(const char* requestPacketStart, uint32_t requestPacketLen);
    // response回报数据进行封包, 得到回报数据包，发送给客户端
    friend class ServiceMap;
    void ProcessResponseData(ResponseType type, const ErrorMessage& errorMessage, uint32_t reqId, char* responseDataStart, uint32_t responseDataLen);
private:
    std::string clientAddr_;

    char recvBuf_[MAX_BUF]{0};
    size_t recvStart_ = 0;
    size_t recvEnd_ = 0;
    
    char sendBuf_[MAX_BUF]{0};
    size_t sendEnd_ = 0;

    TradeSession tradeSession_;
    // std::string SocketSessionId_;
};