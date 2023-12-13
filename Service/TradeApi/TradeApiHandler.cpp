#include "TradeApiHandler.h"
#include "../ServiceMap/ServiceMap.h"
#include "Logger.h"

TradeApiHandler::TradeApiHandler(const std::string& loginStr)
    : loginStr_(loginStr)
{

}

void TradeApiHandler::RspLogin(const ErrorMessage& msg, const LoginRsp& rsp, uint32_t reqId)
{
    INFO("RspLogin: {}, {}, {}", msg.DebugInfo(), rsp.DebugInfo(), reqId);
    ServiceMap::GetInstance().PushAllSession(loginStr_, ResponseType::RspLogin, msg, reqId, (char*)&rsp, sizeof(rsp));

}
void TradeApiHandler::RspOrderInsert(const ErrorMessage& msg, const OrderInsertRsp& rsp, uint32_t reqId)
{
    
}
void TradeApiHandler::RspOrderCancel(const ErrorMessage& msg, const OrderCancelRsp& rsp, uint32_t reqId)
{
    
}
void TradeApiHandler::RspQryAsset(const ErrorMessage& msg, const QryAssetRsp& rsp, uint32_t reqId)
{
    
}
void TradeApiHandler::RspQryPosition(const ErrorMessage& msg, const QryPositionRsp& rsp, uint32_t reqId)
{
    
}
void TradeApiHandler::RspQryOrder(const ErrorMessage& msg, const QryOrderRsp& rsp, uint32_t reqId)
{
    
}
void TradeApiHandler::RspQryTrade(const ErrorMessage& msg, const QryTradeRsp& rsp, uint32_t reqId)
{
    
}
void TradeApiHandler::RtnOrder(const ErrorMessage& msg, const OrderRtn& rtn)
{
    
}
void TradeApiHandler::RtnTrade(const ErrorMessage& msg, const TradeRtn& rtn)
{
    
}