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
class CWin32DCOMApplicationObject : public CWBEMObject
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
        PROP_AppID,
    };

    CWin32DCOMApplicationObject() {}
    CWin32DCOMApplicationObject(const CWin32DCOMApplicationObject &) = default;
    CWin32DCOMApplicationObject(CWin32DCOMApplicationObject &&) = default;
    ~CWin32DCOMApplicationObject() {}
    CWin32DCOMApplicationObject & operator=(const CWin32DCOMApplicationObject &) = default;
    CWin32DCOMApplicationObject & operator=(CWin32DCOMApplicationObject &&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring InstallDate() { return (*Properties().at(PROP_InstallDate)).FromDATETIME(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }
    std::wstring Status() { return (*Properties().at(PROP_Status)).FromBSTR(); }
    std::wstring AppID() { return (*Properties().at(PROP_AppID)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
