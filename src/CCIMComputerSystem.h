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
class CCIMComputerSystemObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Caption,
        PROP_Description,
        PROP_InstallDate,
        PROP_Status,
        PROP_CreationClassName,
        PROP_Name,
        PROP_PrimaryOwnerContact,
        PROP_PrimaryOwnerName,
        PROP_Roles,
        PROP_NameFormat,
    };

    CCIMComputerSystemObject() {}
    CCIMComputerSystemObject(const CCIMComputerSystemObject&) = default;
    CCIMComputerSystemObject(CCIMComputerSystemObject&&) = default;
    ~CCIMComputerSystemObject() {}
    CCIMComputerSystemObject& operator=(const CCIMComputerSystemObject&) = default;
    CCIMComputerSystemObject& operator=(CCIMComputerSystemObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring InstallDate() { return (*Properties().at(PROP_InstallDate)).FromDATETIME(); }
    std::wstring Status() { return (*Properties().at(PROP_Status)).FromBSTR(); }
    std::wstring CreationClassName() { return (*Properties().at(PROP_CreationClassName)).FromBSTR(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }
    std::wstring PrimaryOwnerContact() { return (*Properties().at(PROP_PrimaryOwnerContact)).FromBSTR(); }
    std::wstring PrimaryOwnerName() { return (*Properties().at(PROP_PrimaryOwnerName)).FromBSTR(); }
    std::vector<std::wstring> Roles() { return (*Properties().at(PROP_Roles)).FromArrayBSTR(); }
    std::wstring NameFormat() { return (*Properties().at(PROP_NameFormat)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
