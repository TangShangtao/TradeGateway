/**
 * 请求数据协议类
*/
#pragma once

#include "../DataStructure/Constexpr.h"
#include "../DataStructure/Enum.h"

namespace TradeGateway
{

struct LoginReq
{
    char loginString[MAX_LOGINSTRING_LEN];
};

struct OrderInsertReq
{
    char code[MAX_CODE_LEN];
    char orderRef[MAX_ORDERREF_LEN];
    DirectionType direction;
    OffsetType offset;
    double limitPrice;
    uint32_t volume;
};

struct OrderCancelReq
{
    char orderSysID[MAX_ORDERSYSID_LEN];
    char orderRef[MAX_ORDERREF_LEN];
    ExchangeType exchange;
};

struct QryAssetReq
{
    
};

struct QryPositionReq
{

};

struct QryOrderReq
{

};

struct QryTradeReq
{

};

};

