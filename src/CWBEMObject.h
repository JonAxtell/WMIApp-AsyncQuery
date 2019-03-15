#pragma once

#include "pch.h"
#include "CVariant.h"
#include "CWBEMProperty.h"
#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#ifndef __MINGW_GCC_VERSION
#pragma comment(lib, "wbemuuid.lib")
#endif
#include <vector>
#include <memory>

//#################################################################################################################################
//
// Class that encapsulates the process of retrieving a data set from the WBEM sub system in Windows and storing it 
// in a vector of variants.
//
// A WBEM object is something like the Operating System or a Printer or a Process. Each object can have many properties from
// common ones like a description to properties tied to the object such as stepping model for a processor. A system can
// have either single objects (a single OS) or multiple ones (multiple printers).
//
class CWBEMObject
{
public:
    // Default constructor
    CWBEMObject() {}

    // Copy constructor (does a deep copy of the whole vector)
    CWBEMObject(const CWBEMObject& other)
    {
        for (auto p : other._properties)
        {
            _properties.push_back(p);
        }
    }

    // Move constructor (just transfers the vector)
    CWBEMObject(CWBEMObject&& other)
    {
        _properties = other._properties;
        other._properties.clear();
    }

    // Destructor, deletes all objects in the vector
    virtual ~CWBEMObject()
    {
        for (std::vector<CWBEMProperty*>::iterator p = _properties.begin(); p != _properties.end(); ++p)
        {
            delete (*p);
            (*p) = nullptr;
        }
        _properties.clear();
    }

    // Copy assignment (does a deep copy of the whole vector)
    CWBEMObject& operator=(const CWBEMObject& other)
    {
        for (auto p : other._properties)
        {
            _properties.push_back(p);
        }
        return *this;
    }

    // Move assignment (just transfers the vector)
    CWBEMObject& operator=(CWBEMObject&& other)
    {
        _properties = other._properties;
        other._properties.clear();
        return *this;
    }

    // Public swap function for use in move operations
    friend void swap(CWBEMObject& first, CWBEMObject& second)
    {
        using std::swap;

        swap(first, second);
    }

    // Method that gets the properties from the service and places them in the _properties array
    virtual void Populate(const char** propertyNames, IWbemClassObject __RPC_FAR * pwbemObj);

    // Methods to access the properties
    const std::vector<CWBEMProperty* >& Properties() const { return _properties; }
    const CVariant Property(int prop) const { return (*Properties().at(prop)); }

    // Methdos to access details about the properties
    virtual const char* PropertyName(int prop) = 0;
    unsigned int PropertyCount()
    {
        if (_propertyCount == 0)
        {
            // If count is zero, assume that the list of property names in the derived class hasn't been scanned yet.
            // This is done here rather because you can't call a method in a derived class from a virtual base class's constructor.
            while (PropertyName(_propertyCount++))
            {
            }
            --_propertyCount;
        }
        return _propertyCount; 
    }

private:
    unsigned int _propertyCount{ 0 };
    std::vector<CWBEMProperty* > _properties;
};
