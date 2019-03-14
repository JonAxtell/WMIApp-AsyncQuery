#pragma once

#include "pch.h"
#include "CVariant.h"
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

    // Property common to many objects
    class CAvailability
    {
    public:
        enum valueEnum
        {
            AVAIL_OTHER = 1,
            AVAIL_UNKNOWN = 2,
            AVAIL_RUNNING = 3,
            AVAIL_WARNING = 4,
            AVAIL_INTEST = 5,
            AVAIL_NOTAPPLICABLE = 6,
            AVAIL_POWEROFF = 7,
            AVAIL_OFFLINE = 8,
            AVAIL_OFFDUTY = 9,
            AVAIL_DEGRADED = 10,
            AVAIL_NOTINSTALLED = 11,
            AVAIL_INSTALLERROR = 12,
            AVAIL_POWERSAVE_UNKNOWN = 13,       // The device is known to be in a power save state, but its exact status is unknown.
            AVAIL_POWERSAVE_LOWPOWERMODE = 14,  // The device is in a power save state, but is still functioning, and may exhibit decreased performance.
            AVAIL_POWERSAVE_STANDBY = 15,       // The device is not functioning, but can be brought to full power quickly.
            AVAIL_POWERCYCLE = 16,
            AVAIL_POWERSAVE_WARNING = 17,       // The device is in a warning state, though also in a power save state.
            AVAIL_PAUSED = 18,                  // The device is paused.
            AVAIL_NOTREADY = 19,                // The device is not ready.
            AVAIL_NOTCONFIGURED = 20,           // The device is not configured.
            AVAIL_QUIESCED = 21,
        };
        CAvailability(uint32_t avail) : _avail(avail) {}
        ~CAvailability() {}

        friend std::wostream& operator<<(std::wostream& os, const CAvailability& v);

        const std::string Text() const { return std::string(_availabilityValues[_avail]); }
        uint32_t Value() const { return _avail; }

    private:
        uint32_t _avail;
    };

    // Property common to many objects
    class CConfigManagerErrorCode
    {
    public:
        CConfigManagerErrorCode(uint32_t error) : _error(error) {}
        ~CConfigManagerErrorCode() {}

        friend std::wostream& operator<<(std::wostream& os, const CConfigManagerErrorCode& f);

        const std::string Text() const { return std::string(_configManagerErrorCodeValues[_error]); }
        uint32_t Value() const { return _error; }

    private:
        uint32_t _error;
    };

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
        for (std::vector<CVariant*>::iterator p = _properties.begin(); p != _properties.end(); ++p)
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

    // Method that gets the properties from the service and places them in the _properties array
    virtual void Populate(const char** propertyNames, IWbemClassObject __RPC_FAR * pwbemObj);

    // Methods to access the properties
    const std::vector<CVariant* >& Properties() const { return _properties; }
    const CVariant* Property(int prop) const { return Properties().at(prop); }
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
    std::vector<CVariant* > _properties;

    static const char* _availabilityValues[];
    static const char* _configManagerErrorCodeValues[];
};
