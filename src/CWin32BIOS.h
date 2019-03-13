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
class CWin32BIOSObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_BiosCharacteristics,
        PROP_BIOSVersion,
        PROP_BuildNumber,
        PROP_Caption,
        PROP_CodeSet,
        PROP_CurrentLanguage,
        PROP_Description,
        PROP_EmbeddedControllerMajorVersion,
        PROP_EmbeddedControllerMinorVersion,
        PROP_IdentificationCode,
        PROP_InstallableLanguages,
        PROP_InstallDate,
        PROP_LanguageEdition,
        PROP_ListOfLanguages,
        PROP_Manufacturer,
        PROP_Name,
        PROP_OtherTargetOS,
        PROP_PrimaryBIOS,
        PROP_ReleaseDate,
        PROP_SerialNumber,
        PROP_SMBIOSBIOSVersion,
        PROP_SMBIOSMajorVersion,
        PROP_SMBIOSMinorVersion,
        PROP_SMBIOSPresent,
        PROP_SoftwareElementID,
        PROP_SoftwareElementState,
        PROP_Status,
        PROP_SystemBiosMajorVersion,
        PROP_SystemBiosMinorVersion,
        PROP_TargetOperatingSystem,
        PROP_Version,
    };

    CWin32BIOSObject() {}
    CWin32BIOSObject(const CWin32BIOSObject&) = default;
    CWin32BIOSObject(CWin32BIOSObject&&) = default;
    ~CWin32BIOSObject() {}
    CWin32BIOSObject& operator=(const CWin32BIOSObject&) = default;
    CWin32BIOSObject& operator=(CWin32BIOSObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
