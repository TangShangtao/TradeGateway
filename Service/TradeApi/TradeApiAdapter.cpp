#include "TradeApiAdapter.h"

TradeApiAdapter::TradeApiAdapter(const std::string& loginStr)
    : loginStr_(loginStr), handler_(loginStr)
{

}

