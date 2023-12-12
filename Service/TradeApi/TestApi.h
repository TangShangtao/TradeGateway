#include "TradeApiAdapter.h"

class TestApi : public TradeApiAdapter
{
public:
    TestApi(const std::string& loginStr);
    virtual ~TestApi() override;
    virtual void ReqLogin(const LoginReq& req, uint32_t reqId) override;
    virtual void ReqOrderInsert(const OrderInsertReq& req, uint32_t reqId) override;
    virtual void ReqOrderCancel(const OrderCancelReq& req, uint32_t reqId) override;
    virtual void ReqQryAsset(const QryAssetReq& req, uint32_t reqId) override;
    virtual void ReqQryPosition(const QryPositionReq& req, uint32_t reqId) override;
    virtual void ReqQryOrder(const QryOrderReq& req, uint32_t reqId) override;
    virtual void ReqQryTrade(const QryTradeReq& req, uint32_t reqId) override;
};