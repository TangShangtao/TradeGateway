#include "TestApi.h"


TestApi::TestApi(const std::string& loginStr)
    : TradeApiAdapter(loginStr)
{

}
TestApi::~TestApi()
{
    
}
void TestApi::ReqLogin(const LoginReq& req, uint32_t reqId)
{
    
}
void TestApi::ReqOrderInsert(const OrderInsertReq& req, uint32_t reqId)
{
    
}
void TestApi::ReqOrderCancel(const OrderCancelReq& req, uint32_t reqId)
{
    
}
void TestApi::ReqQryAsset(const QryAssetReq& req, uint32_t reqId)
{
    
}
void TestApi::ReqQryPosition(const QryPositionReq& req, uint32_t reqId)
{
    
}
void TestApi::ReqQryOrder(const QryOrderReq& req, uint32_t reqId)
{
    
}
void TestApi::ReqQryTrade(const QryTradeReq& req, uint32_t reqId)
{
    
}