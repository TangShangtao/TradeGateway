
#pragma once

#include <cinttypes>
#include <string>
#include "../DataStructure/Constexpr.h"


namespace TradeGateway
{
/**
 * 网络通信数据包头
*/
struct SocketPacketHead
{
    std::uint8_t magicNum;                              // 1字节
    std::uint32_t dataLen;  // 本次数据包中数据的长度       // 4字节
    
    static constexpr std::uint8_t ProtoMagicNum = 0x68;  // 协议魔术数字, 第一字节不为该数字的包丢弃
    
};
/**
 * 业务请求数据包头
*/
enum class RequestType : uint8_t
{
    None = UINT8_MAX,
    ReqLogin = 1,
    ReqOrderInsert = 2,
    ReqOrderCancel = 3,
    ReqQryAsset = 4,
    ReqQryPosition = 5,
    ReqQryOrder = 6,
    ReqQryTrade = 7,
};

struct RequestPacketHead
{
    RequestType   requestType;
    uint32_t requestId;
    std::string DebugInfo() const
    {
        return std::to_string((uint8_t)requestType) + ","
             + std::to_string(requestId);
    }
};

/**
 * 业务回报数据包头
*/
enum class ResponseType : uint8_t
{
    None = 0,               
    RspLogin = 1,               //
    RspOrderInsert = 2,         //  
    RspOrderCancel = 3,         //
    RspQryAsset = 4,            //
    RspQryPosition = 5,         //
    RspQryOrder = 6,            //
    RspQryTrade = 7,            //

    RtnOrder = 8,               //
    RtnTrade = 9,               //

};

struct ErrorMessage
{
    uint8_t errorID;
    char message[MAX_ERRORMESSAGE_LEN];
    std::string DebugInfo() const
    {
        return std::to_string(errorID) + ","
             + std::string(message);
    }
};

struct ResponsePacketHead
{
    ResponseType   responseType;
    ErrorMessage errorMessage;
    uint32_t requestId;                 // 推送成交、订单状态回报时, requestId为0
    std::string DebugInfo() const
    {
        return std::to_string((uint8_t)responseType) + ","
             + errorMessage.DebugInfo() + ","
             + std::to_string(requestId);
    }
};

};
