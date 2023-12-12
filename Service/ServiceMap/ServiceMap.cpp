#include "ServiceMap.h"
#include "Logger.h"

void ServiceMap::AddNewSession(const std::string& loginStr, SocketSession* session)
{
    loginStr2SocketSession_[loginStr].insert(session);
}

void ServiceMap::RemoveThisSession(SocketSession* session)
{
    for (auto it = loginStr2SocketSession_.begin(); it != loginStr2SocketSession_.end(); it++)
    {
        if (it->second.count(session))
        {
            it->second.erase(session);
            DEBUG("remove socket session from map");
            break;
        }
    }
}

void ServiceMap::AddTradeApi(const std::string& loginStr, TradeApiAdapter* tradeApi)
{
    loginStr2TradeApi_[loginStr] = tradeApi;
}

void ServiceMap::RemoveTradeApi(TradeApiAdapter* tradeApi)
{
    for (auto it = loginStr2TradeApi_.begin(); it != loginStr2TradeApi_.end(); it++)
    {
        if (it->second == tradeApi)
        {
            loginStr2TradeApi_.erase(it);
            DEBUG("remove tradeApi from map");
            break;
        }
    }
}

void ServiceMap::PushAllSession(std::string& loginStr, ResponseType type, const ErrorMessage& errorMessage, uint32_t reqId, char* responseDataStart, uint32_t responseDataLen)
{
    auto& sessions = loginStr2SocketSession_[loginStr];
    for (SocketSession* session : sessions)
    {
        session->ProcessResponseData(type, errorMessage, reqId, responseDataStart, responseDataLen);
    }
}