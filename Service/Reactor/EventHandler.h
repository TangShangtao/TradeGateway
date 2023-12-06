// epoll事件回调抽象类, 声明关注的fd、关注的epoll事件和事件发生时的处理逻辑
#pragma once

#include "Reactor.h"
#include <cstdint>
#include <string>

class EventHandler
{
    
public:
    /// @brief epoll事件产生时, 触发该回调
    /// @param events epoll events
    /// @return 0: 正常; -1: 异常或使用结束, Reactor会delete这个EventHandler对象
    virtual int OnEpollEvent(uint32_t events) = 0;
    EventHandler() = default;
    virtual ~EventHandler() = 0;
    int GetFd() const;
    uint32_t GetEvents() const;
protected:
    int fd_;                        // 目标fd(子类在构造函数中指定)
    uint32_t events_;               // 订阅的epoll事件(子类在构造函数中指定)
    std::string name_;              // 名称
};