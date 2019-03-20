// WMIApp-AsyncQuery.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "CWBEMObject.h"
#include "CWBEMProperty.h"
#include "CWin32Processor.h"
#include "CWin32BIOS.h"
#include "CWin32OperatingSystem.h"
#include "CWin32Desktop.h"
#include "CWin32SerialPort.h"
#include "CWin32USBController.h"
#include "CWin32USBControllerDevice.h"
#include "CWin32Printer.h"
#include "CWin32PrinterConfiguration.h"
#include "CWin32PrinterDriver.h"
#include "CWin32PrintJob.h"
#include "CWin32Process.h"
#include "CWin32SoftwareLicensingProduct.h"
#include "CWin32PnpEntity.h"
#include "CWin32ClassicCOMApplicationClasses.h"
#include "CWin32ClassicCOMClass.h"
#include "CWin32DCOMApplication.h"
#include "CWin32COMApplicationClasses.h"
#include "CWin32COMApplication.h"
#include "CWin32COMClass.h"
#include "CWin32Product.h"
#include "CCIMComputerSystem.h"
#include "CCom.h"
#include "CWBEM.h"
#include "TWBEMObjects.h"
#include "TWBEMObjectQuery.h"
#include "TWBEMObjectSink.h"
#include "WMIQuery.h"
#include <Psapi.h>
#include <process.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <iterator>

#ifndef __MINGW_GCC_VERSION
#pragma comment(lib, "psapi.lib")
#endif

// Must be placed after precompiled header
//#define configLIST_PROCESSES
//#define configLIST_SOFTWARE_LICENSES
//#define configLIST_USB
//#define configLIST_PRINTER
//#define configLIST_COM
//#define configLIST_PNP_DEVICES
//#define configLIST_PRODUCTS

template <typename T>
void DumpTextualProperties(T t)
{
    std::vector<CWBEMObject::index_property_t> textual = t->Properties(VT_BSTR);
    std::wcout << L"Textual properties = " << textual.size() << std::endl;
    for (auto txt : textual)
    {
        std::wcout << txt.first << L" - " << t->PropertyName(txt.first) << L"=" << *txt.second << std::endl;
    }
}

template <typename T>
void DumpAllProperties(T t)
{
    std::wcout << L"All properties = " << t->Properties().size() << std::endl;
    for (auto &prop : t->Properties())
    {
        int i = static_cast<int>(&prop - &t->Properties()[0]);
        std::wcout << i << L" " << t->PropertyName(i) << L"=" << *prop << std::endl;
    }
}


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
    //CWBEM wbem("\\\\COMPUTER\\root\\cimv2", "USER", "PWD");
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
            std::wcout << &p - &processors.Objects()[0] << L" " << L"Processor is " << p->Architecture() << L"," << p->CpuFamily() << L"," << p->Description() << L"," << p->SocketDesignation() << std::endl;
            std::wcout << L"\t" << p->Availability() << L"," << p->CpuStatus() << L"," << p->Voltage() << L"," << p->Frequency() << std::endl;
            std::wcout << L"\t" << p->Status() << L"," << p->ConfigManagerErrorCode() << std::endl;

            DumpAllProperties(p);

            //std::wcout << L"All properties = " << p->Properties().size() << std::endl;
            //for (auto &prop : p->Properties())
            //{
            //    int i = static_cast<int>(&prop - &p->Properties()[0]);
            //    std::wcout << i << L" " << p->PropertyName(i) << L"=" << *prop << std::endl;
            //}

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

            DumpAllProperties(b);
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

            DumpAllProperties(o);
        }
    }

    //.............................................................................................................................
    // Desktop
    //
    TWBEMObjects<CWin32DesktopObject> desk;
    if (WMIQuery<CWin32DesktopObject>(wbem.Service(), desk.Objects(), CWin32DesktopObject::ObjectName))
    {
        for (auto &o : desk.Objects())
        {
            std::wcout << &o - &desk.Objects()[0] << L" " << o->Name() << std::endl;

            DumpAllProperties(o);
        }
    }

    //.............................................................................................................................
    // Serial Ports
    //
    TWBEMObjects<CWin32SerialPortObject> ports;
    if (WMIQuery<CWin32SerialPortObject>(wbem.Service(), ports.Objects(), CWin32SerialPortObject::ObjectName))
    {
        for (auto &p : ports.Objects())
        {
            std::wcout << &p - &ports.Objects()[0] << L" " << p->Caption() << std::endl;

            DumpAllProperties(p);
        }
    }

