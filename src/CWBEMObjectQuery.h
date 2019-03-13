#pragma once

#include "pch.h"
#include "CWBEMObject.h"
#include "CVariant.h"
#include <string>

class CWBEMObjectSink;

//#################################################################################################################################
//
// Base class that performs the query on the WBEM sub system to retrieve data on an object. It handles the sending
// of the query and referencing the sink that is the callback for notification of the completion of the query.
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
    CWBEMObjectQuery(CWBEMObjectQuery&&) = delete;
    CWBEMObjectQuery& operator=(const CWBEMObjectQuery&) = delete;
    CWBEMObjectQuery& operator=(CWBEMObjectQuery&&) = delete;

    ::IWbemServices* _svc;
    std::string _wmiClassName;
    CWBEMObjectSink* _sink;
};


//#################################################################################################################################
//
// Template that instatiates the CWBEMObjectQeury class
//
// The main purpose of this template it to use the sink parameter which will be template of the sink class with the appropriate
// concrete class as the parameter to the sink class. So all together a link is created between object, query, and sink.
//
template<class SINK>
class TWBEMObjectQuery : public CWBEMObjectQuery
{
public:
    TWBEMObjectQuery(::IWbemServices *pSvc, const std::string wmiClassName) : CWBEMObjectQuery(pSvc, wmiClassName, new SINK) { Sink()->SetQuery(this); Sink()->AddRef(); }
    TWBEMObjectQuery(const TWBEMObjectQuery&) = delete;
    TWBEMObjectQuery(TWBEMObjectQuery&&) = delete;
    ~TWBEMObjectQuery() { Sink()->Release(); }
    TWBEMObjectQuery& operator=(const TWBEMObjectQuery&) = delete;
    TWBEMObjectQuery& operator=(TWBEMObjectQuery&&) = delete;
};
