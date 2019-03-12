#pragma once

#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#include "CWBEMObject.h"
#include "CVariant.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <stdlib.h>

//#################################################################################################################################
//
class CWin32ProcessorObject : public CWBEMObject
{
public:
    static const std::string ObjectName;

    class CArchitecture
    {
    public:
        enum valueEnum
        {
            ARCH_x86        = 0,
            ARCH_MIPS       = 1,
            ARCH_Alpha      = 2,
            ARCH_PowerPC    = 3,
                            // 4
            ARCH_ARM        = 5,
            ARCH_ia64       = 6,
                            // 7
                            // 8
            ARCH_x64        = 9
        };
        CArchitecture(uint32_t arch) : _arch(arch) {}
        ~CArchitecture() {}

        std::wstring Text() { return _architectureValues.at(_arch); }
        uint32_t Value() { return _arch; }

    private:
        uint32_t _arch;
    };

    class CAvailability
    {
    public:
        enum valueEnum
        {
            AVAIL_OTHER                     = 1,
            AVAIL_UNKNOWN                   = 2,
            AVAIL_RUNNING                   = 3,
            AVAIL_WARNING                   = 4,
            AVAIL_INTEST                    = 5,
            AVAIL_NOTAPPLICABLE             = 6,
            AVAIL_POWEROFF                  = 7,
            AVAIL_OFFLINE                   = 8,
            AVAIL_OFFDUTY                   = 9,
            AVAIL_DEGRADED                  = 10,
            AVAIL_NOTINSTALLED              = 11,
            AVAIL_INSTALLERROR              = 12,
            AVAIL_POWERSAVE_UNKNOWN         = 13,   // The device is known to be in a power save state, but its exact status is unknown.
            AVAIL_POWERSAVE_LOWPOWERMODE    = 14,   // The device is in a power save state, but is still functioning, and may exhibit decreased performance.
            AVAIL_POWERSAVE_STANDBY         = 15,   // The device is not functioning, but can be brought to full power quickly.
            AVAIL_POWERCYCLE                = 16,
            AVAIL_POWERSAVE_WARNING         = 17,   // The device is in a warning state, though also in a power save state.
            AVAIL_PAUSED                    = 18,   // The device is paused.
            AVAIL_NOTREADY                  = 19,   // The device is not ready.
            AVAIL_NOTCONFIGURED             = 20,   // The device is not configured.
            AVAIL_QUIESCED                  = 21,
        };
        CAvailability(uint32_t avail) : _avail(avail) {}
        ~CAvailability() {}

        std::wstring Text() { return _availabilityValues.at(_avail); }
        uint32_t Value() { return _avail; }

    private:
        uint32_t _avail;
    };

    class CCpuStatus
    {
    public:
        enum valueEnum
        {
            CPUSTATUS_UKNOWN            = 0,
            CPUSTATUS_ENABLED           = 1,
            CPUSTATUS_DISABLEDBYUSER    = 2,
            CPUSTATUS_DISABLEBYBIOS     = 3,
            CPUSTATUS_IDLE              = 4,
            CPUSTATUS_RESERVED5         = 5,
            CPUSTATUS_RESERVED6         = 6,
            CPUSTATUS_OTHER             = 7,
        };
        CCpuStatus(uint32_t avail) : _status(avail) {}
        ~CCpuStatus() {}

        std::wstring Text() { return _cpuStatusValues.at(_status); }
        uint32_t Value() { return _status; }

    private:
        uint32_t _status;
    };

    class CCpuVoltage
    {
    public:
        CCpuVoltage(uint32_t voltage, uint32_t caps) : _voltage(voltage), _caps(caps) {}
        ~CCpuVoltage() {}

        std::wstring Text() { return std::to_wstring(Volts()); }
        double Value() { return Volts(); }

    private:
        double Volts()
        {
            if (_voltage & 0x80)
            {
                return static_cast<double>(_voltage & 0x7F) / 10.0;
            }
            if (_caps & 0x04)
            {
                return 2.9;
            }
            if (_caps & 0x02)
            {
                return 3.3;
            }
            if (_caps & 0x01)
            {
                return 5.0;
            }
            if (_voltage & 0x7F)
            {
                return static_cast<double>(_voltage & 0x7F) / 10.0;
            }
            return 0.0;
        }
        uint32_t _voltage;
        uint32_t _caps;
    };

    class CCpuFrequency
    {
    public:
        CCpuFrequency(uint32_t clock) : _clock(clock) {}
        ~CCpuFrequency() {}

