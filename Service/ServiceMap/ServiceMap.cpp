#include "ServiceMap.h"
#include "Logger.h"

uint32_t ServiceMap::gatewayReqId_ = 0;
void ServiceMap::AddNewSession(const std::string& loginStr, SocketSession* session)
{
    loginStr2SocketSession_[loginStr].insert(session);
    INFO("Add new session, loginStr: {}", loginStr);
}

void ServiceMap::RemoveThisSession(SocketSession* session)
{
    for (auto it = loginStr2SocketSession_.begin(); it != loginStr2SocketSession_.end(); it++)
    {
        if (it->second.count(session) != 1) continue;

        it->second.erase(session);
        INFO("Remove socket session from map");
        if (it->second.size() == 0)
        {
            std::string loginStr = it->first;
            INFO("No session remain, delete loginStr: {}", loginStr);
            delete loginStr2TradeApi_[loginStr];
            loginStr2TradeApi_.erase(loginStr);
        }
        break;
    }

}

TradeApiAdapter* ServiceMap::GetTradeApi(const std::string& loginStr)
{
    if (loginStr2TradeApi_.count(loginStr))
    {
        return loginStr2TradeApi_[loginStr];
    }
    else
    {
        return nullptr;
    }
}

void ServiceMap::AddTradeApi(const std::string& loginStr, TradeApiAdapter* tradeApi)
{
    loginStr2TradeApi_[loginStr] = tradeApi;
}

void ServiceMap::PushAllSession(std::string& loginStr, ResponseType type, const ErrorMessage& errorMessage, char* responseDataStart, uint32_t responseDataLen)
{
    auto& sessions = loginStr2SocketSession_[loginStr];
    for (SocketSession* session : sessions)
    {
        session->ProcessResponseData(type, errorMessage, 0, responseDataStart, responseDataLen);
    }
}

void ServiceMap::PushOneSession(uint32_t gatewayReqId, ResponseType type, const ErrorMessage& errorMessage, char* responseDataStart, uint32_t responseDataLen)
{
    if (gatewayReqId2SessionReq_.count(gatewayReqId) == 0)
    {
        ERROR("error: gatewayReqId not found in map, gatewayReqId {}", gatewayReqId);
        return;
    }
    auto sessionReq = gatewayReqId2SessionReq_[gatewayReqId];
    uint32_t sessionReqId = sessionReq.first;
    SocketSession* session = sessionReq.second;
    session->ProcessResponseData(type, errorMessage, sessionReqId, responseDataStart, responseDataLen);

}

uint32_t ServiceMap::AddNewReq(uint32_t sessionReqId, SocketSession* session)
{
    gatewayReqId2SessionReq_[++gatewayReqId_] = {sessionReqId, session};
    return gatewayReqId_;
}

void ServiceMap::RemoveReq(uint32_t gatewayReqId)
{
    gatewayReqId2SessionReq_.erase(gatewayReqId);
}