#include "TradeSession.h"
#include "../ServiceMap/ServiceMap.h"
#include "Logger.h"
#include "DLLHelper.h"
#include <cstring>
#include <string>

// #include "../TradeApi/TestApi.h"

TradeSession::~TradeSession()
{
    // ServiceMap::GetInstance().RemoveTradeApi()
}

TradeApiAdapter* TradeSession::LoadTradeApi(const std::string& loginStr)
{
    // TODO 使用LoadLib库动态加载
    std::string apiName = TradeApiAdapter::GetColValue(loginStr, "api");
    std::string soPath = "../lib/lib" + apiName + ".so";
    auto handle = DLLHelper::LoadLib(soPath);
    if (!handle)
    {
        ERROR("error: load dll {} failed, handle is nullptr", soPath);
        return nullptr;
    }
    std::string creatorName = "CreateTradeApi";
    auto createFunc = (CreateTradeApiFunc*)DLLHelper::LoadSymbol(handle, creatorName.c_str());
    if (!createFunc)
    {
        ERROR("error: load symbol {} failed, handle is nullptr", creatorName);
        DLLHelper::FreeLib(handle);
        return nullptr;
    }
    // DLLHelper::FreeLib(handle);
    return createFunc(loginStr);
    // return new TestApi(loginStr);
}

int TradeSession::ProcessLoginReq(const LoginReq& req, uint32_t gatewayReqId)
{
    INFO("receive loginReq, DebugInfo: {}", req.loginString);
    std::string loginStr = req.loginString;
    tradeApi_ = ServiceMap::GetInstance().GetTradeApi(loginStr);
    if (tradeApi_ == nullptr)
    {
        INFO("new loginStr received, load new tradeApi");
        tradeApi_ = LoadTradeApi(loginStr);
    }
    if (tradeApi_ == nullptr)
    {
        ERROR("error: load new tradeApi failed, loginStr: {}", req.loginString);
        return -1;
    }
    else 
    {
        ServiceMap::GetInstance().AddTradeApi(loginStr, tradeApi_);
        int result = tradeApi_->ReqLogin(req, gatewayReqId);
        if (result != 0)
        {
            ERROR("error: ReqLogin failed, result: {}", result);
        }
        return result;
    }


}
int TradeSession::ProcessOrderInsertReq(const OrderInsertReq& req, uint32_t gatewayReqId)
{
    return 0;
}
int TradeSession::ProcessOrderCancelReq(const OrderCancelReq& req, uint32_t gatewayReqId)
{
    return 0;  
}
int TradeSession::ProcessQryAssetReq(const QryAssetReq& req, uint32_t gatewayReqId)
{
    return 0;
}
int TradeSession::ProcessQryPositionReq(const QryPositionReq& req, uint32_t gatewayReqId)
{
    return 0;
}
int TradeSession::ProcessQryOrderReq(const QryOrderReq& req, uint32_t gatewayReqId)
{
    return 0;
}
int TradeSession::ProcessQryTradeReq(const QryTradeReq& req, uint32_t gatewayReqId)
{
    return 0;
}