#ifdef configLIST_USB
    //.............................................................................................................................
    // USB Controller Device
    //
    TWBEMObjects<CWin32USBControllerDeviceObject> usbdev;
    if (WMIQuery<CWin32USBControllerDeviceObject>(wbem.Service(), usbdev.Objects(), CWin32USBControllerDeviceObject::ObjectName))
    {
        for (auto &u : usbdev.Objects())
        {
            std::wcout << &u - &usbdev.Objects()[0] << L" " << u->Antecedent() << L"," << u->Dependent() << std::endl;
        }
    }

    //.............................................................................................................................
    // USB Controller
    //
    TWBEMObjects<CWin32USBControllerObject> usb;
    if (WMIQuery<CWin32USBControllerObject>(wbem.Service(), usb.Objects(), CWin32USBControllerObject::ObjectName))
    {
        for (auto &u : usb.Objects())
        {
            std::wcout << &u - &usb.Objects()[0] << L" " << u->Caption() << L"," << u->Description() << L"," << u->DeviceID() << L"," << u->Name() << L"," << u->PNPDeviceID() << std::dec << std::endl;
        }
    }
#endif

#ifdef configLIST_PRINTER
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
    // Print jobs
    //
    TWBEMObjects<CWin32PrintJobObject> printJobs;
    if (WMIQuery<CWin32PrintJobObject>(wbem.Service(), printJobs.Objects(), CWin32PrintJobObject::ObjectName))
    {
        for (auto &p : printJobs.Objects())
        {
            std::wcout << &p - &printJobs.Objects()[0] << L" " << p->Description() << std::endl;
        }
    }
#endif

#ifdef configLIST_PROCESSES
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

#ifdef configLIST_COM
    //.............................................................................................................................
    // Classic COM Application Classes
    //
    TWBEMObjects<CWin32ClassicCOMApplicationClassesObject> classiccomappclasses;
    if (WMIQuery<CWin32ClassicCOMApplicationClassesObject>(wbem.Service(), classiccomappclasses.Objects(), CWin32ClassicCOMApplicationClassesObject::ObjectName))
    {
        for (auto& c : classiccomappclasses.Objects())
        {
            std::wcout << &c - &classiccomappclasses.Objects()[0] << L" " << c->PartComponentGUID() << L"," << c->GroupComponentGUID() << std::endl;
        }
    }

    //.............................................................................................................................
    // Classic COM Classes
    //
    TWBEMObjects<CWin32ClassicCOMClassObject> classiccomclass;
    if (WMIQuery<CWin32ClassicCOMClassObject>(wbem.Service(), classiccomclass.Objects(), CWin32ClassicCOMClassObject::ObjectName))
    {
        for (auto& c : classiccomclass.Objects())
        {
            std::wcout << &c - &classiccomclass.Objects()[0] << L" " << c->Name() << L"," << c->ComponentID() << std::endl;
        }
    }

    //.............................................................................................................................
    // DCOM Application
    //
    TWBEMObjects<CWin32DCOMApplicationObject> dcomapp;
    if (WMIQuery<CWin32DCOMApplicationObject>(wbem.Service(), dcomapp.Objects(), CWin32DCOMApplicationObject::ObjectName))
    {
        for (auto &c : dcomapp.Objects())
        {
            std::wcout << &c - &dcomapp.Objects()[0] << L" " << c->Name() << L"," << c->AppID() << std::endl;
        }
    }
#endif

