#include "pch.h"
#include "CWin32Printer.h"

const char* CWin32PrinterObject::ObjectName = "Win32_Printer";

const char* CWin32PrinterObject::propertyNames[] =
{
    "Attributes",
    "Availability",
    "AvailableJobSheets",
    "AveragePagesPerMinute",
    "Capabilities",
    "CapabilityDescriptions",
    "Caption",
    "CharSetsSupported",
    "Comment",
    "ConfigManagerErrorCode",
    "ConfigManagerUserConfig",
    "CreationClassName",
    "CurrentCapabilities",
    "CurrentCharSet",
    "CurrentLanguage",
    "CurrentMimeType",
    "CurrentNaturalLanguage",
    "CurrentPaperType",
    "Default",
    "DefaultCapabilities",
    "DefaultCopies",
    "DefaultLanguage",
    "DefaultMimeType",
    "DefaultNumberUp",
    "DefaultPaperType",
    "DefaultPriority",
    "Description",
    "DetectedErrorState",
    "DeviceID",
    "Direct",
    "DoCompleteFirst",
    "DriverName",
    "EnableBIDI",
    "EnableDevQueryPrint",
    "ErrorCleared",
    "ErrorDescription",
    "ErrorInformation",
    "ExtendedDetectedErrorState",
    "ExtendedPrinterStatus",
    "Hidden",
    "HorizontalResolution",
    "InstallDate",
    "JobCountSinceLastReset",
    "KeepPrintedJobs",
    "LanguagesSupported",
    "LastErrorCode",
    "Local",
    "Location",
    "MarkingTechnology",
    "MaxCopies",
    "MaxNumberUp",
    "MaxSizeSupported",
    "MimeTypesSupported",
    "Name",
    "NaturalLanguagesSupported",
    "Network",
    "PaperSizesSupported",
    "PaperTypesAvailable",
    "Parameters",
    "PNPDeviceID",
    "PortName",
    "PowerManagementCapabilities",
    "PowerManagementSupported",
    "PrinterPaperNames",
    "PrinterState",
    "PrinterStatus",
    "PrintJobDataType",
    "PrintProcessor",
    "Priority",
    "Published",
    "Queued",
    "RawOnly",
    "SeparatorFile",
    "ServerName",
    "Shared",
    "ShareName",
    "SpoolEnabled",
    "StartTime",
    "Status",
    "StatusInfo",
    "SystemCreationClassName",
    "SystemName",
    "TimeOfLastReset",
    "UntilTime",
    "VerticalResolution",
    "WorkOffline",
    NULL
};
