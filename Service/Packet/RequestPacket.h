#pragma once
#include <cinttypes>
#include <string>

#include "Protocol.h"
// 对request数据字节序列进行封装, 用于解析、拷贝成协议数据类

using namespace TradeGateway;

class RequestPacket
{
public:
    RequestPacket(const char* origin, uint32_t len);
    void SetRequestPacket(const char* origin, uint32_t len);

    /// 对数据包进行解包, 解析、拷贝成协议数据类
    RequestPacketHead Decode();
public:
    // 解包后的数据
    const char* RequestDataStart;
private:
    // 从request数据字节序列解析出协议包头
    RequestPacketHead ParseRequestPacketHead();
private:
    // 请求数据字节序列
    const char* origin_;    // char [0x68, dataLen, data]
    ssize_t len_;
};