#if 0
    //.............................................................................................................................
    // COM Application Classes
    //
    TWBEMObjects<CWin32COMApplicationClassesObject> comclasses;
    if (WMIQuery<CWin32COMApplicationClassesObject>(wbem.Service(), comclasses.Objects(), CWin32COMApplicationClassesObject::ObjectName))
    {
        for (auto &c : comclasses.Objects())
        {
            std::wcout << &c - &comclasses.Objects()[0] << L" " << c->PartComponent() << std::endl;
        }
    }

    //.............................................................................................................................
    // COM Applications
    //
    TWBEMObjects<CWin32COMApplicationObject> comobj;
    if (WMIQuery<CWin32COMApplicationObject>(wbem.Service(), comobj.Objects(), CWin32COMApplicationObject::ObjectName))
    {
        for (auto &c : comobj.Objects())
        {
            std::wcout << &c - &comobj.Objects()[0] << L" " << c->Name() << std::endl;
        }
    }

    //.............................................................................................................................
    // COM Application Classes
    //
    TWBEMObjects<CWin32COMClassObject> comclass;
    if (WMIQuery<CWin32COMClassObject>(wbem.Service(), comclass.Objects(), CWin32COMClassObject::ObjectName))
    {
        for (auto &c : comclass.Objects())
        {
            std::wcout << &c - &comclass.Objects()[0] << L" " << c->Name() << std::endl;
        }
    }
#endif

#ifdef configLIST_SOFTWARE_LICENSES
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
            std::vector<std::wstring> roles = c->Roles();
            for (std::vector<std::wstring>::iterator r = roles.begin(); r != roles.end(); ++r)
            {
                if (r == roles.begin())
                {
                    std::wcout << L"Roles:\t";
                }
                else
                {
                    std::wcout << L"\t";
                }
                std::wcout << *r << std::endl;
            }
        }
    }

#ifdef configLIST_PRODUCTS
    //.............................................................................................................................
    // Products
    //
    TWBEMObjects<CWin32ProductObject> prodobj;
    if (WMIQuery<CWin32ProductObject>(wbem.Service(), prodobj.Objects(), CWin32ProductObject::ObjectName))
    {
        for (auto &p : prodobj.Objects())
        {
            std::wcout << &p - &prodobj.Objects()[0] << L" " << p->Description() << std::endl;
        }
    }
#endif

#ifdef configLIST_PNP_DEVICES
    //.............................................................................................................................
    // Pnp Devices
    //
    TWBEMObjects<CWin32PnpEntityObject> devices;
    if (WMIQuery<CWin32PnpEntityObject>(wbem.Service(), devices.Objects(), CWin32PnpEntityObject::ObjectName))
    {
        for (auto &d : devices.Objects())
        {
            if (!d->Present())
            {
                continue;
            }
            std::wcout << &d - &devices.Objects()[0] << L" ";
            if (d->Description().empty() && d->Caption().empty())
            {
                // Description and caption are blank so use name
                std::wcout << d->Name();
            }
            else if (d->Description().empty())
            {
                // No description, so use caption
                std::wcout << d->Caption();
            }
            else if (d->Caption().empty())
            {
                // No caption, so use description
                std::wcout << d->Description();
            }
            else if (d->Description() != d->Caption())
            {
                // Description is not the same as caption, so print both
                std::wcout << d->Description() << L"," << d->Caption();
            }
            else
            {
                // Description and caption aren't blank and are the same so just use description
                std::wcout << d->Description();
            }
            std::wcout << std::endl;
            for (auto &i : d->CompatibleID())
            {
                std::wcout << L"\t" << i << L" " << std::endl;
            }
        }
    }
#endif

#ifdef _DEBUG
    //PrintMemoryInfo(_getpid());
    _RPT1(_CRT_WARN, "HEAPCHK=%d", _heapchk());
    //std::wcout << L"HEAPCHK=" << _heapchk() << std::endl;
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
    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    //_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    //_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    //_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    //_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    //_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

    // Send all reports to debug channel
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    //PrintMemoryInfo(_getpid());
    _RPT1(_CRT_WARN, "HEAPCHK=%d", _heapchk());
    //std::wcout << L"HEAPCHK=" << _heapchk() << std::endl;
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
        std::cout << "HRESULT Error 0x" << std::hex << hres << std::dec << std::endl;
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