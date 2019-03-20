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
class CWin32SerialPortObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Availability,
        PROP_Binary,
        PROP_Capabilities,
        PROP_CapabilityDescriptions,
        PROP_Caption,
        PROP_ConfigManagerErrorCode,
        PROP_ConfigManagerUserConfig,
        PROP_CreationClassName,
        PROP_Description,
        PROP_DeviceID,
        PROP_ErrorCleared,
        PROP_ErrorDescription,
        PROP_InstallDate,
        PROP_LastErrorCode,
        PROP_MaxBaudRate,
        PROP_MaximumInputBufferSize,
        PROP_MaximumOutputBufferSize,
        PROP_MaxNumberControlled,
        PROP_Name,
        PROP_OSAutoDiscovered,
        PROP_PNPDeviceID,
        PROP_PowerManagementCapabilities,
        PROP_PowerManagementSupported,
        PROP_ProtocolSupported,
        PROP_ProviderType,
        PROP_SettableBaudRate,
        PROP_SettableDataBits,
        PROP_SettableFlowControl,
        PROP_SettableParity,
        PROP_SettableParityCheck,
        PROP_SettableRLSD,
        PROP_SettableStopBits,
        PROP_Status,
        PROP_StatusInfo,
        PROP_Supports16BitMode,
        PROP_SupportsDTRDSR,
        PROP_SupportsElapsedTimeouts,
        PROP_SupportsIntTimeouts,
        PROP_SupportsParityCheck,
        PROP_SupportsRLSD,
        PROP_SupportsRTSCTS,
        PROP_SupportsSpecialCharacters,
        PROP_SupportsXOnXOff,
        PROP_SupportsXOnXOffSet,
        PROP_SystemCreationClassName,
        PROP_SystemName,
        PROP_TimeOfLastReset,
    };

    CWin32SerialPortObject() {}
    CWin32SerialPortObject(const CWin32SerialPortObject&) = default;
    CWin32SerialPortObject(CWin32SerialPortObject&&) = default;
    ~CWin32SerialPortObject() {}
    CWin32SerialPortObject& operator=(const CWin32SerialPortObject&) = default;
    CWin32SerialPortObject& operator=(CWin32SerialPortObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    CWBEMProperty_Availability Availability() { return CWBEMProperty_Availability(*(Properties().at(PROP_Availability))); }
    CWBEMProperty_ConfigManagerErrorCode ConfigManagerErrorCode() { return CWBEMProperty_Availability(*(Properties().at(PROP_ConfigManagerErrorCode))); }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }

public:
    static const char* propertyNames[];

private:
};
