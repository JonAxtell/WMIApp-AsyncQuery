#pragma once

#include "pch.h"
#include "CWBEMObject.h"
#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#ifndef __MINGW_GCC_VERSION
#pragma comment(lib, "wbemuuid.lib")
#endif

//#################################################################################################################################
//
// Template that instatiates the CWBEMObjectSink class
//
// The main purpose of this template it to define the Indicate method for the appropriate WBEM object class.
//
template<class COBJECT>
class TWBEMObjectSink : public CWBEMObjectSink
{
public:
    TWBEMObjectSink() : CWBEMObjectSink() { AddRef(); }
    TWBEMObjectSink(const TWBEMObjectSink&) = delete;
    TWBEMObjectSink(TWBEMObjectSink&&) = delete;
    ~TWBEMObjectSink() {}
    TWBEMObjectSink& operator=(const TWBEMObjectSink&) = delete;
    TWBEMObjectSink& operator=(TWBEMObjectSink&&) = delete;

    // IWbemObjectSink methods
    HRESULT STDMETHODCALLTYPE Indicate(LONG lObjectCount, IWbemClassObject __RPC_FAR *__RPC_FAR * apObjArray)
    {
        //std::wcout << L"Indicated with " << lObjectCount << L" for " << Query()->WMIClassName().c_str() << std::endl;
        SetIndicateFlag();
        for (LONG i = 0; i < lObjectCount; i++)
        {
            try
            {
                COBJECT* p = new COBJECT;
                p->Populate(p->propertyNames, apObjArray[i]);
                AddObject(p);
            }
            catch (HRESULT hres)
            {
                std::wcout << L"Caught hres with " << NumberToHex(hres).c_str() << std::endl;
                throw std::runtime_error(CWBEMObjectSink::Query()->WMIClassName() + std::string(": Error 0x") + NumberToHex(hres));
            }
            catch (...)
            {
                std::wcout << L"Caught exception" << std::endl;
                throw;
            }
        }
        return WBEM_S_NO_ERROR;
    }

    //size_t Count() { return CWBEMObjectSink::Count(); }
    //CWBEMObject* Object(int i) { return CWBEMObjectSink::Object(i); }
    //std::vector<CWBEMObject*>& Objects() { return CWBEMObjectSink::Objects(); }
};
