#pragma once
#include "Protocol.h"
#include <string>
using namespace TradeGateway;

class TradeApiHandler
{
public:
    explicit TradeApiHandler(const std::string& loginStr);
public:
    void RspLogin(const ErrorMessage& msg, const LoginRsp& rsp, uint32_t gatewayReqId);
    void RspOrderInsert(const ErrorMessage& msg, const OrderInsertRsp& rsp, uint32_t gatewayReqId);
    void RspOrderCancel(const ErrorMessage& msg, const OrderCancelRsp& rsp, uint32_t gatewayReqId);
    void RspQryAsset(const ErrorMessage& msg, const QryAssetRsp& rsp, uint32_t gatewayReqId);
    void RspQryPosition(const ErrorMessage& msg, const QryPositionRsp& rsp, uint32_t gatewayReqId);
    void RspQryOrder(const ErrorMessage& msg, const QryOrderRsp& rsp, uint32_t gatewayReqId);
    void RspQryTrade(const ErrorMessage& msg, const QryTradeRsp& rsp, uint32_t gatewayReqId);
    void RtnOrder(const ErrorMessage& msg, const OrderRtn& rtn);
    void RtnTrade(const ErrorMessage& msg, const TradeRtn& rtn);
private:
    std::string loginStr_;
};