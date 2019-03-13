#include "pch.h"
#include "CWBEMObjectQuery.h"
#include "CWBEMObjectSink.h"

//#################################################################################################################################
//
CWBEMObjectQuery::CWBEMObjectQuery(::IWbemServices *pSvc, const std::string wmiClassName, CWBEMObjectSink* sink) :
        _svc(pSvc), 
        _wmiClassName(wmiClassName), 
        _sink(sink)
{
}

//#################################################################################################################################
//
CWBEMObjectQuery::~CWBEMObjectQuery()
{
    _svc->CancelAsyncCall(_sink);
    _sink->Release();
}

//#################################################################################################################################
//
void CWBEMObjectQuery::Query()
{
    std::wstring select = L"SELECT * FROM ";
    select.append(_wmiClassName.begin(), _wmiClassName.end());
    BSTR wql;
    wql = ConvertStringToBSTR("WQL");
    HRESULT hres = _svc->ExecQueryAsync(wql,                        // Query language
                                        BSTR(select.c_str()),       // Query
                                        WBEM_FLAG_BIDIRECTIONAL,    // Flags
                                        NULL,                       // Context
                                        Sink());                    // Response handle
    if (FAILED(hres))
    {
        _sink->Release();
        throw std::runtime_error(std::string("CWBEMObjectQuery::Query ") + _wmiClassName + std::string(" failed. Error code = 0x") + NumberToHex(hres));
    }
    ::SysFreeString(wql);
    //std::wcout << L"Query of " << _wmiClassName.c_str() << L" succeeded" << std::endl;
}

//#################################################################################################################################
//
bool CWBEMObjectQuery::IsDone() const
{
    return _sink->IsDone();
}

//#################################################################################################################################
//
bool CWBEMObjectQuery::HasIndicated() const
{
    return _sink->HasIndicated();
}