        std::string Text()
        {
            char dec[32];
            char frac[32];
            const char *freq;
            if (_clock >= 1000)
            {
                _itoa_s(_clock / 1000, dec, 32, 10);
                _itoa_s( static_cast<int>(((static_cast<double>(_clock) / 1000) - (_clock / 1000)) * 100.0), frac, 32, 10);
                freq = "Ghz";
            }
            else
            {
                _itoa_s(_clock, dec, 32, 10);
                frac[0] = 0;
                freq = "Mhz";
            }
            return std::string(dec) + "." + std::string(frac) + std::string(freq);
        }
        double Value() { return static_cast<double>(_clock); }

    private:
        uint32_t _clock;
    };

    class CCpuFamily
    {
    public:
        CCpuFamily(uint32_t family) : _family(family) {}
        ~CCpuFamily() {}

        std::wstring Text() { return _cpuFamilyValues.at(_family); }
        uint32_t Value() { return _family; }

    private:
        uint32_t _family;
    };

    enum propertyEnum
    {
        PROP_AddressWidth,
        PROP_Architecture,
        PROP_AssetTag,
        PROP_Availability,
        PROP_Caption,
        PROP_Characteristics,
        PROP_ConfigManagerErrorCode,
        PROP_ConfigManagerUserConfig,
        PROP_CpuStatus,
        PROP_CreationClassName,
        PROP_CurrentClockSpeed,
        PROP_CurrentVoltage,
        PROP_DataWidth,
        PROP_Description,
        PROP_DeviceID,
        PROP_ErrorCleared,
        PROP_ErrorDescription,
        PROP_ExtClock,
        PROP_Family,
        PROP_InstallDate,
        PROP_L2CacheSize,
        PROP_L2CacheSpeed,
        PROP_L3CacheSize,
        PROP_L3CacheSpeed,
        PROP_LastErrorCode,
        PROP_Level,
        PROP_LoadPercentage,
        PROP_Manufacturer,
        PROP_MaxClockSpeed,
        PROP_Name,
        PROP_NumberOfCores,
        PROP_NumberOfEnabledCore,
        PROP_NumberOfLogicalProcessors,
        PROP_OtherFamilyDescription,
        PROP_PartNumber,
        PROP_PNPDeviceID,
        PROP_PowerManagementCapabilities,
        PROP_PowerManagementSupported,
        PROP_ProcessorId,
        PROP_ProcessorType,
        PROP_Revision,
        PROP_Role,
        PROP_SecondLevelAddressTranslationExtensions,
        PROP_SerialNumber,
        PROP_SocketDesignation,
        PROP_Status,
        PROP_StatusInfo,
        PROP_Stepping,
        PROP_SystemCreationClassName,
        PROP_SystemName,
        PROP_ThreadCount,
        PROP_UniqueId,
        PROP_UpgradeMethod,
        PROP_Version,
        PROP_VirtualizationFirmwareEnabled,
        PROP_VMMonitorModeExtensions,
        PROP_VoltageCaps,
    };

    CWin32ProcessorObject() {}
    CWin32ProcessorObject(const CWin32ProcessorObject&) = default;
    ~CWin32ProcessorObject() {}
    CWin32ProcessorObject& operator=(const CWin32ProcessorObject&) = default;

    std::shared_ptr<CVariant> Property(int prop) { return Properties().at(prop); }

    CArchitecture Architecture() { return (*Properties().at(PROP_Architecture)).FromI4(); }
    CAvailability Availability() { return (*Properties().at(PROP_Availability)).FromI4(); }
    CCpuStatus CpuStatus() { return (*Properties().at(PROP_CpuStatus)).FromI4(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    uint32_t CurrentVoltage() { return (*Properties().at(PROP_CurrentVoltage)).FromI4(); }
    uint32_t CurrentClockSpeed() { return (*Properties().at(PROP_CurrentClockSpeed)).FromI4(); }
    uint32_t Family() { return (*Properties().at(PROP_Family)).FromI4(); }
    std::wstring SocketDesignation() { return (*Properties().at(PROP_SocketDesignation)).FromBSTR(); }
    uint32_t VoltageCaps() { return (*Properties().at(PROP_VoltageCaps)).FromI4(); }

    CCpuVoltage Voltage() { return CCpuVoltage((*Properties().at(PROP_CurrentVoltage)).FromI4(), (*Properties().at(PROP_VoltageCaps)).FromI4()); }
    CCpuFrequency Frequency() { return CCpuFrequency((*Properties().at(PROP_CurrentClockSpeed)).FromI4()); }
    CCpuFamily CpuFamily() { return CCpuFamily((*Properties().at(PROP_Family)).FromI4()); }

public:
    static const std::vector<std::string> propertyNames;

private:
    static const std::vector<std::wstring> _architectureValues;
    static const std::vector<std::wstring> _availabilityValues;
    static const std::vector<std::wstring> _cpuStatusValues;
    static const std::map<int, std::wstring> _cpuFamilyValues;
};