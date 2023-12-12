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

    // 对readBuf处的socket数据包进行解包, 解包出请求数据包
    void SetSocketPacket(const char* socketPacketStart, ssize_t socketPacketLen);
    ssize_t Decode();
    std::pair<const char*, uint32_t> GetRequestPacket();
    //  对回报数据包进行封包，封装出socket数据包, 拷贝至sendBuf处
    void SetResponsePacket(const char* responseHeadStart, const char* responseDataStart, uint32_t responseDataLen);
    ssize_t Encode(char* socketPacketStart, size_t socketPacketLen);

private:
    // 解包, 请求数据包
    const char* requestPacketStart_;
    uint32_t requestPacketLen_;

    // 封包, 回报数据包
    const char* responseHeadStart_;
    const char* responseDataStart_;
    uint32_t responseDataLen_;

    // socket接收\发送数据
    const char* socketPacketStart_;
    ssize_t socketPacketLen_;
};