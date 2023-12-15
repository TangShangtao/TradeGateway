#include "TestApi.h"
#include <cstring>

TestApi::TestApi(const std::string& loginStr)
    : TradeApiAdapter(loginStr)
{

}
TestApi::~TestApi()
{
    
}
int TestApi::ReqLogin(const LoginReq& req, uint32_t reqId)
{
    ErrorMessage msg{0};
    msg.errorID = 111;
    strncpy(msg.message, "aabbcc", sizeof(msg.message) - 1);
    LoginRsp rsp;
    handler_.RspLogin(msg, rsp, reqId);
    return 0;
}
int TestApi::ReqOrderInsert(const OrderInsertReq& req, uint32_t reqId)
{
    return 0;
}
int TestApi::ReqOrderCancel(const OrderCancelReq& req, uint32_t reqId)
{
    return 0;
}
int TestApi::ReqQryAsset(const QryAssetReq& req, uint32_t reqId)
{
    return 0;
}
int TestApi::ReqQryPosition(const QryPositionReq& req, uint32_t reqId)
{
    return 0; 
}
int TestApi::ReqQryOrder(const QryOrderReq& req, uint32_t reqId)
{
    return 0;
}
int TestApi::ReqQryTrade(const QryTradeReq& req, uint32_t reqId)
{
    return 0;
}