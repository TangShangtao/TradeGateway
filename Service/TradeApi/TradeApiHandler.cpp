#include "TradeApiHandler.h"
#include "../ServiceMap/ServiceMap.h"

TradeApiHandler::TradeApiHandler(const std::string& loginStr)
    : loginStr_(loginStr)
{

}

void TradeApiHandler::RspLogin(const ErrorMessage& msg, const LoginRsp& req, uint32_t reqId)
{
    ServiceMap::GetInstance().PushAllSession(loginStr_, ResponseType::RspLogin, msg, reqId, (char*)&req, sizeof(req));
}
void TradeApiHandler::RspOrderInsert(const ErrorMessage& msg, const OrderInsertRsp& req, uint32_t reqId)
{
    
}
void TradeApiHandler::RspOrderCancel(const ErrorMessage& msg, const OrderCancelRsp& req, uint32_t reqId)
{
    
}
void TradeApiHandler::RspQryAsset(const ErrorMessage& msg, const QryAssetRsp& req, uint32_t reqId)
{
    
}
void TradeApiHandler::RspQryPosition(const ErrorMessage& msg, const QryPositionRsp& req, uint32_t reqId)
{
    
}
void TradeApiHandler::RspQryOrder(const ErrorMessage& msg, const QryOrderRsp& req, uint32_t reqId)
{
    
}
void TradeApiHandler::RspQryTrade(const ErrorMessage& msg, const QryTradeRsp& req, uint32_t reqId)
{
    
}
void TradeApiHandler::RtnOrder(const ErrorMessage& msg, const OrderRtn& rtn)
{
    
}
void TradeApiHandler::RtnTrade(const ErrorMessage& msg, const TradeRtn& rtn)
{
    
}