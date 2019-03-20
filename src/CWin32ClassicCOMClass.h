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
class CWin32ClassicCOMClassObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Caption,
        PROP_Description,
        PROP_InstallDate,
        PROP_Status,
        PROP_ComponentID,
        PROP_Name,
    };

    CWin32ClassicCOMClassObject() {}
    CWin32ClassicCOMClassObject(const CWin32ClassicCOMClassObject &) = default;
    CWin32ClassicCOMClassObject(CWin32ClassicCOMClassObject &&) = default;
    ~CWin32ClassicCOMClassObject() {}
    CWin32ClassicCOMClassObject & operator=(const CWin32ClassicCOMClassObject &) = default;
    CWin32ClassicCOMClassObject & operator=(CWin32ClassicCOMClassObject &&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring InstallDate() { return (*Properties().at(PROP_InstallDate)).FromDATETIME(); }
    std::wstring Status() { return (*Properties().at(PROP_Status)).FromBSTR(); }
    std::wstring ComponentID() { return (*Properties().at(PROP_ComponentID)).FromBSTR(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
