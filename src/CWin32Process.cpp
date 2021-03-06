#include "pch.h"
#include "CWin32Process.h"

const char* CWin32ProcessObject::ObjectName = "Win32_Process";

const char* CWin32ProcessObject::propertyNames[] =
{
    "CreationClassName",
    "Caption",
    "CommandLine",
    "CreationDate",
    "CSCreationClassName",
    "CSName",
    "Description",
    "ExecutablePath",
    "ExecutionState",
    "Handle",
    "HandleCount",
    "InstallDate",
    "KernelModeTime",
    "MaximumWorkingSetSize",
    "MinimumWorkingSetSize",
    "Name",
    "OSCreationClassName",
    "OSName",
    "OtherOperationCount",
    "OtherTransferCount",
    "PageFaults",
    "PageFileUsage",
    "ParentProcessId",
    "PeakPageFileUsage",
    "PeakVirtualSize",
    "PeakWorkingSetSize",
    "Priority",
    "PrivatePageCount",
    "ProcessId",
    "QuotaNonPagedPoolUsage",
    "QuotaPagedPoolUsage",
    "QuotaPeakNonPagedPoolUsage",
    "QuotaPeakPagedPoolUsage",
    "ReadOperationCount",
    "ReadTransferCount",
    "SessionId",
    "Status",
    "TerminationDate",
    "ThreadCount",
    "UserModeTime",
    "VirtualSize",
    "WindowsVersion",
    "WorkingSetSize",
    "WriteOperationCount",
    "WriteTransferCount",
    NULL
};
