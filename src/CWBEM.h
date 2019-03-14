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
    ~CWBEM();

    void ConnectServer();

    ::IWbemServices* Service() { return _pSvc; }

private:
    CWBEM(const CWBEM&) = delete;
    CWBEM& operator=(const CWBEM&) = delete;
    CWBEM* operator&() = delete;

    const std::string _networkResource;
    ::IWbemLocator *_pLoc;
    ::IWbemServices *_pSvc;
};
