#pragma once

#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#include "CWBEMObject.h"
#include "CVariant.h"
#include <string>
#include <vector>

//#################################################################################################################################
//
class CWin32PrintJobObject : public CWBEMObject
{
public:
    static const std::string ObjectName;

    enum propertyEnum
    {
        PROP_Caption,
        PROP_Description,
        PROP_InstallDate,
        PROP_Name,
        PROP_Status,
        PROP_ElapsedTime,
        PROP_JobStatus,
        PROP_Notify,
        PROP_Owner,
        PROP_Priority,
        PROP_StartTime,
        PROP_TimeSubmitted,
        PROP_UntilTime,
        PROP_Color,
        PROP_DataType,
        PROP_Document,
        PROP_DriverName,
        PROP_HostPrintQueue,
        PROP_JobId,
        PROP_PagesPrinted,
        PROP_PaperLength,
        PROP_PaperSize,
        PROP_PaperWidth,
        PROP_Parameters,
        PROP_PrintProcessor,
        PROP_Size,
        PROP_StatusMask,
        PROP_TotalPages,
    };

    CWin32PrintJobObject() {}
    CWin32PrintJobObject(const CWin32PrintJobObject&) = default;
    ~CWin32PrintJobObject() {}
    CWin32PrintJobObject& operator=(const CWin32PrintJobObject&) = default;

    std::shared_ptr<CVariant>  Property(int prop) { return Properties().at(prop); }

    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }

public:
    static const std::vector<std::string> propertyNames;
};
