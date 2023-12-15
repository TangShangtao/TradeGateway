#pragma once

#include "../Session/TradeSession.h"
#include "../Session/SocketSession.h"
#include "../TradeApi/TradeApiAdapter.h"

#include <unordered_map>
#include <unordered_set>
#include <utility>

// 全局路由表
class ServiceMap
{
public:
    static ServiceMap& GetInstance()
    {   
        static ServiceMap serviceMap;
        return serviceMap;
    }
    ServiceMap(const ServiceMap&) = delete;
    ServiceMap& operator=(const ServiceMap&) = delete;

    ServiceMap() = default;
    ~ServiceMap() = default;
    // SocketSession收到登录请求时调用, 添加至路由表
    void AddNewSession(const std::string& loginStr, SocketSession* session);
    // SocketSession析构时调用, 从路由表中删除; 若loginStr已经没有任何session, 则析构TradeApi, 从路由表中删除
    void RemoveThisSession(SocketSession* session);
    // SocketSession收到登录请求时调用(具体为TradeSession调用), 若相同的loginStr已经创建了一次TradeApi, 则继续使用这个TradeApi, 否则新创建一个
    TradeApiAdapter* GetTradeApi(const std::string& loginStr);
    void AddTradeApi(const std::string& loginStr, TradeApiAdapter* tradeApi);
    // 向全session推送, 用于RtnOrder和RtnTrade
    void PushAllSession(std::string& loginStr, ResponseType type, const ErrorMessage& errorMessage, char* responseDataStart, uint32_t responseDataLen);
    // 根据GatewayReqId向发出请求的session推送
    void PushOneSession(uint32_t gatewayReqId, ResponseType type, const ErrorMessage& errorMessage, char* responseDataStart, uint32_t responseDataLen);
    // 某socketSession有新的请求, 将其添加至路由表, 返回gatewayReqId
    uint32_t AddNewReq(uint32_t sessionReqId, SocketSession* session);
    // 请求处理完毕，从路由表中删除
    void RemoveReq(uint32_t gatewayReqId);
private:    
    // 一个loginStr--一个TradeApi--一个TradeApiHandler, 
    std::unordered_map<std::string, TradeApiAdapter*> loginStr2TradeApi_;
    // 一个loginStr--<多个用同一一个loginStr登录的SocketSession>
    std::unordered_map<std::string, std::unordered_set<SocketSession*>> loginStr2SocketSession_;
    // Gateway向柜台的ReqId--Session向Gateway的ReqId, session指针
    std::unordered_map<uint32_t, std::pair<uint32_t, SocketSession*>> gatewayReqId2SessionReq_;
    // Gateway向柜台的ReqId, 全局自增且唯一
    static uint32_t gatewayReqId_;



};