#include "SocketPacket.h"
#include "Logger.h"

#include <cstring>

void SocketPacket::SetSocketPacket(const char* socketPacketStart, ssize_t socketPacketLen)
{
    socketPacketStart_ = socketPacketStart;
    socketPacketLen_ = socketPacketLen;
}

ssize_t SocketPacket::Decode()
{
    // 包长度小于包头长度, 继续接收

    if (socketPacketLen_ < sizeof(SocketPacketHead)) return 0;
    // 解析包头
    SocketPacketHead head;
    memset(&head, 0, sizeof(SocketPacketHead));

    memcpy(&head, socketPacketStart_, sizeof(SocketPacketHead));
    // 第一字节不为该数字的包丢弃, 包格式不合法
    if (head.magicNum != SocketPacketHead::ProtoMagicNum) return -1;
    // 本次数据包中数据的长度大于原始数据字节序列长度, 继续接收
    if (head.dataLen > socketPacketLen_ - sizeof(SocketPacketHead)) return 0;
    // 数据包完整合法, 拷贝解包后的数据
    requestPacketStart_ = socketPacketStart_ + sizeof(SocketPacketHead);
    requestPacketLen_ = head.dataLen;
    
    return sizeof(SocketPacketHead) + head.dataLen;

}

std::pair<const char*, uint32_t> SocketPacket::GetRequestPacket()
{
    return {socketPacketStart_, requestPacketLen_};
}

void SocketPacket::SetResponsePacket(const char* responseHeadStart, const char* responseDataStart, uint32_t responseDataLen)
{
    responseHeadStart_ = responseHeadStart;

    responseDataStart_ = responseDataStart;
    responseDataLen_ = responseDataLen;
}

ssize_t SocketPacket::Encode(char* socketPacketStart, size_t socketPacketLen)
{
    if (socketPacketLen <  responseDataLen_ + sizeof(ResponsePacketHead))
    {
        ERROR("socket packet encode error, send buf empty");
        return 0;
    }
    SocketPacketHead head;
    memset(&head, 0, sizeof(SocketPacketHead));
    head.magicNum = SocketPacketHead::ProtoMagicNum;
    head.dataLen = responseDataLen_ + sizeof(ResponsePacketHead);
    memcpy(socketPacketStart, &head, sizeof(SocketPacketHead));
    socketPacketStart += sizeof(SocketPacketHead);
    memcpy(socketPacketStart, responseHeadStart_, sizeof(ResponsePacketHead));
    socketPacketStart += sizeof(ResponsePacketHead);
    memcpy(socketPacketStart, responseDataStart_, responseDataLen_);
    return sizeof(SocketPacketHead) + head.dataLen;
}

