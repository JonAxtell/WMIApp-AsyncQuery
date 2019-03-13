#pragma once

#include "pch.h"
#include "CWBEMObject.h"
#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#include <string>

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
