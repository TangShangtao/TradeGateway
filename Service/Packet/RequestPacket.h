#pragma once
#include <cinttypes>
#include <string>

#include "Protocol.h"
// 对request数据字节序列进行封装, 用于解析、拷贝成协议数据类

using namespace TradeGateway;

class RequestPacket
{
public:

    RequestPacket() = default;
    ~RequestPacket() = default;

    /// 对数据包进行解包, 解析、拷贝成协议数据类
    RequestPacketHead Decode(const char* requestPacketStart, uint32_t requestPacketLen);
public:
    // 解包后的数据
    const char* RequestDataStart;
    // 请求数据字节序列
    const char* RequestPacketStart;
    uint32_t RequestPacketLen;
private:
    // 从request数据字节序列解析出协议包头
    RequestPacketHead ParseRequestPacketHead();
};