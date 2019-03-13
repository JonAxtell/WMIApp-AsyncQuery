#include "pch.h"
#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"

//#################################################################################################################################
//
ULONG CWBEMObjectSink::AddRef()
{
    return ::InterlockedIncrement(&_refCount);
}

//#################################################################################################################################
//
ULONG CWBEMObjectSink::Release()
{
    LONG lRef = ::InterlockedDecrement(&_refCount);
    if (lRef == 0)
    {
        delete this;
    }
    return lRef;
}

//#################################################################################################################################
//
HRESULT CWBEMObjectSink::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown || riid == IID_IWbemObjectSink)
    {
        *ppv = (IWbemObjectSink *)this;
        AddRef();
        return WBEM_S_NO_ERROR;
    }
    return E_NOINTERFACE;
}

//#################################################################################################################################
//
void CWBEMObjectSink::SetIndicateFlag()
{
    ::EnterCriticalSection(&threadLock);
    _indicatedFlag = true;
    ::LeaveCriticalSection(&threadLock);
}

//#################################################################################################################################
//
HRESULT STDMETHODCALLTYPE CWBEMObjectSink::SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject __RPC_FAR *pObjParam)
{
    //std::wcout << L"Set status for " << Query()->WMIClassName().c_str() << L" to " << lFlags << std::endl;
    hResult = hResult;
    strParam = strParam;
    pObjParam = pObjParam;
    if (lFlags == WBEM_STATUS_COMPLETE)
    {
        ::EnterCriticalSection(&threadLock);
        _doneFlag = true;
        ::LeaveCriticalSection(&threadLock);
    }
    else if (lFlags == WBEM_STATUS_PROGRESS)
    {
        std::wcout << L"Call in progress" << std::endl;
    }
    else
    {
        std::wcout << L"Flags is " << lFlags << std::endl;
    }
    return WBEM_S_NO_ERROR;
}

//#################################################################################################################################
//
bool CWBEMObjectSink::IsDone()
{
    bool done = true;

    ::EnterCriticalSection(&threadLock);
    done = _doneFlag;
    ::LeaveCriticalSection(&threadLock);

    return done;
}

//#################################################################################################################################
//
bool CWBEMObjectSink::HasIndicated()
{
    bool indicated = true;

    ::EnterCriticalSection(&threadLock);
    indicated = _indicatedFlag;
    ::LeaveCriticalSection(&threadLock);

    return indicated;
}
