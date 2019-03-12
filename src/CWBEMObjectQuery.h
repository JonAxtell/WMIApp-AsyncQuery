#pragma once

#include "CWBEMObject.h"
#include "CVariant.h"
#include <string>

class CWBEMObjectSink;

//#################################################################################################################################
//
// Base class that performs the query on the WBEM sub system to retrieve data on an object. It handles the sending
// of the query and providing the sink that is the callback for notification of the completion of the query.
//
// Classes based on this class must provide the WMI class name which is part of the WQL select statement and 
// a pointer to the sink object that will handle the receiving of the data. The query is sent to a WBEM service
// object that has been created in the COM system.
//
class CWBEMObjectQuery
{
public:
    CWBEMObjectQuery(::IWbemServices *pSvc, const std::string wmiClassName, CWBEMObjectSink* sink);
    virtual ~CWBEMObjectQuery();

    ::IWbemServices* Service() { return _svc; }
    const std::string& WMIClassName() { return _wmiClassName; }
    CWBEMObjectSink* Sink() { return _sink; }

    void Query();
    bool IsDone() const;
    bool HasIndicated() const;

private:
    CWBEMObjectQuery(const CWBEMObjectQuery&) = delete;
    CWBEMObjectQuery& operator=(const CWBEMObjectQuery&) = delete;

    std::string _wmiClassName;
    ::IWbemServices* _svc;
    CWBEMObjectSink* _sink;
};


//#################################################################################################################################
//
// Template that instatiates the CWBEMObjectQeury class
//
template<class SINK>
class TWBEMObjectQuery : public CWBEMObjectQuery
{
public:
    TWBEMObjectQuery(::IWbemServices *pSvc, const std::string wmiClassName) : CWBEMObjectQuery(pSvc, wmiClassName, new SINK) { Sink()->SetQuery(this); }
    ~TWBEMObjectQuery() 
    { 
        Service()->CancelAsyncCall(Sink()); 
        Sink()->Release(); 
    }

private:
    TWBEMObjectQuery(const TWBEMObjectQuery&) = delete;
    TWBEMObjectQuery& operator=(const TWBEMObjectQuery&) = delete;
};
