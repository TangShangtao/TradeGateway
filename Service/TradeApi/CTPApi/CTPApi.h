#pragma once
#include "TradeApiAdapter.h"
#include "ThostFtdcTraderApi.h"

class CTPSpi;

class CTPApi : public TradeApiAdapter
{
public:
    friend class CTPSpi;
    CTPApi(const std::string& loginStr);
    virtual ~CTPApi() override;
    virtual int ReqLogin(const LoginReq& req, uint32_t reqId) override;
    virtual int ReqOrderInsert(const OrderInsertReq& req, uint32_t reqId) override;
    virtual int ReqOrderCancel(const OrderCancelReq& req, uint32_t reqId) override;
    virtual int ReqQryAsset(const QryAssetReq& req, uint32_t reqId) override;
    virtual int ReqQryPosition(const QryPositionReq& req, uint32_t reqId) override;
    virtual int ReqQryOrder(const QryOrderReq& req, uint32_t reqId) override;
    virtual int ReqQryTrade(const QryTradeReq& req, uint32_t reqId) override;
private:
    CThostFtdcTraderApi* userApi_;
    CTPSpi* spi_;
    std::string ip_;
    std::string port_;
    std::string brokerid_;
    std::string authcode_;
    std::string appid_;
    std::string account_;
    std::string password_;

    uint32_t loginReqId_;

};

extern "C" TradeApiAdapter* CreateTradeApi(const std::string& loginStr)
{
    return new CTPApi(loginStr);
}

class CTPSpi : public CThostFtdcTraderSpi
{
public:
    CTPSpi(CTPApi* api);
    ~CTPSpi() = default;
    // 连接成功
	virtual void OnFrontConnected() override;
    // 连接断开
	virtual void OnFrontDisconnected(int nReason) override;
    // 回报认证结果
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报登录结果
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报结算单确认结果
    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报修改密码结果
	virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报订单查询结果
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报成交查询结果 
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报持仓查询结果 
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报资金查询结果 
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报合约信息查询结果 
    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报订单状态更新 
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) override;
    // 回报成交更新 
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) override;
    // 回报CTP拒单, 当前session触发回调
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报CTP拒撤单, 当前session触发回调
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    // 回报CTP拒单, 所有session触发回调
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) override;
    // 回报CTP拒撤单, 所有session触发回调
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) override;

private:
    CTPApi* api_;

};