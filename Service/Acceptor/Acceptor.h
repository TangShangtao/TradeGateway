#pragma once

#include "../Reactor/EventHandler.h"
#include <cstdint> 
class Acceptor : public EventHandler
{
public:
    Acceptor();
    virtual ~Acceptor() override;
    virtual int OnEpollEvent(uint32_t events) override;
    
    void Listen(uint16_t port);
    
    
};