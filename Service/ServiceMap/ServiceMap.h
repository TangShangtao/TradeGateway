#pragma once

#include "../Session/TradeSession.h"
#include "../Session/SocketSession.h"

#include <unordered_map>
#include <unordered_set>

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

    void AddNewSession(const std::string& loginStr, SocketSession* session);
    void RemoveThisSession(SocketSession* session);
    void AddTradeApi(const std::string& loginStr, TradeApiAdapter* tradeApi);
    void RemoveTradeApi(TradeApiAdapter* tradeApi);

    void PushAllSession(std::string& loginStr, ResponseType type, const ErrorMessage& errorMessage, uint32_t reqId, char* responseDataStart, uint32_t responseDataLen);
private:    
    // 一个登录字符串--一个TradeApi--一个TradeApiHandler--多个用同一登录字符串登录的socketSession
    std::unordered_map<std::string, TradeApiAdapter*> loginStr2TradeApi_;
    
    std::unordered_map<std::string, std::unordered_set<SocketSession*>> loginStr2SocketSession_;
};