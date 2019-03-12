#pragma once

#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#include "CWBEMObject.h"
#include "CVariant.h"
#include <string>
#include <vector>

//#################################################################################################################################
//
class CWin32OperatingSystemObject : public CWBEMObject
{
public:
    static const std::string ObjectName;
    
    enum propertyEnum
    {
        PROP_BootDevice,
        PROP_BuildNumber,
        PROP_BuildType,
        PROP_Caption,
        PROP_CodeSet,
        PROP_CountryCode,
        PROP_CreationClassName,
        PROP_CSCreationClassName,
        PROP_CSDVersion,
        PROP_CSName,
        PROP_CurrentTimeZone,
        PROP_DataExecutionPrevention_Available,
        PROP_DataExecutionPrevention_32BitApplications,
        PROP_DataExecutionPrevention_Drivers,
        PROP_DataExecutionPrevention_SupportPolicy,
        PROP_Debug,
        PROP_Description,
        PROP_Distributed,
        PROP_EncryptionLevel,
        PROP_ForegroundApplicationBoost,
        PROP_FreePhysicalMemory,
        PROP_FreeSpaceInPagingFiles,
        PROP_FreeVirtualMemory,
        PROP_InstallDate,
        PROP_LargeSystemCache,
        PROP_LastBootUpTime,
        PROP_LocalDateTime,
        PROP_Locale,
        PROP_Manufacturer,
        PROP_MaxNumberOfProcesses,
        PROP_MaxProcessMemorySize,
        PROP_MUILanguages,
        PROP_Name,
        PROP_NumberOfLicensedUsers,
        PROP_NumberOfProcesses,
        PROP_NumberOfUsers,
        PROP_OperatingSystemSKU,
        PROP_Organization,
        PROP_OSArchitecture,
        PROP_OSLanguage,
        PROP_OSProductSuite,
        PROP_OSType,
        PROP_OtherTypeDescription,
        PROP_PAEEnabled,
        PROP_PlusProductID,
        PROP_PlusVersionNumber,
        PROP_PortableOperatingSystem,
        PROP_Primary,
        PROP_ProductType,
        PROP_QuantumLength,
        PROP_QuantumType,
        PROP_RegisteredUser,
        PROP_SerialNumber,
        PROP_ServicePackMajorVersion,
        PROP_ServicePackMinorVersion,
        PROP_SizeStoredInPagingFiles,
        PROP_Status,
        PROP_SuiteMask,
        PROP_SystemDevice,
        PROP_SystemDirectory,
        PROP_SystemDrive,
        PROP_TotalSwapSpaceSize,
        PROP_TotalVirtualMemorySize,
        PROP_TotalVisibleMemorySize,
        PROP_Version,
        PROP_WindowsDirectory,
    };

    CWin32OperatingSystemObject() {}
    CWin32OperatingSystemObject(const CWin32OperatingSystemObject&) = default;
    ~CWin32OperatingSystemObject() {}
    CWin32OperatingSystemObject& operator=(const CWin32OperatingSystemObject&) = default;

    std::shared_ptr<CVariant>  Property(int prop) { return Properties().at(prop); }

    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }

public:
    static const std::vector<std::string> propertyNames;
};
