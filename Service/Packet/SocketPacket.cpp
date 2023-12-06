#include "SocketPacket.h"
#include <cstring>

SocketPacket::SocketPacket(const char* origin, ssize_t len) : origin_(origin), len_(len) {}

void SocketPacket::SetSocketPacket(const char* origin, ssize_t len)
{
    origin_ = origin;
    len_ = len;
}

ssize_t SocketPacket::Decode()
{
    // 包长度小于包头长度, 继续接收
    uint8_t headLen = sizeof(SocketPacketHead);
    if (len_ < headLen) return 0;
    // 解析包头
    auto head = ParseSocketPacketHead();
    // 第一字节不为该数字的包丢弃, 包格式不合法
    if (head.magicNum != SocketPacketHead::ProtoMagicNum) return -1;
    // 本次数据包中数据的长度大于原始数据字节序列长度, 继续接收
    if (head.dataLen > len_ - headLen) return 0;
    // 数据包完整合法, 拷贝解包后的数据
    RequestPacketStart = origin_ + headLen;
    RequestPacketLen = head.dataLen;
    
    return headLen + head.dataLen;

}

SocketPacketHead SocketPacket::ParseSocketPacketHead()
{
    uint8_t headLen = sizeof(SocketPacketHead);
    SocketPacketHead head{0};
    memcpy(&head, origin_, headLen);
    return head;
}