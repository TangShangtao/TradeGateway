#include "SocketPacket.h"
#include <cstring>


ssize_t SocketPacket::Decode(const char* socketPacketStart, ssize_t socketPacketLen)
{
    // 包长度小于包头长度, 继续接收
    uint8_t headLen = sizeof(SocketPacketHead);
    SocketPacketStart = socketPacketStart;
    SocketPacketLen = socketPacketLen;

    if (SocketPacketLen < headLen) return 0;
    // 解析包头
    auto head = ParseSocketPacketHead();
    // 第一字节不为该数字的包丢弃, 包格式不合法
    if (head.magicNum != SocketPacketHead::ProtoMagicNum) return -1;
    // 本次数据包中数据的长度大于原始数据字节序列长度, 继续接收
    if (head.dataLen > SocketPacketLen - headLen) return 0;
    // 数据包完整合法, 拷贝解包后的数据
    RequestPacketStart = SocketPacketStart + headLen;
    RequestPacketLen = head.dataLen;
    
    return headLen + head.dataLen;

}


SocketPacketHead SocketPacket::ParseSocketPacketHead()
{
    uint8_t headLen = sizeof(SocketPacketHead);
    SocketPacketHead head{0};
    memcpy(&head, SocketPacketStart, headLen);
    return head;
}