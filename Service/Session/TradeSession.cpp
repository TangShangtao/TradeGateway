#include "TradeSession.h"
#include "../ServiceMap/ServiceMap.h"
#include "Logger.h"
#include <cstring>
#include <string>
#include "../TradeApi/TestApi.h"

TradeSession::~TradeSession()
{
    // ServiceMap::GetInstance().RemoveTradeApi()
}

TradeApiAdapter* TradeSession::LoadLib(const std::string& loginStr)
{
    // TODO 使用LoadLib库动态加载
    return new TestApi(loginStr);
}

int TradeSession::ProcessLoginReq(const LoginReq& req, uint32_t reqId)
{
    INFO("receive loginReq, DebugInfo: {}", req.loginString);
    std::string loginStr = req.loginString;
    tradeApi_ = ServiceMap::GetInstance().GetTradeApi(loginStr);
    if (tradeApi_ == nullptr)
    {
        INFO("new loginStr received, load new tradeApi");
        tradeApi_ = LoadLib(loginStr);
        ServiceMap::GetInstance().AddTradeApi(loginStr, tradeApi_);
    }
    if (tradeApi_ == nullptr)
    {
        ERROR("error: load new tradeApi failed, loginStr: {}", req.loginString);
        return -1;
    }

    int result = tradeApi_->ReqLogin(req, reqId);
    if (result != 0)
    {
        ERROR("error: ReqLogin failed, result: {}", result);
    }
    return result;
}
int TradeSession::ProcessOrderInsertReq(const OrderInsertReq& req, uint32_t reqId)
{
    return 0;
}
int TradeSession::ProcessOrderCancelReq(const OrderCancelReq& req, uint32_t reqId)
{
    return 0;  
}
int TradeSession::ProcessQryAssetReq(const QryAssetReq& req, uint32_t reqId)
{
    return 0;
}
int TradeSession::ProcessQryPositionReq(const QryPositionReq& req, uint32_t reqId)
{
    return 0;
}
int TradeSession::ProcessQryOrderReq(const QryOrderReq& req, uint32_t reqId)
{
    return 0;
}
int TradeSession::ProcessQryTradeReq(const QryTradeReq& req, uint32_t reqId)
{
    return 0;
}


