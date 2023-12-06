#pragma once
#include <cinttypes>
#include <string>
#include <utility>

#include "Protocol.h"
// 对原始数据字节序列进行封装, 用于检测数据是否接收完毕
// 数据包协议:
// 0: 0x68, magicNum
// 1-4: uint32_t, data长度
// 4: data
class SocketPacket
{
public:
    ///
    /// \param start 数据包开始指针
    /// \param size 数据包大小
    SocketPacket(const char* origin, ssize_t len);
    ///
    /// \param start 数据包开始指针
    /// \param size 数据包大小
    void SetSocketPacket(const char* origin, ssize_t len);
    /// 对数据包进行解包, 若包合法, 则拷贝
    /// \return -1: 包格式不合法, 丢弃; 0: 包未接收完; len: 包合法, 包长len(包头长+数据长)
    ssize_t Decode();
private:
    // 从原始数据字节序列解析出协议包头
    SocketPacketHead ParseSocketPacketHead();

private:
    // 原始数据字节序列
    const char* origin_;    // char [0x68, dataLen, data]
    ssize_t len_;
public:
    // 解包后数据
    std::string content_;

};