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
class CWin32PrinterObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Attributes,
        PROP_Availability,
        PROP_AvailableJobSheets,
        PROP_AveragePagesPerMinute,
        PROP_Capabilities,
        PROP_CapabilityDescriptions,
        PROP_Caption,
        PROP_CharSetsSupported,
        PROP_Comment,
        PROP_ConfigManagerErrorCode,
        PROP_ConfigManagerUserConfig,
        PROP_CreationClassName,
        PROP_CurrentCapabilities,
        PROP_CurrentCharSet,
        PROP_CurrentLanguage,
        PROP_CurrentMimeType,
        PROP_CurrentNaturalLanguage,
        PROP_CurrentPaperType,
        PROP_Default,
        PROP_DefaultCapabilities,
        PROP_DefaultCopies,
        PROP_DefaultLanguage,
        PROP_DefaultMimeType,
        PROP_DefaultNumberUp,
        PROP_DefaultPaperType,
        PROP_DefaultPriority,
        PROP_Description,
        PROP_DetectedErrorState,
        PROP_DeviceID,
        PROP_Direct,
        PROP_DoCompleteFirst,
        PROP_DriverName,
        PROP_EnableBIDI,
        PROP_EnableDevQueryPrint,
        PROP_ErrorCleared,
        PROP_ErrorDescription,
        PROP_ErrorInformation,
        PROP_ExtendedDetectedErrorState,
        PROP_ExtendedPrinterStatus,
        PROP_Hidden,
        PROP_HorizontalResolution,
        PROP_InstallDate,
        PROP_JobCountSinceLastReset,
        PROP_KeepPrintedJobs,
        PROP_LanguagesSupported,
        PROP_LastErrorCode,
        PROP_Local,
        PROP_Location,
        PROP_MarkingTechnology,
        PROP_MaxCopies,
        PROP_MaxNumberUp,
        PROP_MaxSizeSupported,
        PROP_MimeTypesSupported,
        PROP_Name,
        PROP_NaturalLanguagesSupported,
        PROP_Network,
        PROP_PaperSizesSupported,
        PROP_PaperTypesAvailable,
        PROP_Parameters,
        PROP_PNPDeviceID,
        PROP_PortName,
        PROP_PowerManagementCapabilities,
        PROP_PowerManagementSupported,
        PROP_PrinterPaperNames,
        PROP_PrinterState,
        PROP_PrinterStatus,
        PROP_PrintJobDataType,
        PROP_PrintProcessor,
        PROP_Priority,
        PROP_Published,
        PROP_Queued,
        PROP_RawOnly,
        PROP_SeparatorFile,
        PROP_ServerName,
        PROP_Shared,
        PROP_ShareName,
        PROP_SpoolEnabled,
        PROP_StartTime,
        PROP_Status,
        PROP_StatusInfo,
        PROP_SystemCreationClassName,
        PROP_SystemName,
        PROP_TimeOfLastReset,
        PROP_UntilTime,
        PROP_VerticalResolution,
        PROP_WorkOffline,
    };

    CWin32PrinterObject() {}
    CWin32PrinterObject(const CWin32PrinterObject&) = default;
    CWin32PrinterObject(CWin32PrinterObject&&) = default;
    ~CWin32PrinterObject() {}
    CWin32PrinterObject& operator=(const CWin32PrinterObject&) = default;
    CWin32PrinterObject& operator=(CWin32PrinterObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
