#include "pch.h"
#include "CWin32PrinterConfiguration.h"

const char* CWin32PrinterConfigurationObject::ObjectName = "Win32_PrinterConfiguration";

const char* CWin32PrinterConfigurationObject::propertyNames[] =
{
    "Caption",
    "Description",
    "SettingID",
    "BitsPerPel",
    "Collate",
    "Color",
    "Copies",
    "DeviceName",
    "DisplayFlags",
    "DisplayFrequency",
    "DitherType",
    "DriverVersion",
    "Duplex",
    "FormName",
    "HorizontalResolution",
    "ICMIntent",
    "ICMMethod",
    "LogPixels",
    "MediaType",
    "Name",
    "Orientation",
    "PaperLength",
    "PaperSize",
    "PaperWidth",
    "PelsHeight",
    "PelsWidth",
    "PrintQuality",
    "Scale",
    "SpecificationVersion",
    "TTOption",
    "VerticalResolution",
    "XResolution",
    "YResolution",
    NULL
};
