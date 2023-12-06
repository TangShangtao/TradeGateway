#include "RequestPacket.h"
#include <cstring>

RequestPacket::RequestPacket(const char* origin, uint32_t len) : origin_(origin), len_(len) {}

void RequestPacket::SetRequestPacket(const char* origin, uint32_t len)
{
    origin_ = origin;
    len_ = len;
}

RequestPacketHead RequestPacket::Decode()
{
    // 解析包头
    auto head = ParseRequestPacketHead();
    uint8_t headLen = sizeof(RequestPacketHead);
    RequestDataStart = origin_ + headLen;
    
    return head;
}

RequestPacketHead RequestPacket::ParseRequestPacketHead()
{
    uint8_t headLen = sizeof(RequestPacketHead);
    RequestPacketHead head;
    memset(&head, 0, sizeof(RequestPacketHead));
    memcpy(&head, origin_, headLen);
    return head;
}