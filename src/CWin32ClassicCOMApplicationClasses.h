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
class CWin32ClassicCOMApplicationClassesObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_PartComponent,
        PROP_GroupComponent,
    };

    CWin32ClassicCOMApplicationClassesObject() {}
    CWin32ClassicCOMApplicationClassesObject(const CWin32ClassicCOMApplicationClassesObject &) = default;
    CWin32ClassicCOMApplicationClassesObject(CWin32ClassicCOMApplicationClassesObject &&) = default;
    ~CWin32ClassicCOMApplicationClassesObject() {}
    CWin32ClassicCOMApplicationClassesObject & operator=(const CWin32ClassicCOMApplicationClassesObject &) = default;
    CWin32ClassicCOMApplicationClassesObject & operator=(CWin32ClassicCOMApplicationClassesObject &&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring PartComponent() { return (*Properties().at(PROP_PartComponent)).FromBSTR(); }      // Win32_ClassicComClass.ComponentId
    std::wstring GroupComponent() { return (*Properties().at(PROP_GroupComponent)).FromBSTR(); }    // Win32_DCOMApplication.AppID

    std::wstring PartComponentGUID();
    std::wstring GroupComponentGUID();

public:
    static const char* propertyNames[];
};
