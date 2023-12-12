#pragma once

#include "Protocol.h"
// #include "SocketSession.h"
#include "../TradeApi/TradeApiAdapter.h"
#include <unordered_map>
#include <string>
#include <memory>

using namespace TradeGateway;

class TradeSession
{
public:
    TradeSession() = default;
    ~TradeSession() = default;
public:
    void ProcessLoginReq(const LoginReq& req, uint32_t reqId);
    void ProcessOrderInsertReq(const OrderInsertReq& req, uint32_t reqId);
    void ProcessOrderCancelReq(const OrderCancelReq& req, uint32_t reqId);
    void ProcessQryAssetReq(const QryAssetReq& req, uint32_t reqId);
    void ProcessQryPositionReq(const QryPositionReq& req, uint32_t reqId);
    void ProcessQryOrderReq(const QryOrderReq& req, uint32_t reqId);
    void ProcessQryTradeReq(const QryTradeReq& req, uint32_t reqId);

private:
    TradeApiAdapter* tradeApi_;

};