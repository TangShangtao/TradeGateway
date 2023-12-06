#pragma once
#include <cinttypes>
#include <string>

#include "Protocol.h"
// 对socket原始数据字节序列进行封装, 用于检测数据是否接收完毕

using namespace TradeGateway;

class SocketPacket
{
public:

    SocketPacket(const char* origin, ssize_t len);
    void SetSocketPacket(const char* origin, ssize_t len);

    /// 对数据包进行解包, 解包出请求数据包
    /// \return -1: 包格式不合法, 丢弃; 0: 包未接收完; len: 包合法, 包长len(包头长+数据长)
    ssize_t Decode();
public:
    // 解包后数据
    const char* RequestPacketStart;
    uint32_t RequestPacketLen;

private:
    // 从原始数据字节序列解析出协议包头
    SocketPacketHead ParseSocketPacketHead();

private:
    // 原始数据字节序列
    const char* origin_;    // char [0x68, dataLen, data]
    ssize_t len_;

    std::string content_;

};