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
    ~TradeSession();
public:
    TradeApiAdapter* LoadLib(const std::string& loginStr);
    int ProcessLoginReq(const LoginReq& req, uint32_t reqId);
    int ProcessOrderInsertReq(const OrderInsertReq& req, uint32_t reqId);
    int ProcessOrderCancelReq(const OrderCancelReq& req, uint32_t reqId);
    int ProcessQryAssetReq(const QryAssetReq& req, uint32_t reqId);
    int ProcessQryPositionReq(const QryPositionReq& req, uint32_t reqId);
    int ProcessQryOrderReq(const QryOrderReq& req, uint32_t reqId);
    int ProcessQryTradeReq(const QryTradeReq& req, uint32_t reqId);

private:
    TradeApiAdapter* tradeApi_;

};