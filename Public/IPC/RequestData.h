/**
 * 请求数据协议类
*/
#pragma once

#include "../DataStructure/Constexpr.h"
#include "../DataStructure/Enum.h"
#include <string>

namespace TradeGateway
{

struct LoginReq
{
    char            loginString[MAX_LOGINSTRING_LEN];

    std::string DebugInfo()
    {
        return std::string(loginString) + ",";
    }
};

struct OrderInsertReq
{
    char            code[MAX_CODE_LEN];
    char            orderRef[MAX_ORDERREF_LEN];
    DirectionType   direction;
    OffsetType      offset;
    double          limitPrice;
    uint32_t        volume;

    std::string DebugInfo()
    {
        return std::string(code) + "," 
             + std::string(orderRef) + ","
             + std::to_string((int)direction) + ","
             + std::to_string((int)offset) + ","
             + std::to_string((int)limitPrice) + ","
             + std::to_string((int)volume) + ",";
    }
};

struct OrderCancelReq
{
    char            orderSysID[MAX_ORDERSYSID_LEN];
    char            orderRef[MAX_ORDERREF_LEN];
    ExchangeType    exchange;

    std::string DebugInfo()
    {
        return std::string(orderSysID) + "," 
             + std::string(orderRef) + ","
             + std::to_string((int)exchange) + ",";
    }
};

struct QryAssetReq
{

    std::string DebugInfo()
    {
        return "";
    }
};

struct QryPositionReq
{

    std::string DebugInfo()
    {
        return "";
    }
};

struct QryOrderReq
{

    std::string DebugInfo()
    {
        return "";
    }
};

struct QryTradeReq
{
    
    std::string DebugInfo()
    {
        return "";
    }
};

};

