#pragma once

#include "pch.h"
#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#include "CWBEMObject.h"
#include "CVariant.h"
#include <ostream>
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
    static const char* ObjectName;

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

        friend std::wostream& operator<<(std::wostream& os, const CArchitecture& v);

        const std::string Text() const { return std::string(_architectureValues[_arch]); }
        uint32_t Value() const { return _arch; }

    private:
        uint32_t _arch;
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

        friend std::wostream& operator<<(std::wostream& os, const CCpuStatus& v);

        const std::string Text() const { return std::string(_cpuStatusValues[_status]); }
        uint32_t Value() const { return _status; }

    private:
        uint32_t _status;
    };

    class CCpuVoltage
    {
    public:
        CCpuVoltage(uint32_t voltage, uint32_t caps) : _voltage(voltage), _caps(caps) {}
        CCpuVoltage(const CCpuVoltage&) = default;
        CCpuVoltage(CCpuVoltage&&) = default;
        ~CCpuVoltage() {}
        CCpuVoltage& operator=(const CCpuVoltage&) = default;
        CCpuVoltage& operator=(CCpuVoltage&&) = default;

        friend std::wostream& operator<<(std::wostream& os, const CCpuVoltage& v);

        const std::string Text() const 
        { 
            double v = Volts();
            char dec[32];
            char frac[32];
            _itoa_s(static_cast<int>(v), dec, 32, 10);
            _itoa_s(static_cast<int>((v - static_cast<int>(v)) * 100), frac, 32, 10);
            return std::string(dec) + "." + std::string(frac) + "V";
        }
        double Value() const { return Volts(); }

    private:
        CCpuVoltage() = delete;

        double Volts() const
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

        friend std::wostream& operator<<(std::wostream& os, const CCpuFrequency& f);

        const std::string Text() const
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
        double Value() const { return static_cast<double>(_clock); }

    private:
        uint32_t _clock;
    };

    class CCpuFamily
    {
    public:
        CCpuFamily(uint32_t family) : _family(family) {}
        ~CCpuFamily() {}

        friend std::wostream& operator<<(std::wostream& os, const CCpuFamily& f);

        const std::string Text() const { return std::string(_cpuFamilyValues.at(_family)); }
        uint32_t Value() const { return _family; }

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
    CWin32ProcessorObject(CWin32ProcessorObject&&) = default;
    ~CWin32ProcessorObject() {}
    CWin32ProcessorObject& operator=(const CWin32ProcessorObject&) = default;
    CWin32ProcessorObject& operator=(CWin32ProcessorObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    CWBEMObject::CAvailability Availability() { return (*Properties().at(PROP_Availability)).FromI4(); }
    CWBEMObject::CConfigManagerErrorCode ConfigManagerErrorCode() { return (*Properties().at(PROP_ConfigManagerErrorCode)).FromI4(); }

    CArchitecture Architecture() { return (*Properties().at(PROP_Architecture)).FromI4(); }
    CCpuStatus CpuStatus() { return (*Properties().at(PROP_CpuStatus)).FromI4(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    uint32_t CurrentVoltage() { return (*Properties().at(PROP_CurrentVoltage)).FromI4(); }
    uint32_t CurrentClockSpeed() { return (*Properties().at(PROP_CurrentClockSpeed)).FromI4(); }
    uint32_t Family() { return (*Properties().at(PROP_Family)).FromI4(); }
    std::wstring SocketDesignation() { return (*Properties().at(PROP_SocketDesignation)).FromBSTR(); }
    std::wstring Status() { return (*Properties().at(PROP_Status)).FromBSTR(); }
    uint32_t VoltageCaps() { return (*Properties().at(PROP_VoltageCaps)).FromI4(); }

    CCpuVoltage Voltage() { return CCpuVoltage((*Properties().at(PROP_CurrentVoltage)).FromI4(), (*Properties().at(PROP_VoltageCaps)).FromI4()); }
    CCpuFrequency Frequency() { return CCpuFrequency((*Properties().at(PROP_CurrentClockSpeed)).FromI4()); }
    CCpuFamily CpuFamily() { return CCpuFamily((*Properties().at(PROP_Family)).FromI4()); }

public:
    static const char* propertyNames[];

private:
    static const char* _architectureValues[];
    static const char* _cpuStatusValues[];
    static const std::map<int, const char*> _cpuFamilyValues;
};
