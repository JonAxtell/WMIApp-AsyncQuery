#pragma once

#include "pch.h"
#include "CVariant.h"

class CWBEMProperty : public CVariant
{
public:
    CWBEMProperty() : CVariant() {}
    CWBEMProperty(const CWBEMProperty& variant) : CVariant(variant) {}
    CWBEMProperty(CWBEMProperty&& variant) : CVariant(variant) {}
    CWBEMProperty(const CVariant& variant) : CVariant(variant) {}
    CWBEMProperty(CVariant&& variant) : CVariant(variant) {}
    CWBEMProperty(const VARIANT& variant) : CVariant(variant) {}
    CWBEMProperty(VARIANT&& variant) : CVariant(variant) {}
    ~CWBEMProperty() {}
    CWBEMProperty& operator=(CWBEMProperty v)
    {
        (CVariant)*this = (const CVariant)v;
        return *this;
    }
    CWBEMProperty& operator=(CWBEMProperty&& v)
    {
        (CVariant)*this = (const CVariant)v;
        return *this;
    }

    // Public swap function for use in move operations
    friend void swap(CWBEMProperty& first, CWBEMProperty& second)
    {
        using std::swap;

        swap(first, second);
    }
};

// Property common to many objects
class CWBEMProperty_Availability : public CWBEMProperty
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
    CWBEMProperty_Availability() : CWBEMProperty() {}
    CWBEMProperty_Availability(const CWBEMProperty_Availability& variant) : CWBEMProperty(variant) {}
    CWBEMProperty_Availability(CWBEMProperty_Availability&& variant) : CWBEMProperty(variant) {}
    CWBEMProperty_Availability(const CVariant& variant) : CWBEMProperty(variant) {}
    CWBEMProperty_Availability(CVariant&& variant) : CWBEMProperty(variant) {}
    ~CWBEMProperty_Availability() {}
    CWBEMProperty_Availability& operator=(const CWBEMProperty_Availability& v)
    {
        *this = v;
        return *this;
    }
    CWBEMProperty_Availability& operator=(CWBEMProperty_Availability&& v)
    {
        *this = v;
        return *this;
    }

    friend std::wostream& operator<<(std::wostream& os, const CWBEMProperty_Availability& v);

    operator std::string() { return Text(); }

    const std::string Text() const { return std::string(_values[this->FromI4()]); }
    uint32_t Value() const { return this->FromI4(); }

private:
    static const char* _values[];
};

// Property common to many objects
class CWBEMProperty_ConfigManagerErrorCode : public CWBEMProperty
{
public:
    CWBEMProperty_ConfigManagerErrorCode() : CWBEMProperty() {}
    CWBEMProperty_ConfigManagerErrorCode(const CWBEMProperty_ConfigManagerErrorCode& variant) : CWBEMProperty(variant) {}
    CWBEMProperty_ConfigManagerErrorCode(CWBEMProperty_ConfigManagerErrorCode&& variant) : CWBEMProperty(variant) {}
    CWBEMProperty_ConfigManagerErrorCode(const CVariant& variant) : CWBEMProperty(variant) {}
    CWBEMProperty_ConfigManagerErrorCode(CVariant&& variant) : CWBEMProperty(variant) {}
    ~CWBEMProperty_ConfigManagerErrorCode() {}
    CWBEMProperty_ConfigManagerErrorCode& operator=(const CWBEMProperty_ConfigManagerErrorCode& v)
    {
        *this = v;
        return *this;
    }
    CWBEMProperty_ConfigManagerErrorCode& operator=(CWBEMProperty_ConfigManagerErrorCode&& v)
    {
        *this = v;
        return *this;
    }

    friend std::wostream& operator<<(std::wostream& os, const CWBEMProperty_ConfigManagerErrorCode& f);

    const std::string Text() const { return std::string(_values[this->FromI4()]); }
    uint32_t Value() const { return this->FromI4(); }

private:
    static const char* _values[];
};
