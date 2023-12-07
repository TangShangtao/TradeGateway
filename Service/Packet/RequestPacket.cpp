#include "RequestPacket.h"
#include <cstring>

RequestPacketHead RequestPacket::Decode(const char* requestPacketStart, uint32_t requestPacketLen)
{
    RequestPacketStart = requestPacketStart;
    RequestPacketLen = requestPacketLen;
    // 解析包头
    auto head = ParseRequestPacketHead();
    uint8_t headLen = sizeof(RequestPacketHead);
    RequestDataStart = RequestPacketStart + headLen;
    
    return head;
}

RequestPacketHead RequestPacket::ParseRequestPacketHead()
{
    uint8_t headLen = sizeof(RequestPacketHead);
    RequestPacketHead head;
    memset(&head, 0, sizeof(RequestPacketHead));
    memcpy(&head, RequestPacketStart, headLen);
    return head;
}