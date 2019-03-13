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
class CWin32PrinterConfigurationObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Caption,
        PROP_Description,
        PROP_SettingID,
        PROP_BitsPerPel,
        PROP_Collate,
        PROP_Color,
        PROP_Copies,
        PROP_DeviceName,
        PROP_DisplayFlags,
        PROP_DisplayFrequency,
        PROP_DitherType,
        PROP_DriverVersion,
        PROP_Duplex,
        PROP_FormName,
        PROP_HorizontalResolution,
        PROP_ICMIntent,
        PROP_ICMMethod,
        PROP_LogPixels,
        PROP_MediaType,
        PROP_Name,
        PROP_Orientation,
        PROP_PaperLength,
        PROP_PaperSize,
        PROP_PaperWidth,
        PROP_PelsHeight,
        PROP_PelsWidth,
        PROP_PrintQuality,
        PROP_Scale,
        PROP_SpecificationVersion,
        PROP_TTOption,
        PROP_VerticalResolution,
        PROP_XResolution,
        PROP_YResolution,
    };

    CWin32PrinterConfigurationObject() {}
    CWin32PrinterConfigurationObject(const CWin32PrinterConfigurationObject&) = default;
    CWin32PrinterConfigurationObject(CWin32PrinterConfigurationObject&&) = default;
    ~CWin32PrinterConfigurationObject() {}
    CWin32PrinterConfigurationObject& operator=(const CWin32PrinterConfigurationObject&) = default;
    CWin32PrinterConfigurationObject& operator=(CWin32PrinterConfigurationObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
