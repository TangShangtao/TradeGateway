#pragma once
#include "TradeApiAdapter.h"

class TestApi : public TradeApiAdapter
{
public:
    TestApi(const std::string& loginStr);
    virtual ~TestApi() override;
    virtual int ReqLogin(const LoginReq& req, uint32_t reqId) override;
    virtual int ReqOrderInsert(const OrderInsertReq& req, uint32_t reqId) override;
    virtual int ReqOrderCancel(const OrderCancelReq& req, uint32_t reqId) override;
    virtual int ReqQryAsset(const QryAssetReq& req, uint32_t reqId) override;
    virtual int ReqQryPosition(const QryPositionReq& req, uint32_t reqId) override;
    virtual int ReqQryOrder(const QryOrderReq& req, uint32_t reqId) override;
    virtual int ReqQryTrade(const QryTradeReq& req, uint32_t reqId) override;
};

extern "C" TradeApiAdapter* CreateTradeApi(const std::string& loginStr)
{
    return new TestApi(loginStr);
}