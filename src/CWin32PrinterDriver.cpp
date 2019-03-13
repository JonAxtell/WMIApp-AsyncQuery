#include "pch.h"
#include "CWin32PrinterDriver.h"

const char* CWin32PrinterDriverObject::ObjectName = "Win32_PrinterDriver";

const char* CWin32PrinterDriverObject::propertyNames[] =
{
    "Caption",
    "ConfigFile",
    "CreationClassName",
    "DataFile",
    "DefaultDataType",
    "DependentFiles",
    "Description",
    "DriverPath",
    "FilePath",
    "HelpFile",
    "InfName",
    "InstallDate",
    "MonitorName",
    "Name",
    "OEMUrl",
    "Started",
    "StartMode",
    "Status",
    "SupportedPlatform",
    "SystemCreationClassName",
    "SystemName",
    "Version",
    NULL
};
