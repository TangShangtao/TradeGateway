#include "TradeApiAdapter.h"
#include "Logger.h"
#include <vector>
#include <string>
#include <sstream>

TradeApiAdapter::TradeApiAdapter(const std::string& loginStr)
    : loginStr_(loginStr), handler_(loginStr)
{

}

std::vector<std::string> split(const std::string& source, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(source);
    std::string item;
    
    while (std::getline(ss, item, delim))
    {
        result.push_back(item);
    }
    
    return result;
}

// loginStr格式: colName1=colValue1;colName2=colValue2;
std::string TradeApiAdapter::GetColValue(const std::string& loginStr, const std::string& colName)
{
    auto result = split(loginStr, ';');
    for (const auto& str : result)
    {
        auto vec = split(str, '=');
        if (vec.size() <= 1) return "";
        if (vec[0] == colName) return vec[1];
    }
    ERROR("colName {} not found, loginStr {}", colName, loginStr);
    return "";
}