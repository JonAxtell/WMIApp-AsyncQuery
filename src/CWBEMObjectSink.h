#pragma once

#include "pch.h"
#include "CWBEMObject.h"
#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#ifndef __MINGW_GCC_VERSION
#pragma comment(lib, "wbemuuid.lib")
#endif

class CWBEMObjectQuery;

//#################################################################################################################################
//
class CWBEMObjectSink : public IWbemObjectSink
{
public:
    CWBEMObjectSink()
    {
        _refCount = 0;
        _doneFlag = false;
        _indicatedFlag = false;
        ::InitializeCriticalSection(&threadLock);
        _query = nullptr;
        //AddRef();
    }
    virtual ~CWBEMObjectSink()
    {
        // Objects in vector aren't deleted as they are owned by the TWBEMObjects class after all the properties have been retrieved.
        _objects.clear();
        ::DeleteCriticalSection(&threadLock);
    }

    // COM methods
    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

    // IWbemObjectSink methods
    virtual HRESULT STDMETHODCALLTYPE Indicate(LONG lObjectCount, IWbemClassObject __RPC_FAR *__RPC_FAR * apObjArray) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject __RPC_FAR *pObjParam);

    size_t Count() { return _objects.size(); }
    CWBEMObject* Object(int i) { return _objects.at(i); }
    std::vector<CWBEMObject*>& Objects() { return _objects; }
    void AddObject(CWBEMObject* obj) { _objects.push_back(obj); }

    void SetQuery(CWBEMObjectQuery *query) { _query = query; }
    CWBEMObjectQuery* Query() { return _query; }

    void SetIndicateFlag();
    bool IsDone();
    bool HasIndicated();

private:
    CWBEMObjectSink(const CWBEMObjectSink&) = delete;
    CWBEMObjectSink(CWBEMObjectSink&&) = delete;
    CWBEMObjectSink& operator=(const CWBEMObjectSink&) = delete;
    CWBEMObjectSink& operator=(CWBEMObjectSink&&) = delete;

    LONG _refCount;
    bool _doneFlag;
    bool _indicatedFlag;
    CRITICAL_SECTION threadLock; // for thread safety
    CWBEMObjectQuery* _query;

    std::vector<CWBEMObject*> _objects;
};

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
