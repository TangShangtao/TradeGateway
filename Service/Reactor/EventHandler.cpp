#include "EventHandler.h"
#include <unistd.h>

EventHandler::~EventHandler()
{
    close(fd_);
}

int EventHandler::GetFd() const
{
    return fd_;
}

uint32_t EventHandler::GetEvents() const
{
    return events_;
}
