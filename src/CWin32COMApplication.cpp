#include "pch.h"
#include "CWin32COMApplication.h"

const char* CWin32COMApplicationObject::ObjectName = "Win32_COMApplication";

const char* CWin32COMApplicationObject::propertyNames[] =
{
    "Caption",
    "Description",
    "InstallDate",
    "Name",
    "Status",
    NULL
};
