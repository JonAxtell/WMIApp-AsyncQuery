#pragma once

#include "pch.h"
#include "CWBEMProperty.h"
#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#include "CWBEMObject.h"
#include "CVariant.h"
#include <ostream>
#include <string>
#include <stdlib.h>

//#################################################################################################################################
//
class CWin32USBControllerObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Availability,
        PROP_Caption,
        PROP_ConfigManagerErrorCode,
        PROP_ConfigManagerUserConfig,
        PROP_CreationClassName,
        PROP_Description,
        PROP_DeviceID,
        PROP_ErrorCleared,
        PROP_ErrorDescription,
        PROP_InstallDate,
        PROP_LastErrorCode,
        PROP_Manufacturer,
        PROP_MaxNumberControlled,
        PROP_Name,
        PROP_PNPDeviceID,
        PROP_PowerManagementCapabilities,
        PROP_PowerManagementSupported,
        PROP_ProtocolSupported,
        PROP_Status,
        PROP_StatusInfo,
        PROP_SystemCreationClassName,
        PROP_SystemName,
        PROP_TimeOfLastReset,
    };

    CWin32USBControllerObject() {}
    CWin32USBControllerObject(const CWin32USBControllerObject&) = default;
    CWin32USBControllerObject(CWin32USBControllerObject&&) = default;
    ~CWin32USBControllerObject() {}
    CWin32USBControllerObject& operator=(const CWin32USBControllerObject&) = default;
    CWin32USBControllerObject& operator=(CWin32USBControllerObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    CWBEMProperty_Availability Availability() { return CWBEMProperty_Availability(*(Properties().at(PROP_Availability))); }
    CWBEMProperty_ConfigManagerErrorCode ConfigManagerErrorCode() { return CWBEMProperty_Availability(*(Properties().at(PROP_ConfigManagerErrorCode))); }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring DeviceID() { return (*Properties().at(PROP_DeviceID)).FromBSTR(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }
    std::wstring PNPDeviceID() { return (*Properties().at(PROP_PNPDeviceID)).FromBSTR(); }

public:
    static const char* propertyNames[];

private:
};
