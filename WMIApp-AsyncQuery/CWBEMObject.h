#pragma once

#include "CVariant.h"
#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include <vector>

//#################################################################################################################################
//
// Class that encapsulates the process of retrieving a data set from the WBEM sub system in Windows and storing it 
// in a vector of variants.
//
class CWBEMObject
{
public:
    CWBEMObject() {}
    CWBEMObject(const CWBEMObject&) = default;
    virtual ~CWBEMObject() {}
    CWBEMObject& operator=(const CWBEMObject&) = default;
    CWBEMObject& operator=(CWBEMObject&&) = default;

    // Method that gets the properties from the service and places them in the _properties array
    virtual void Populate(const std::vector<std::string>& propertyNames, IWbemClassObject __RPC_FAR * pwbemObj);

    // Methods to access the properties
    const std::vector<std::shared_ptr<CVariant> >& Properties() const { return _properties; }
    const std::shared_ptr<CVariant> Property(int prop) const { return Properties().at(prop); }

private:
    std::vector<std::shared_ptr<CVariant> > _properties;
};

//#################################################################################################################################
//
template<class CWBEMOBJECT>
class TWBEMObjects
{
public:
    TWBEMObjects() {}
    TWBEMObjects(const TWBEMObjects& objs)
    {
        for (auto p : objs._objects)
        {
            _objects.push_back(new CWBEMOBJECT(*p));
        }
    }
    ~TWBEMObjects()
    {
        for (auto o : _objects)
        {
            delete o;
        }
        _objects.clear();
    }
    TWBEMObjects& operator=(const TWBEMObjects& objs) 
    {
        for (auto p : objs._objects)
        {
            _objects.push_back(new CWBEMOBJECT(p));
        }
        return *this;
    }

    CWBEMOBJECT* at(int i) { return _objects.at(i); }
    void push_back(const CWBEMOBJECT& obj) { _objects.push_back(obj); }
    void push_back(CWBEMOBJECT&& obj) { _objects.push_back(&obj); }
    size_t size() { return _objects.size(); }

    std::vector<CWBEMOBJECT* >& Objects() { return _objects; }

private:
    std::vector<CWBEMOBJECT* > _objects;
};