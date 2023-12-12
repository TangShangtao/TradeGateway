// 对各个交易柜台Api的封装
#pragma once

#include "TradeApiHandler.h"
#include "Protocol.h"
#include <cinttypes>
#include <string>
using namespace TradeGateway;

class TradeApiAdapter
{
public:
    explicit TradeApiAdapter(const std::string& loginStr);
    virtual ~TradeApiAdapter() = 0;

    virtual void ReqLogin(const LoginReq& req, uint32_t reqId) = 0;
    virtual void ReqOrderInsert(const OrderInsertReq& req, uint32_t reqId) = 0;
    virtual void ReqOrderCancel(const OrderCancelReq& req, uint32_t reqId) = 0;
    virtual void ReqQryAsset(const QryAssetReq& req, uint32_t reqId) = 0;
    virtual void ReqQryPosition(const QryPositionReq& req, uint32_t reqId) = 0;
    virtual void ReqQryOrder(const QryOrderReq& req, uint32_t reqId) = 0;
    virtual void ReqQryTrade(const QryTradeReq& req, uint32_t reqId) = 0;

protected:
    TradeApiHandler handler_;
    std::string loginStr_;
    std::string apiName_;
};