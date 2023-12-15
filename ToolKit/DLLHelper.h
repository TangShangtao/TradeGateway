#include <dlfcn.h>
#include <string>
#include "Logger.h"

class DLLHelper
{
public:
    static void* LoadLib(const std::string& path);

    static void* LoadSymbol(void* dllHandle, const std::string& symbolName);

    static void FreeLib(void* dllHandle);
};