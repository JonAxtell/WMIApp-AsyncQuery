#include "pch.h"
#include "CWin32PrintJob.h"

const std::string CWin32PrintJobObject::ObjectName("Win32_PrintJob");

const std::vector<std::string> CWin32PrintJobObject::propertyNames =
{
    "Caption",
    "Description",
    "InstallDate",
    "Name",
    "Status",
    "ElapsedTime",
    "JobStatus",
    "Notify",
    "Owner",
    "Priority",
    "StartTime",
    "TimeSubmitted",
    "UntilTime",
    "Color",
    "DataType",
    "Document",
    "DriverName",
    "HostPrintQueue",
    "JobId",
    "PagesPrinted",
    "PaperLength",
    "PaperSize",
    "PaperWidth",
    "Parameters",
    "PrintProcessor",
    "Size",
    "StatusMask",
    "TotalPages", 
};
