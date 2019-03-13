// WMIApp-AsyncQuery.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "CWin32Processor.h"
#include "CWin32BIOS.h"
#include "CWin32OperatingSystem.h"
#include "CWin32Printer.h"
#include "CWin32PrinterConfiguration.h"
#include "CWin32PrinterDriver.h"
#include "CWin32PrintJob.h"
#include "CWin32Process.h"
#include "CWin32SoftwareLicensingProduct.h"
#include "CCIMComputerSystem.h"
#include "TWBEMObjectQuery.h"
#include "TWBEMObjectSink.h"
#include <Psapi.h>
#include <process.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <iterator>

#ifndef __MINGW_GCC_VERSION
#pragma comment(lib, "psapi.lib")
#endif

//#################################################################################################################################
//
template<typename COBJECT>
bool WMIQuery(::IWbemServices *pSvc, std::vector<COBJECT *>& obj, std::string className)
{
    try
    {
        TWBEMObjectQuery<TWBEMObjectSink<COBJECT> >* query = new TWBEMObjectQuery<TWBEMObjectSink<COBJECT> >(pSvc, className.c_str());
        std::wcout << L"Querying " << query->WMIClassName().c_str() << std::endl;
        query->Query();
        while (!query->IsDone())
        {
            ::Sleep(100);
        }
        if (!query->HasIndicated())
        {
            std::wcout << L"WMIQuery Object " << query->WMIClassName().c_str() << L" not populated." << std::endl;
            delete query;
            return false;
        }

        std::wcout << L"Object " << query->WMIClassName().c_str() << L" populated with " << query->Sink()->Count() << L" items" << std::endl;

        // Transfer the objects out of the sink before the sink loses focus
        obj = *reinterpret_cast<std::vector<COBJECT *> *>(&query->Sink()->Objects());
        delete query;
        return true;
    }
    catch (HRESULT hres)
    {
        throw std::runtime_error(std::string("WMIQuery Query for ") + className + std::string(" details failed. Error code = 0x") + NumberToHex(hres));
    }
    catch (std::runtime_error err)
    {
        throw err;
    }
    return false;
}

//#################################################################################################################################
//
class CCOM
{
public:
    // COINIT_MULTITHREADED or COINIT_APARTMENTTHREADED
    CCOM(COINIT model) 
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
    ~CCOM() 
    {
        ::CoUninitialize();
    }

    void InitializeSecurity()
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

private:
    CCOM(const CCOM&) = delete;
    CCOM& operator=(const CCOM&) = delete;
    CCOM* operator&() = delete;
};

//#################################################################################################################################
//
class CWBEM
{
public:
    // Network resource should be ::_bstr_t(L"ROOT\\CIMV2")
    CWBEM(const std::string& networkResource) : _networkResource(networkResource), _pLoc(nullptr), _pSvc(nullptr)
    {
        _pLoc = NULL;
        HRESULT hres = ::CoCreateInstance(::CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_pLoc));
        if (FAILED(hres))
        {
            throw std::runtime_error(std::string("CWBEM::CWBEM Failed to create IWbemLocator object. Error code = 0x") + NumberToHex(hres));
        }
    }
    ~CWBEM() 
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

    void ConnectServer()
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

    ::IWbemServices* Service() { return _pSvc; }

private:
    CWBEM(const CWBEM&) = delete;
    CWBEM& operator=(const CWBEM&) = delete;
    CWBEM* operator&() = delete;

    const std::string _networkResource;
    ::IWbemLocator *_pLoc;
    ::IWbemServices *_pSvc;
};

#ifdef _DEBUG
//.................................................................................................................................
//
void PrintMemoryInfo(DWORD processID)
{
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;

    // Print the process identifier.

    printf("\nProcess ID: %u\n", processID);

    // Print information about the memory usage of the process.

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (NULL == hProcess)
    {
        return;
    }

    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
    {
        printf("\tPageFaultCount: 0x%08X\n", pmc.PageFaultCount);
        printf("\tPeakWorkingSetSize: 0x%08X\n", (DWORD)pmc.PeakWorkingSetSize);
        printf("\tWorkingSetSize: 0x%08X\n", (DWORD)pmc.WorkingSetSize);
        printf("\tQuotaPeakPagedPoolUsage: 0x%08X\n", (DWORD)pmc.QuotaPeakPagedPoolUsage);
        printf("\tQuotaPagedPoolUsage: 0x%08X\n", (DWORD)pmc.QuotaPagedPoolUsage);
        printf("\tQuotaPeakNonPagedPoolUsage: 0x%08X\n", (DWORD)pmc.QuotaPeakNonPagedPoolUsage);
        printf("\tQuotaNonPagedPoolUsage: 0x%08X\n", (DWORD)pmc.QuotaNonPagedPoolUsage);
        printf("\tPagefileUsage: 0x%08X\n", (DWORD)pmc.PagefileUsage);
        printf("\tPeakPagefileUsage: 0x%08X\n", (DWORD)pmc.PeakPagefileUsage);
    }

    CloseHandle(hProcess);
}

