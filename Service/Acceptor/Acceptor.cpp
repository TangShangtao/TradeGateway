#include "Acceptor.h"
#include "Session.h"
#include "Logger.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
Acceptor::Acceptor()
{
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ == -1)
    {
        ERROR("Acceptor socket fd error");
    }
    events_ = EPOLLIN | EPOLLET;
    name_ = "Acceptor";
}

Acceptor::~Acceptor() = default;

void Acceptor::Listen(uint16_t port)
{
    // 绑定
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port); // 端口
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 所有IP
    // 设置端口复用
    int opt = 1;
    int ret = 0;
    ret = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (ret == -1)
    {
        ERROR("Acceptor setsockopt error");
        exit(-1);
    }
    // 绑定端口
    ret = bind(fd_, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret == -1)
    {
        ERROR("Acceptor bind error");
        exit(-1);
    }
    // 监听
    ret = listen(fd_, 64);
    if (ret == -1)
    {
        ERROR("Acceptor listen error");
        exit(-1);
    }
    // 添加至reactor
    Reactor::GetInstance().AddHandler(this);
}

int Acceptor::OnEpollEvent(uint32_t events)
{
    if (events & EPOLLIN)
    {
        // 采用边缘模式, 需要while true持续读取
        while (true)
        {
            struct sockaddr_in clientAddr = {0};
            socklen_t addrLen = sizeof(in_addr);
            int clientFd = accept(fd_, (struct sockaddr*)&clientAddr, &addrLen);
            if (clientFd == -1)
            {
                if (errno == EAGAIN) return 0;    // 当fd上所有connect请求都读完后, 返回
                else
                {
                    ERROR("Acceptor accept error");
                    return -1;
                }
            }
            ERROR("Acceptor new client connection");
            // 将clientFd封装为Session, 放入Reactor, 在Reactor处delete
            auto session = new Session(inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), clientFd);
            Reactor::GetInstance().AddHandler(session);
        }

    }
    else
    {
        std::cout << "acceptor error epoll event" << std::endl;
        return -1;
    }

}

