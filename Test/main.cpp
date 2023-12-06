#include "Logger.h"
#include "Acceptor/Acceptor.h"
#include "Reactor/Reactor.h"

int main()
{
    Logger::Init(Logger::level_enum::debug);
    auto acceptor = Acceptor();
    acceptor.Listen(9876);
    Reactor::GetInstance().Run();


}