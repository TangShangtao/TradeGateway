/**
 * 业务请求数据包头
*/
#pragma once

#include <cinttypes>

enum class RequestType
{
    None = 0,
    Login = 1,
    OrderInsert = 2,
    OrderCancel = 3,
    QryAsset = 4,
    QryPosition = 5,
    QryOrder = 6,
    QryTrade = 7,
};

struct RequestPacketHead
{
    std::uint32_t requestId;
    RequestType   requestType;
};
