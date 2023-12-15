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
    virtual ~TradeApiAdapter() = default;

    virtual int ReqLogin(const LoginReq& req, uint32_t gatewayReqId) = 0;
    virtual int ReqOrderInsert(const OrderInsertReq& req, uint32_t gatewayReqId) = 0;
    virtual int ReqOrderCancel(const OrderCancelReq& req, uint32_t gatewayReqId) = 0;
    virtual int ReqQryAsset(const QryAssetReq& req, uint32_t gatewayReqId) = 0;
    virtual int ReqQryPosition(const QryPositionReq& req, uint32_t gatewayReqId) = 0;
    virtual int ReqQryOrder(const QryOrderReq& req, uint32_t gatewayReqId) = 0;
    virtual int ReqQryTrade(const QryTradeReq& req, uint32_t gatewayReqId) = 0;

    static std::string GetColValue(const std::string& loginStr, const std::string& colName);

protected:
    TradeApiHandler handler_;
    std::string loginStr_;
    std::string apiName_;
};
typedef TradeApiAdapter* CreateTradeApiFunc(const std::string& loginStr);