//.................................................................................................................................
//
void heapdump(void)
{
    _HEAPINFO hinfo;
    int heapstatus;
    int numLoops;
    hinfo._pentry = NULL;
    numLoops = 0;
    while ((heapstatus = _heapwalk(&hinfo)) == _HEAPOK && numLoops < 100)
    {
        printf("%8s block at %p of size %4.4X\n", (hinfo._useflag == _USEDENTRY ? "USED" : "FREE"), hinfo._pentry, (DWORD)hinfo._size);
        numLoops++;
    }
    printf("Number of blocks is %d\n", numLoops);

    switch (heapstatus)
    {
        case _HEAPEMPTY:
            printf("OK - empty heap\n");
            break;
        case _HEAPEND:
            printf("OK - end of heap\n");
            break;
        case _HEAPBADPTR:
            printf("ERROR - bad pointer to heap\n");
            break;
        case _HEAPBADBEGIN:
            printf("ERROR - bad start of heap\n");
            break;
        case _HEAPBADNODE:
            printf("ERROR - bad node in heap\n");
            break;
    }
}
#endif

//---------------------------------------------------------------------------------------------------------------------------------
//
void ListWBEMObjects()
{
    CCOM com(COINIT_MULTITHREADED);
    CWBEM wbem("ROOT\\CIMV2");
    wbem.ConnectServer();

    //.............................................................................................................................
    // Processors
    //
    TWBEMObjects<CWin32ProcessorObject> processors;
    if (WMIQuery<CWin32ProcessorObject>(wbem.Service(), processors.Objects(), CWin32ProcessorObject::ObjectName))
    {
        for (auto &p : processors.Objects())
        {
            std::wcout << &p - &processors.Objects()[0] << L" " << L"Processor is " << p->Architecture() << L"," << p->Availability() << L"," << p->CpuStatus() << L"," << p->Description() << L"," << p->Voltage() << L"," << p->Frequency() << L"," << p->CpuFamily() << L"," << p->SocketDesignation() << std::endl;
        }
    }

    //.............................................................................................................................
    // BIOS
    //
    TWBEMObjects<CWin32BIOSObject> bios;
    if (WMIQuery<CWin32BIOSObject>(wbem.Service(), bios.Objects(), CWin32BIOSObject::ObjectName))
    {
        for (auto &b : bios.Objects())
        {
            std::wcout << &b - &bios.Objects()[0] << L" " << b->Description() << std::endl;
        }
    }

    //.............................................................................................................................
    // Operating System
    //
    TWBEMObjects<CWin32OperatingSystemObject> os;
    if (WMIQuery<CWin32OperatingSystemObject>(wbem.Service(), os.Objects(), CWin32OperatingSystemObject::ObjectName))
    {
        for (auto &o : os.Objects())
        {
            std::wcout << &o - &os.Objects()[0] << L" " << o->Caption() << std::endl;
        }
    }

    //.............................................................................................................................
    // Printers
    //
    TWBEMObjects<CWin32PrinterObject> printers;
    if (WMIQuery<CWin32PrinterObject>(wbem.Service(), printers.Objects(), CWin32PrinterObject::ObjectName))
    {
        for (auto &p : printers.Objects())
        {
            std::wcout << &p - &printers.Objects()[0] << L" " << p->Caption() << std::endl;
        }
    }

    //.............................................................................................................................
    // Printer configurations
    //
    TWBEMObjects<CWin32PrinterConfigurationObject> printerConfigurations;
    if (WMIQuery<CWin32PrinterConfigurationObject>(wbem.Service(), printerConfigurations.Objects(), CWin32PrinterConfigurationObject::ObjectName))
    {
        for (auto &p : printerConfigurations.Objects())
        {
            std::wcout << &p - &printerConfigurations.Objects()[0] << L" " << p->Description() << std::endl;
        }
    }

    //.............................................................................................................................
    // Printer drivers
    //
    TWBEMObjects<CWin32PrinterDriverObject> printerDrivers;
    if (WMIQuery<CWin32PrinterDriverObject>(wbem.Service(), printerDrivers.Objects(), CWin32PrinterDriverObject::ObjectName))
    {
        for (auto &p : printerDrivers.Objects())
        {
            std::wcout << &p - &printerDrivers.Objects()[0] << L" " << p->Name() << std::endl;
        }
    }

    //.............................................................................................................................
    // Print job
    //
    TWBEMObjects<CWin32PrintJobObject> printJobs;
    if (WMIQuery<CWin32PrintJobObject>(wbem.Service(), printJobs.Objects(), CWin32PrintJobObject::ObjectName))
    {
        for (auto &p : printJobs.Objects())
        {
            std::wcout << &p - &printJobs.Objects()[0] << L" " << p->Description() << std::endl;
        }
    }

#if 1
    //.............................................................................................................................
    // Processes
    //
    TWBEMObjects<CWin32ProcessObject> processes;
    if (WMIQuery<CWin32ProcessObject>(wbem.Service(), processes.Objects(), CWin32ProcessObject::ObjectName))
    {
        for (auto &p : processes.Objects())
        {
            std::wcout << &p - &processes.Objects()[0] << L" " << p->ProcessId() << L" " << p->Name() << L" " << p->HandleCount() << std::endl;
        }
    }
#endif

#if 0
    //.............................................................................................................................
    // Software Licensing Product
    //
    TWBEMObjects<CWin32SoftwareLicensingProductObject> products;
    if (WMIQuery<CWin32SoftwareLicensingProductObject>(wbem.Service(), products.Objects(), CWin32SoftwareLicensingProductObject::ObjectName))
    {
        for (auto &p : products.Objects())
        {
            std::wcout << &p - &products.Objects()[0] << L" " << p->Description() << std::endl;
        }
    }
#endif

    //.............................................................................................................................
    // CIM Computer System
    //
    TWBEMObjects<CCIMComputerSystemObject> computer;
    if (WMIQuery<CCIMComputerSystemObject>(wbem.Service(), computer.Objects(), CCIMComputerSystemObject::ObjectName))
    {
        for (auto &c : computer.Objects())
        {
            std::wcout << &c - &computer.Objects()[0] << L" " <<
                c->Caption() << L"," <<
                c->Description() << L"," <<
                c->InstallDate() << L"," <<
                c->Status() << L"," <<
                c->CreationClassName() << L"," <<
                c->Name() << L"," <<
                c->NameFormat() << L"," <<
                c->PrimaryOwnerContact() << L"," <<
                c->PrimaryOwnerName() << std::endl;
            for (auto &r : c->Roles())
            {
                std::wcout << r << std::endl;
            }
        }
    }
#ifdef _DEBUG
    //PrintMemoryInfo(_getpid());
    std::wcout << L"HEAPCHK=" << _heapchk() << std::endl;
#endif
}

