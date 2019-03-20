#pragma once

#include "pch.h"
#include "CWBEMProperty.h"
#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#include "CWBEMObject.h"
#include "CVariant.h"
#include <ostream>
#include <string>
#include <stdlib.h>

//#################################################################################################################################
//
class CWin32USBControllerDeviceObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_NegotiatedDataWidth,
        PROP_NegotiatedSpeed,
        PROP_AccessState,
        PROP_NumberOfHardResets,
        PROP_NumberOfSoftResets,
        PROP_Antecedent,
        PROP_Dependent,
    };

    CWin32USBControllerDeviceObject() {}
    CWin32USBControllerDeviceObject(const CWin32USBControllerDeviceObject&) = default;
    CWin32USBControllerDeviceObject(CWin32USBControllerDeviceObject&&) = default;
    ~CWin32USBControllerDeviceObject() {}
    CWin32USBControllerDeviceObject& operator=(const CWin32USBControllerDeviceObject&) = default;
    CWin32USBControllerDeviceObject& operator=(CWin32USBControllerDeviceObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Antecedent() { return (*Properties().at(PROP_Antecedent)).FromBSTR(); }
    std::wstring Dependent() { return (*Properties().at(PROP_Dependent)).FromBSTR(); }

public:
    static const char* propertyNames[];

private:
};
