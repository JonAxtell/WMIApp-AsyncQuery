#include "pch.h"
#include "CWin32PrinterConfiguration.h"

const std::string CWin32PrinterConfigurationObject::ObjectName("Win32_PrinterConfiguration");

const std::vector<std::string> CWin32PrinterConfigurationObject::propertyNames =
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
};
