#include "pch.h"
#include "CCom.h"

// COINIT_MULTITHREADED or COINIT_APARTMENTTHREADED
CCOM::CCOM(COINIT model)
{
    HRESULT hres = ::CoInitializeEx(NULL, model | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hres))
    {
        throw std::runtime_error(std::string("Failed to initialize COM library. Error code = 0x") + NumberToHex(hres));
    }
    if (hres == S_FALSE)
    {
        throw std::runtime_error(std::string("COM already initialized"));
    }
    InitializeSecurity();
}

CCOM::~CCOM()
{
    ::CoUninitialize();
}

void CCOM::InitializeSecurity()
{
    HRESULT hres = ::CoInitializeSecurity(NULL,                         // Security descriptor
        -1,                           // COM Authentication
        NULL,                         // Authentication services
        NULL,                         // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,    // Authentication level
        RPC_C_IMP_LEVEL_IMPERSONATE,  // Impersonation level
        NULL,                         // Authentication list
        EOAC_NONE,                    // Additional capabilities 
        NULL);                        // Reserved
    if (FAILED(hres))
    {
        throw std::runtime_error(std::string("Failed to initialize security. Error code = 0x") + NumberToHex(hres));
    }
}
