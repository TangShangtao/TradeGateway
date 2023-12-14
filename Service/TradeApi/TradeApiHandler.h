#pragma once
#include "Protocol.h"
#include <string>
using namespace TradeGateway;

class TradeApiHandler
{
public:
    explicit TradeApiHandler(const std::string& loginStr);
public:
<<<<<<< HEAD
    void RspLogin(const ErrorMessage& msg, const LoginRsp& rsp, uint32_t reqId);
    void RspOrderInsert(const ErrorMessage& msg, const OrderInsertRsp& rsp, uint32_t reqId);
    void RspOrderCancel(const ErrorMessage& msg, const OrderCancelRsp& rsp, uint32_t reqId);
    void RspQryAsset(const ErrorMessage& msg, const QryAssetRsp& rsp, uint32_t reqId);
    void RspQryPosition(const ErrorMessage& msg, const QryPositionRsp& rsp, uint32_t reqId);
    void RspQryOrder(const ErrorMessage& msg, const QryOrderRsp& rsp, uint32_t reqId);
    void RspQryTrade(const ErrorMessage& msg, const QryTradeRsp& rsp, uint32_t reqId);
=======
    void RspLogin(const ErrorMessage& msg, const LoginRsp& req, uint32_t reqId);
    void RspOrderInsert(const ErrorMessage& msg, const OrderInsertRsp& req, uint32_t reqId);
    void RspOrderCancel(const ErrorMessage& msg, const OrderCancelRsp& req, uint32_t reqId);
    void RspQryAsset(const ErrorMessage& msg, const QryAssetRsp& req, uint32_t reqId);
    void RspQryPosition(const ErrorMessage& msg, const QryPositionRsp& req, uint32_t reqId);
    void RspQryOrder(const ErrorMessage& msg, const QryOrderRsp& req, uint32_t reqId);
    void RspQryTrade(const ErrorMessage& msg, const QryTradeRsp& req, uint32_t reqId);
>>>>>>> d23a801dd2219c996fa3c08a1a397f61399093de
    void RtnOrder(const ErrorMessage& msg, const OrderRtn& rtn);
    void RtnTrade(const ErrorMessage& msg, const TradeRtn& rtn);
private:
    std::string loginStr_;
};