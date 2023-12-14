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
    // 对readBuf处的socket数据包进行解包, 解包出请求数据包
    // 返回值: -1: 包不合法, 0: 包未接收完整, len: 该socket数据包完整长度
    ssize_t Decode();
    // 对readBuf处的socket数据包进行解包, 解包出请求数据包
    // 返回值: 业务请求数据包指针起始、包长
    std::pair<const char*, uint32_t> GetRequestPacket();
<<<<<<< HEAD

    // 对回报数据包进行封包，封装出socket数据包, 拷贝至sendBuf处
    void SetResponsePacket(const char* responseHeadStart, const char* responseDataStart, uint32_t responseDataLen);
    // 对回报数据包进行封包，封装出socket数据包, 拷贝至sendBuf处
    // 返回值: 该socket数据包完整长度
=======
    //  对回报数据包进行封包，封装出socket数据包, 拷贝至sendBuf处
    void SetResponsePacket(const char* responseHeadStart, const char* responseDataStart, uint32_t responseDataLen);
>>>>>>> d23a801dd2219c996fa3c08a1a397f61399093de
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