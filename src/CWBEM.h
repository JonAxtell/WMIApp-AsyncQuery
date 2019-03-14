#pragma once

#include "pch.h"

#include <Psapi.h>
#include <process.h>
#include <WbemCli.h>

//#################################################################################################################################
//
class CWBEM
{
public:
    // Network resource should be ::_bstr_t(L"ROOT\\CIMV2")
    CWBEM(const std::string& networkResource);
    CWBEM(const std::string& networkResource, const std::string& username, const std::string& password);
    CWBEM(const CWBEM&) = delete;
    CWBEM(CWBEM&&) = delete;
    ~CWBEM();
    CWBEM& operator=(const CWBEM&) = delete;
    CWBEM& operator=(CWBEM&&) = delete;

    void ConnectServer();

    ::IWbemServices* Service() { return _pSvc; }

private:
    void InitialiseContext(IWbemContext *pContext);

    const std::string _networkResource;
    const std::string _username;
    const std::string _password;
    ::IWbemLocator *_pLoc;
    ::IWbemContext *_pCtx;
    ::IWbemServices *_pSvc;
};
