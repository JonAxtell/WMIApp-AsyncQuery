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
    hResult;
    strParam;
    pObjParam;
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
