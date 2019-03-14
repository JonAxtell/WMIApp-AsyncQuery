#include "pch.h"
#include "CWin32PnpEntity.h"

const char* CWin32PnpEntityObject::ObjectName = "Win32_PnpEntity";

const char* CWin32PnpEntityObject::propertyNames[] =
{
    "Availability",
    "Caption",
    "ClassGuid",
    "CompatibleID",
    "ConfigManagerErrorCode",
    "ConfigManagerUserConfig",
    "CreationClassName",
    "Description",
    "DeviceID",
    "ErrorCleared",
    "ErrorDescription",
    "HardwareID",
    "InstallDate",
    "LastErrorCode",
    "Manufacturer",
    "Name",
    "PNPClass",
    "PNPDeviceID",
    "PowerManagementCapabilities",
    "PowerManagementSupported",
    "Present",
    "Service",
    "Status",
    "StatusInfo",
    "SystemCreationClassName",
    "SystemName",
    NULL
};
