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
    _sink->Release();
}

//#################################################################################################################################
//
void CWBEMObjectQuery::Query()
{
    std::wstring select = L"SELECT * FROM ";
    select.append(_wmiClassName.begin(), _wmiClassName.end());
    HRESULT hres = _svc->ExecQueryAsync(bstr_t("WQL"),              // Query language
                                        BSTR(select.c_str()),       // Query
                                        WBEM_FLAG_BIDIRECTIONAL,    // Flags
                                        NULL,                       // Context
                                        Sink());                    // Response handle
    if (FAILED(hres))
    {
        _sink->Release();
        throw std::runtime_error(std::string("CWBEMObjectQuery::Query ") + _wmiClassName + std::string(" failed. Error code = 0x") + NumberToHex(hres));
    }
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
