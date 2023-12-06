/**
 * 业务请求数据包头
*/
#pragma once

#include <cinttypes>
// request数据包协议:
// 0: uint8_t, 请求类型
// 1-4: uint32_t, 请求Id
// 4: data

namespace TradeGateway
{

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
};


};

