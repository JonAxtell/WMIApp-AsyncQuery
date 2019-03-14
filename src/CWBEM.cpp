#include "pch.h"
#include "CWBEM.h"
#include <iostream>

// Network resource should be ::_bstr_t(L"ROOT\\CIMV2")
CWBEM::CWBEM(const std::string& networkResource) : _networkResource(networkResource), _pLoc(nullptr), _pSvc(nullptr)
{
    _pLoc = NULL;
    HRESULT hres = ::CoCreateInstance(::CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_pLoc));
    if (FAILED(hres))
    {
        throw std::runtime_error(std::string("CWBEM::CWBEM Failed to create IWbemLocator object. Error code = 0x") + NumberToHex(hres));
    }
}

CWBEM::~CWBEM()
{
    if (_pSvc != nullptr)
    {
        _pSvc->Release();
    }
    if (_pLoc != nullptr)
    {
        _pLoc->Release();
    }
}

void CWBEM::ConnectServer()
{
    // Use WBEM_FLAG_CONNECT_USE_MAX_WAIT to limit wait to 2 minutes or less
    BSTR netres;
    netres = ConvertStringToBSTR(_networkResource.c_str());
    HRESULT hres = _pLoc->ConnectServer(netres,                             // Network resource
        NULL,                               // User
        NULL,                               // Password
        0,                                  // Locale
        WBEM_FLAG_CONNECT_USE_MAX_WAIT,     // Security flags
        0,                                  // Authority
        0,                                  // WBEM context
        &_pSvc);                            // WBEM Services namespace
    if (FAILED(hres))
    {
        throw std::runtime_error(std::string("CWBEM::ConnectServer Could not connect to ") + _networkResource + std::string(". Error code = 0x") + NumberToHex(hres));
    }
    ::SysFreeString(netres);

    std::wcout << L"Connected to " << _networkResource.c_str() << L" WMI namespace" << std::endl;

    hres = ::CoSetProxyBlanket(_pSvc,                       // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
        NULL,                        // Server principal name 
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE);                  // proxy capabilities 
    if (FAILED(hres))
    {
        throw std::runtime_error(std::string("Could not set proxy blanket. Error code = 0x" + NumberToHex(hres)));
    }
}