//#################################################################################################################################
//
int main(int argc, char **argv)
{
    argc = argc;
    argv = argv;
#ifdef _DEBUG
    DWORD dbgFlag = _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
    dbgFlag = (dbgFlag & 0x0000FFFF) | _CRTDBG_CHECK_EVERY_16_DF;
    _CrtSetDbgFlag(dbgFlag);

    // Send all reports to STDOUT
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    //PrintMemoryInfo(_getpid());
    std::wcout << L"HEAPCHK=" << _heapchk() << std::endl;
    _CrtMemState s1;
    _CrtMemCheckpoint(&s1);
    _CrtMemDumpStatistics(&s1);
#endif

    try
    {
        ListWBEMObjects();
    }
    catch (HRESULT hres)
    {
        std::cout << "Error 0x" << std::hex << hres << std::dec << std::endl;
    }
    catch (std::runtime_error err)
    {
        std::cout << std::flush << "Runtime error: " << err.what() << std::flush;
    }
    catch (std::exception exp)
    {
        std::cout << exp.what() << "Exception: " << std::flush;
    }
    catch (...)
    {
        std::cout << "Unknown error, something went wrong " << std::endl;
    }

 #ifdef _DEBUG
    _CrtMemState s2;
    _CrtMemCheckpoint(&s2);
    _CrtMemDumpStatistics(&s2);
    
    _CrtMemState s3;
    if (_CrtMemDifference(&s3, &s1, &s2) == TRUE)
    {
        _CrtMemDumpStatistics(&s3);
    }

 #endif
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
    return 0;
}