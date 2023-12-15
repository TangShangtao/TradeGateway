#include "DLLHelper.h"

void* DLLHelper::LoadLib(const std::string& path)
{
    try
    {
        auto dllHandle = dlopen(path.c_str(), RTLD_NOW);
        if (!dllHandle) ERROR("LoadLib {} failed, dlerror: {}", path, dlerror());

        return dllHandle;
        
    }
    catch(const std::exception& e)
    {
        ERROR("LoadLib {} failed, dlerror: {}", path, dlerror());
        return nullptr;
    }
}

void* DLLHelper::LoadSymbol(void* dllHandle, const std::string& symbolName)
{
    if (!dllHandle) return nullptr;
    try
    {
        auto symbolHandle = dlsym(dllHandle, symbolName.c_str());
        if (!symbolHandle) ERROR("LoadSymbol {} failed, dlerror: {}", symbolName, dlerror());

        return symbolHandle;
    }
    catch(const std::exception& e)
    {
        ERROR("LoadSymbol {} failed, dlerror: {}", symbolName, dlerror());
        return nullptr;
    }

}

void DLLHelper::FreeLib(void* dllHandle)
{
    dlclose(dllHandle);
}