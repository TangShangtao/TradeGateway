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
    TradeApiAdapter* LoadTradeApi(const std::string& loginStr);
    int ProcessLoginReq(const LoginReq& req, uint32_t sessionReqId);
    int ProcessOrderInsertReq(const OrderInsertReq& req, uint32_t gatewayReqId);
    int ProcessOrderCancelReq(const OrderCancelReq& req, uint32_t gatewayReqId);
    int ProcessQryAssetReq(const QryAssetReq& req, uint32_t gatewayReqId);
    int ProcessQryPositionReq(const QryPositionReq& req, uint32_t gatewayReqId);
    int ProcessQryOrderReq(const QryOrderReq& req, uint32_t gatewayReqId);
    int ProcessQryTradeReq(const QryTradeReq& req, uint32_t gatewayReqId);

private:
    TradeApiAdapter* tradeApi_;

};