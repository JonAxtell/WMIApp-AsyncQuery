#pragma once

#include "pch.h"
#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#include "CWBEMObject.h"
#include "CVariant.h"
#include <string>
#include <vector>

//#################################################################################################################################
//
class CWin32PnpEntityObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Availability,
        PROP_Caption,
        PROP_ClassGuid,
        PROP_CompatibleID,
        PROP_ConfigManagerErrorCode,
        PROP_ConfigManagerUserConfig,
        PROP_CreationClassName,
        PROP_Description,
        PROP_DeviceID,
        PROP_ErrorCleared,
        PROP_ErrorDescription,
        PROP_HardwareID,
        PROP_InstallDate,
        PROP_LastErrorCode,
        PROP_Manufacturer,
        PROP_Name,
        PROP_PNPClass,
        PROP_PNPDeviceID,
        PROP_PowerManagementCapabilities,
        PROP_PowerManagementSupported,
        PROP_Present,
        PROP_Service,
        PROP_Status,
        PROP_StatusInfo,
        PROP_SystemCreationClassName,
        PROP_SystemName,
    };

    CWin32PnpEntityObject() {}
    CWin32PnpEntityObject(const CWin32PnpEntityObject&) = default;
    CWin32PnpEntityObject(CWin32PnpEntityObject&&) = default;
    ~CWin32PnpEntityObject() {}
    CWin32PnpEntityObject& operator=(const CWin32PnpEntityObject&) = default;
    CWin32PnpEntityObject& operator=(CWin32PnpEntityObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    CWBEMProperty_Availability Availability() { return (*Properties().at(PROP_Availability)); }
    CWBEMProperty_ConfigManagerErrorCode ConfigManagerErrorCode() { return (*Properties().at(PROP_ConfigManagerErrorCode)); }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }
    std::vector<std::wstring> CompatibleID() { return (*Properties().at(PROP_CompatibleID)).FromArrayBSTR(); }

public:
    static const char* propertyNames[];
};
