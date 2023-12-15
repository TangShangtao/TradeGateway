#include "CTPApi.h"
#include "Logger.h"
#include  <cstring>

CTPApi::CTPApi(const std::string& loginStr)
    : TradeApiAdapter(loginStr)
{
    apiName_ = "CTPApi";
    spi_ = new CTPSpi(this);
}

CTPApi::~CTPApi()
{
    userApi_->Release();
    delete spi_;
}
int CTPApi::ReqLogin(const LoginReq& req, uint32_t reqId)
{
    loginReqId_ = reqId;

    ip_ = TradeApiAdapter::GetColValue(loginStr_, "ip");
    port_ = TradeApiAdapter::GetColValue(loginStr_, "port");
    brokerid_ = TradeApiAdapter::GetColValue(loginStr_, "brokerid");
    authcode_ = TradeApiAdapter::GetColValue(loginStr_, "authcode");
    appid_ = TradeApiAdapter::GetColValue(loginStr_, "appid");
    account_ = TradeApiAdapter::GetColValue(loginStr_, "account");
    password_ = TradeApiAdapter::GetColValue(loginStr_, "password");
    std::string remoteAddr = "tcp://" + ip_ + ":" + port_;
    userApi_ = CThostFtdcTraderApi::CreateFtdcTraderApi();
    if (!userApi_)
    {
        ERROR("CThostFtdcTraderApi::CreateFtdcTraderApi() return nullptr");
        return -1;
    }
    userApi_->RegisterSpi(spi_);
    userApi_->SubscribePublicTopic(THOST_TERT_QUICK);  
    userApi_->SubscribePrivateTopic(THOST_TERT_QUICK); 
    userApi_->RegisterFront((char*)remoteAddr.c_str());
    userApi_->Init();
    return 0;

}
int CTPApi::ReqOrderInsert(const OrderInsertReq& req, uint32_t reqId)
{
    return 0;
}
int CTPApi::ReqOrderCancel(const OrderCancelReq& req, uint32_t reqId)
{
    return 0;
}
int CTPApi::ReqQryAsset(const QryAssetReq& req, uint32_t reqId)
{
    return 0;
}
int CTPApi::ReqQryPosition(const QryPositionReq& req, uint32_t reqId)
{
    return 0; 
}
int CTPApi::ReqQryOrder(const QryOrderReq& req, uint32_t reqId)
{
    return 0;
}
int CTPApi::ReqQryTrade(const QryTradeReq& req, uint32_t reqId)
{
    return 0;
}


CTPSpi::CTPSpi(CTPApi* api) : api_(api) {};

// 连接成功
void CTPSpi::OnFrontConnected() 
{
    INFO("CTPSpi OnFrontConnected");

    CThostFtdcReqAuthenticateField authField{0};
    strncpy(authField.BrokerID, api_->brokerid_.c_str(), sizeof(authField.BrokerID) - 1);
    strncpy(authField.UserID, api_->account_.c_str(), sizeof(authField.UserID) - 1);
    strncpy(authField.AuthCode, api_->authcode_.c_str(), sizeof(authField.AuthCode) - 1);
    strncpy(authField.AppID, api_->appid_.c_str(), sizeof(authField.AppID) - 1);

    CThostFtdcReqUserLoginField loginField{0};
    strncpy(loginField.BrokerID, api_->brokerid_.c_str(), sizeof(loginField.BrokerID) - 1);
    strncpy(loginField.UserID, api_->account_.c_str(), sizeof(loginField.UserID) - 1);
    strncpy(loginField.Password, api_->password_.c_str(), sizeof(loginField.Password) - 1);
    strncpy(loginField.BrokerID, api_->brokerid_.c_str(), sizeof(loginField.BrokerID) - 1);

    int result = api_->userApi_->ReqUserLogin(&loginField, api_->loginReqId_);
    if (result != 0)
    {
        ERROR("ReqUserLogin() return != 0");
    }
    return;
}
// 连接断开
void CTPSpi::OnFrontDisconnected(int nReason)
{
    ERROR("error: OnFrontDisconnected, nReason: {}", nReason);
}
// 回报认证结果
void CTPSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    
}
// 回报登录结果
void CTPSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    
}
// 回报结算单确认结果
void CTPSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    
}
// 回报修改密码结果
void CTPSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    
}
// 回报订单查询结果
void CTPSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    
}
// 回报成交查询结果 
void CTPSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    
}
// 回报持仓查询结果 
void CTPSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    
}
// 回报资金查询结果 
void CTPSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    
}
// 回报合约信息查询结果 
void CTPSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    
}
// 回报订单状态更新 
void CTPSpi::OnRtnOrder(CThostFtdcOrderField *pOrder) 
{
    
}
// 回报成交更新 
void CTPSpi::OnRtnTrade(CThostFtdcTradeField *pTrade) 
{
    
}
// 回报CTP拒单, 当前session触发回调
void CTPSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    
}
// 回报CTP拒撤单, 当前session触发回调
void CTPSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    
}
// 回报CTP拒单, 所有session触发回调
void CTPSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) 
{
    
}
// 回报CTP拒撤单, 所有session触发回调
void CTPSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) 
{
    
}