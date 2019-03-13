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
class CWin32ProcessObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_CreationClassName,
        PROP_Caption,
        PROP_CommandLine,
        PROP_CreationDate,
        PROP_CSCreationClassName,
        PROP_CSName,
        PROP_Description,
        PROP_ExecutablePath,
        PROP_ExecutionState,
        PROP_Handle,
        PROP_HandleCount,
        PROP_InstallDate,
        PROP_KernelModeTime,
        PROP_MaximumWorkingSetSize,
        PROP_MinimumWorkingSetSize,
        PROP_Name,
        PROP_OSCreationClassName,
        PROP_OSName,
        PROP_OtherOperationCount,
        PROP_OtherTransferCount,
        PROP_PageFaults,
        PROP_PageFileUsage,
        PROP_ParentProcessId,
        PROP_PeakPageFileUsage,
        PROP_PeakVirtualSize,
        PROP_PeakWorkingSetSize,
        PROP_Priority,
        PROP_PrivatePageCount,
        PROP_ProcessId,
        PROP_QuotaNonPagedPoolUsage,
        PROP_QuotaPagedPoolUsage,
        PROP_QuotaPeakNonPagedPoolUsage,
        PROP_QuotaPeakPagedPoolUsage,
        PROP_ReadOperationCount,
        PROP_ReadTransferCount,
        PROP_SessionId,
        PROP_Status,
        PROP_TerminationDate,
        PROP_ThreadCount,
        PROP_UserModeTime,
        PROP_VirtualSize,
        PROP_WindowsVersion,
        PROP_WorkingSetSize,
        PROP_WriteOperationCount,
        PROP_WriteTransferCount,
    };

    CWin32ProcessObject() {}
    CWin32ProcessObject(const CWin32ProcessObject&) = default;
    CWin32ProcessObject(CWin32ProcessObject&&) = default;
    ~CWin32ProcessObject() {}
    CWin32ProcessObject& operator=(const CWin32ProcessObject&) = default;
    CWin32ProcessObject& operator=(CWin32ProcessObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    uint16_t ExecutionState() { return (*Properties().at(PROP_ExecutionState)).FromI4(); }
    uint16_t HandleCount() { return (*Properties().at(PROP_HandleCount)).FromI4(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }
    uint16_t ProcessId() { return (*Properties().at(PROP_ProcessId)).FromI4(); }

public:
    static const char* propertyNames[];
};
