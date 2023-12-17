#include "TradeApiHandler.h"
#include "../ServiceMap/ServiceMap.h"
#include "Logger.h"

TradeApiHandler::TradeApiHandler(const std::string& loginStr)
    : loginStr_(loginStr)
{

}

void TradeApiHandler::RspLogin(const ErrorMessage& msg, const LoginRsp& rsp, uint32_t gatewayReqId)
{
    INFO("RspLogin : {}, {}, {}, loginStr: {}", msg.DebugInfo(), rsp.DebugInfo(), gatewayReqId, loginStr_);
    ServiceMap::GetInstance().PushOneSession(gatewayReqId, ResponseType::RspLogin, msg, (char*)&rsp, sizeof(rsp));
}
void TradeApiHandler::RspOrderInsert(const ErrorMessage& msg, const OrderInsertRsp& rsp, uint32_t gatewayReqId)
{
    
}
void TradeApiHandler::RspOrderCancel(const ErrorMessage& msg, const OrderCancelRsp& rsp, uint32_t gatewayReqId)
{
    
}
void TradeApiHandler::RspQryAsset(const ErrorMessage& msg, const QryAssetRsp& rsp, uint32_t gatewayReqId)
{
    
}
void TradeApiHandler::RspQryPosition(const ErrorMessage& msg, const QryPositionRsp& rsp, uint32_t gatewayReqId)
{
    
}
void TradeApiHandler::RspQryOrder(const ErrorMessage& msg, const QryOrderRsp& rsp, uint32_t gatewayReqId)
{
    
}
void TradeApiHandler::RspQryTrade(const ErrorMessage& msg, const QryTradeRsp& rsp, uint32_t gatewayReqId)
{
    
}
void TradeApiHandler::RtnOrder(const ErrorMessage& msg, const OrderRtn& rtn)
{
    
}
void TradeApiHandler::RtnTrade(const ErrorMessage& msg, const TradeRtn& rtn)
{
    
}