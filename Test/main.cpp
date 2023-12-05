#include "Logger.h"
int main()
{
    Logger::Init(Logger::level_enum::debug);
    INFO("aaa");

}