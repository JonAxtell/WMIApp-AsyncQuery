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
class CWin32SoftwareLicensingProductObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_ID,
        PROP_Name,
        PROP_Description,
        PROP_ApplicationID,
        PROP_ProcessorURL,
        PROP_MachineURL,
        PROP_ProductKeyURL,
        PROP_UseLicenseURL,
        PROP_LicenseStatus,
        PROP_LicenseStatusReason,
        PROP_GracePeriodRemaining,
        PROP_EvaluationEndDate,
        PROP_OfflineInstallationId,
        PROP_PartialProductKey,
        PROP_ProductKeyID,
        PROP_LicenseFamily,
        PROP_LicenseDependsOn,
        PROP_LicenseIsAddon,
        PROP_VLActivationInterval,
        PROP_VLRenewalInterval,
        PROP_KeyManagementServiceProductKeyID,
        PROP_KeyManagementServiceMachine,
        PROP_KeyManagementServicePort,
        PROP_DiscoveredKeyManagementServiceMachineName,
        PROP_DiscoveredKeyManagementServiceMachinePort,
        PROP_IsKeyManagementServiceMachine,
        PROP_KeyManagementServiceCurrentCount,
        PROP_RequiredClientCount,
        PROP_KeyManagementServiceUnlicensedRequests,
        PROP_KeyManagementServiceLicensedRequests,
        PROP_KeyManagementServiceOOBGraceRequests,
        PROP_KeyManagementServiceOOTGraceRequests,
        PROP_KeyManagementServiceNonGenuineGraceRequests,
        PROP_KeyManagementServiceTotalRequests,
        PROP_KeyManagementServiceFailedRequests,
        PROP_KeyManagementServiceNotificationRequests,
        PROP_GenuineStatus,
        PROP_ExtendedGrace,
        PROP_TokenActivationILID,
        PROP_TokenActivationILVID,
        PROP_TokenActivationGrantNumber,
        PROP_TokenActivationCertificateThumbprint,
        PROP_TokenActivationAdditionalInfo,
        PROP_TrustedTime,
    };

    CWin32SoftwareLicensingProductObject() {}
    CWin32SoftwareLicensingProductObject(const CWin32SoftwareLicensingProductObject&) = default;
    CWin32SoftwareLicensingProductObject(CWin32SoftwareLicensingProductObject&&) = default;
    ~CWin32SoftwareLicensingProductObject() {}
    CWin32SoftwareLicensingProductObject& operator=(const CWin32SoftwareLicensingProductObject&) = default;
    CWin32SoftwareLicensingProductObject& operator=(CWin32SoftwareLicensingProductObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
