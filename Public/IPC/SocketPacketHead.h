/**
 * 网络通信数据包头
*/
#pragma once

#include <cinttypes>

struct SocketPacketHead
{
    std::uint8_t magicNum;
    std::uint32_t dataLen;  // 本次数据包中数据的长度
    
    static constexpr std::uint8_t ProtoMagicNum = 0x68;  // 协议魔术数字, 第一字节不为该数字的包丢弃
    
};



