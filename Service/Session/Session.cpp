#include "Session.h"
#include "Logger.h"

#include <iostream>
// #include <sys/socket.h>
#include <unistd.h>
#include <cstring>
Session::Session(const std::string& clientIP, uint16_t port, uint16_t clientFd)
{
    fd_ = clientFd;
    events_ = EPOLLERR | EPOLLHUP | EPOLLIN | EPOLLOUT;
    clientAddr_ = clientIP + ":" + std::to_string(port);
    name_ = fmt::format("Session clientAddr {}", clientAddr_);
}

Session::~Session() = default;

int Session::OnEpollEvent(uint32_t events)
{
    if (events & (EPOLLERR | EPOLLHUP))
    {
        ERROR("clientAddr {} EPOLLERR | EPOLLHUP error", clientAddr_);
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
                    ERROR("clientAddr {} read len == -1 error", clientAddr_);
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
                auto socketPacket = SocketPacket(recvBuf_ + recvStart_, recvEnd_ - recvStart_);
                result = socketPacket.Decode();
                // 1.包不合法, 断开连接
                if (result == -1)
                {
                    ERROR("clientAddr {} invalid SocketPacket error", clientAddr_);
                    recvStart_ = recvEnd_;
                }
                // 2.包未读完, 继续读取
                else if (result == 0)
                {
                    // std::cout << "continue read..." << std::endl;
                }
                // 3.解析出一个包
                else
                {
                    recvStart_ += result;
                    ProcessSocketPacket(socketPacket);
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
        return 0;
    }
    else
    {
        ERROR("clientAddr {} error epoll event", clientAddr_);
        return -1;
    }
}

void Session::ProcessSocketPacket(const SocketPacket &socketPacket)
{
    INFO("clientAddr {} Processing... {}", clientAddr_, socketPacket.content_);
}
