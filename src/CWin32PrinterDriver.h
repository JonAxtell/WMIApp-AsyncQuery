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
class CWin32PrinterDriverObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Caption,
        PROP_ConfigFile,
        PROP_CreationClassName,
        PROP_DataFile,
        PROP_DefaultDataType,
        PROP_DependentFiles,
        PROP_Description,
        PROP_DriverPath,
        PROP_FilePath,
        PROP_HelpFile,
        PROP_InfName,
        PROP_InstallDate,
        PROP_MonitorName,
        PROP_Name,
        PROP_OEMUrl,
        PROP_Started,
        PROP_StartMode,
        PROP_Status,
        PROP_SupportedPlatform,
        PROP_SystemCreationClassName,
        PROP_SystemName,
        PROP_Version,
    };

    CWin32PrinterDriverObject() {}
    CWin32PrinterDriverObject(const CWin32PrinterDriverObject&) = default;
    CWin32PrinterDriverObject(CWin32PrinterDriverObject&&) = default;
    ~CWin32PrinterDriverObject() {}
    CWin32PrinterDriverObject& operator=(const CWin32PrinterDriverObject&) = default;
    CWin32PrinterDriverObject& operator=(CWin32PrinterDriverObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
