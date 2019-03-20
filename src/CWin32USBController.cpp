#include "pch.h"
#include "CWin32USBController.h"

const char* CWin32USBControllerObject::ObjectName = "Win32_USBController";

const char* CWin32USBControllerObject::propertyNames[] =
{
    "Availability",
    "Caption",
    "ConfigManagerErrorCode",
    "ConfigManagerUserConfig",
    "CreationClassName",
    "Description",
    "DeviceID",
    "ErrorCleared",
    "ErrorDescription",
    "InstallDate",
    "LastErrorCode",
    "Manufacturer",
    "MaxNumberControlled",
    "Name",
    "PNPDeviceID",
    "PowerManagementCapabilities",
    "PowerManagementSupported",
    "ProtocolSupported",
    "Status",
    "StatusInfo",
    "SystemCreationClassName",
    "SystemName",
    "TimeOfLastReset",
    NULL
};

