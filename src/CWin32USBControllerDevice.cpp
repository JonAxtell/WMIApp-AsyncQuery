#include "pch.h"
#include "CWin32USBControllerDevice.h"

const char* CWin32USBControllerDeviceObject::ObjectName = "Win32_USBControllerDevice";

const char* CWin32USBControllerDeviceObject::propertyNames[] =
{
    "NegotiatedDataWidth",
    "NegotiatedSpeed",
    "AccessState",
    "NumberOfHardResets",
    "NumberOfSoftResets",
    "Antecedent",
    "Dependent",
    NULL
};

