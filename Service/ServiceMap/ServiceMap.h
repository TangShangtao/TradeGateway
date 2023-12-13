#pragma once

#include "../Session/TradeSession.h"
#include "../Session/SocketSession.h"
#include "../TradeApi/TradeApiAdapter.h"

#include <unordered_map>
#include <unordered_set>

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
    void PushAllSession(std::string& loginStr, ResponseType type, const ErrorMessage& errorMessage, uint32_t reqId, char* responseDataStart, uint32_t responseDataLen);
private:    
    // 一个loginStr--一个TradeApi--一个TradeApiHandler, 
    std::unordered_map<std::string, TradeApiAdapter*> loginStr2TradeApi_;
    // 一个loginStr--<多个用同一一个loginStr登录的SocketSession>
    std::unordered_map<std::string, std::unordered_set<SocketSession*>> loginStr2SocketSession_;
};