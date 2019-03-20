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
class CWin32COMClassObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Caption,
        PROP_Description,
        PROP_InstallDate,
        PROP_Name,
        PROP_Status,
    };

    CWin32COMClassObject() {}
    CWin32COMClassObject(const CWin32COMClassObject &) = default;
    CWin32COMClassObject(CWin32COMClassObject &&) = default;
    ~CWin32COMClassObject() {}
    CWin32COMClassObject & operator=(const CWin32COMClassObject &) = default;
    CWin32COMClassObject & operator=(CWin32COMClassObject &&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring InstallDate() { return (*Properties().at(PROP_InstallDate)).FromDATETIME(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }
    std::wstring Status() { return (*Properties().at(PROP_Status)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
