// 对epoll的封装, 用于管理fd, 分发事件触发回调
#pragma once
#include "EventHandler.h"
#include <vector>
#include <sys/epoll.h>
class EventHandler;
class Reactor
{
public:
    static const size_t MAX_EVENT = 1024;
public:

    static Reactor& GetInstance()
    {   
        static Reactor reactor;
        return reactor;
    }
    Reactor(const Reactor&) = delete;
    Reactor& operator=(const Reactor&) = delete;
    Reactor();
    ~Reactor();

    void AddHandler(EventHandler* handler);

    [[noreturn]] void Run(bool isBusyWait=false);

private:
    void MakeSocketNonBlocking(int fd);   // ret: 0 正常, -1 异常

private:
    int epollFd_;
    std::vector<EventHandler*> handlers_{MAX_EVENT}; // fd -> EventHandler
};