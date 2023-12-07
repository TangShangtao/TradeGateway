#pragma once

#include "Constexpr.h"
#include "Enum.h"

namespace TradeGateway
{

struct OrderData
{
    char            code[MAX_CODE_LEN];
    char            orderRef[MAX_ORDERREF_LEN];
    DirectionType   direction;
    OffsetType      offset;
    double          limitPrice;
    uint32_t        volume;
    ExchangeType    exchange;
    char            tradingDay[MAX_TRADINGDAY_LEN];
    char            orderSysID[MAX_ORDERSYSID_LEN];
    OrderStatusType orderStatus;
    uint32_t        volumeTraded;
    char            insertTime[MAX_TIME_LEN];
    char            updateTime[MAX_TIME_LEN];
    char            cancelTime[MAX_TIME_LEN];
};

struct TradeData
{
    char            code[MAX_CODE_LEN];
    char            orderRef[MAX_ORDERREF_LEN];
    ExchangeType    exchange;
    char            tradeID[MAX_TRADEID_LEN];
    DirectionType   direction;
    OffsetType      offset;
    char            orderSysID[MAX_ORDERSYSID_LEN];
    double          tradePrice;
    uint32_t        tradeVolume;
    char            tradingDay[MAX_TRADINGDAY_LEN];
};

struct AssetData
{
    double          currMargin;
    double          balance;
    double          available;
    double          preBalance;
    double          deposit;
    double          withdraw;
    double          frozenMargin;
    double          frozenCommission;
    double          commission;
    double          closeProfit;
    double          positionProfit;
    double          withdrawQuota;
    double          frozenCash;
};

struct PositionData
{
    char                code[MAX_CODE_LEN];
    PositionDirectionType positionDirection;
    PositionDateType    positionDate;
    uint32_t            volume;
    ExchangeType        exchange;
};

};


