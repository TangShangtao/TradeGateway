#include "Reactor.h"
#include "Logger.h"

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
Reactor::Reactor()
{
    epollFd_ = epoll_create(MAX_EVENT);
}

Reactor::~Reactor()
{
    close(epollFd_);
}

void Reactor::MakeSocketNonBlocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);
}

void Reactor::AddHandler(EventHandler* handler)
{
    int fd = handler->GetFd();
    MakeSocketNonBlocking(fd);
    
    handlers_[fd] = handler;
    struct epoll_event epollEvent{};
    epollEvent.data.fd = fd;
    epollEvent.events = handler->GetEvents();
    epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &epollEvent);
}

void Reactor::Run(bool isBusyWait)
{
    struct epoll_event epollEvents[MAX_EVENT];
    while (true)
    {
        int eventCount = epoll_wait(epollFd_, epollEvents, MAX_EVENT, isBusyWait ? 0 : -1);
        for (int i = 0; i < eventCount; i++)
        {
            struct epoll_event& epollEvent = epollEvents[i];
            int fd = epollEvent.data.fd;
            EventHandler* handler = handlers_[fd];
            // 发生handler订阅的事件时, 触发其回调
            if (epollEvent.events & handler->GetEvents())
            {
                int ret = handler->OnEpollEvent(epollEvent.events);
                if (ret == -1) 
                {
                    INFO("delete handler");
                    delete handler;
                }
            }

        }
    }
}
