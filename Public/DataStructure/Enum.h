#pragma once

#include <cinttypes>


namespace TradeGateway
{

enum class DirectionType : uint8_t
{
    None = UINT8_MAX,
    Buy = 1,
    Sell = 2,

};

enum class OffsetType : uint8_t
{
    None = UINT8_MAX,
    Open = 1,
    Close = 2,
    CloseToday = 3,
};

enum class ExchangeType : uint8_t
{
    None = UINT8_MAX,
    SHFE = 1,
    CZCE = 2,
    DCE = 3,
    CFFEX = 4,
    SSE = 5,
    SZSE = 6,
};

enum class PositionDirectionType
{
    None = UINT8_MAX,
    Long = 1,
    Short = 2,
};

enum class PositionDateType
{
    None = UINT8_MAX,
    Today = 1,
    History = 2,
};

enum class OrderStatusType
{
    None = UINT8_MAX,
    AllTraded = 1,
    Queueing = 2,
    Rejected = 3,
    Cancelled = 4,
    PartialTraded = 5,
    Inited = 6,
};

};

