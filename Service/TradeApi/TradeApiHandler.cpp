#include "TradeApiHandler.h"
#include "../ServiceMap/ServiceMap.h"
<<<<<<< HEAD
#include "Logger.h"
=======
>>>>>>> d23a801dd2219c996fa3c08a1a397f61399093de

TradeApiHandler::TradeApiHandler(const std::string& loginStr)
    : loginStr_(loginStr)
{

}

<<<<<<< HEAD
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
=======
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
>>>>>>> d23a801dd2219c996fa3c08a1a397f61399093de
{
    
}
void TradeApiHandler::RtnOrder(const ErrorMessage& msg, const OrderRtn& rtn)
{
    
}
void TradeApiHandler::RtnTrade(const ErrorMessage& msg, const TradeRtn& rtn)
{
    
}