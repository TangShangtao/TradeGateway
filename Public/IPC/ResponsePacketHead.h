/**
 * 业务回报数据包头
*/
#pragma once

#include <cinttypes>

enum class ResponseType
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

struct ResponsePacketHead
{
    std::uint32_t requestId;

    ResponseType   requestType;
};