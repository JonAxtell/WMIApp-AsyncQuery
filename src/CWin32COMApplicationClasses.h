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
class CWin32COMApplicationClassesObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_PartComponent,
        PROP_GroupComponent,
    };

    CWin32COMApplicationClassesObject() {}
    CWin32COMApplicationClassesObject(const CWin32COMApplicationClassesObject &) = default;
    CWin32COMApplicationClassesObject(CWin32COMApplicationClassesObject &&) = default;
    ~CWin32COMApplicationClassesObject() {}
    CWin32COMApplicationClassesObject & operator=(const CWin32COMApplicationClassesObject &) = default;
    CWin32COMApplicationClassesObject & operator=(CWin32COMApplicationClassesObject &&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring PartComponent() { return (*Properties().at(PROP_PartComponent)).FromBSTR(); }
    std::wstring GroupComponent() { return (*Properties().at(PROP_GroupComponent)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
