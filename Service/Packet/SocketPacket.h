#pragma once
#include <cinttypes>
#include <string>
#include <utility>
#include "Protocol.h"
// 对socket原始数据字节序列进行封装, 用于检测数据是否接收完毕

using namespace TradeGateway;

class SocketPacket
{
public:
    SocketPacket() = default;
    ~SocketPacket() = default;

    /// 对数据包进行解包, 解包出请求数据包
    ssize_t Decode(const char* socketPacketStart, ssize_t socketPacketLen);
public:
    // 解包后请求数据
    const char* RequestPacketStart;
    uint32_t RequestPacketLen;
    // socket接收\发送数据
    const char* SocketPacketStart;
    ssize_t SocketPacketLen;

private:
    // 从原始数据字节序列解析出协议包头
    SocketPacketHead ParseSocketPacketHead();

    // // 将回报数据加上包头
    // void AddSocketPacketHead();
};