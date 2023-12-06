// 对客户端fd的封装, 用于处理客户端请求
#pragma once

#include "../Reactor/EventHandler.h"
#include "../Packet/SocketPacket.h"
#include "../Packet/RequestPacket.h"
#include <string>


class SocketSession : public EventHandler
{
public:
    static const size_t MAX_BUF = 65536 * 60;
public:
    SocketSession(const std::string& clientIP, uint16_t port, uint16_t clientFd);
    ~SocketSession() override;
    int OnEpollEvent(uint32_t events) override;
private:
    void ProcessSocketPacket(const SocketPacket& SocketPacket);
private:
    std::string clientAddr_;

    char recvBuf_[MAX_BUF]{0};
    size_t recvStart_ = 0;
    size_t recvEnd_ = 0;
    char sendBuf_[MAX_BUF]{0};
    // std::string SocketSessionId_;
};