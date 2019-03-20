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
class CWin32ProductObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_AssignmentType,
        PROP_Caption,
        PROP_Description,
        PROP_IdentifyingNumber,
        PROP_InstallDate,
        PROP_InstallDate2,
        PROP_InstallLocation,
        PROP_InstallState,
        PROP_HelpLink,
        PROP_HelpTelephone,
        PROP_InstallSource,
        PROP_Language,
        PROP_LocalPackage,
        PROP_Name,
        PROP_PackageCache,
        PROP_PackageCode,
        PROP_PackageName,
        PROP_ProductID,
        PROP_RegOwner,
        PROP_RegCompany,
        PROP_SKUNumber,
        PROP_Transforms,
        PROP_URLInfoAbout,
        PROP_URLUpdateInfo,
        PROP_Vendor,
        PROP_WordCount,
        PROP_Version,
    };

    CWin32ProductObject() {}
    CWin32ProductObject(const CWin32ProductObject&) = default;
    CWin32ProductObject(CWin32ProductObject&&) = default;
    ~CWin32ProductObject() {}
    CWin32ProductObject& operator=(const CWin32ProductObject&) = default;
    CWin32ProductObject& operator=(CWin32ProductObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
