#include "pch.h"
#include "CWin32Processor.h"

const char* CWin32ProcessorObject::ObjectName = "Win32_Processor";

const char* CWin32ProcessorObject::_architectureValues[] =
{
    "x86",
    "MIPS",
    "Alpha",
    "PowerPC",
    "",
    "ARM",
    "ia64",
    "",
    "",
    "x64"
};

const char* CWin32ProcessorObject::_availabilityValues[] =
{
    "",
    "Other(1)",
    "Unknown(2)",
    "Running / Full Power(3)",
    "Warning(4)",
    "In Test(5)",
    "Not Applicable(6)",
    "Power Off(7)",
    "Off Line(8)",
    "Off Duty(9)",
    "Degraded(10)",
    "Not Installed(11)",
    "Install Error(12)",
    "Power Save - Unknown(13)",
    "Power Save - Low Power Mode(14)",
    "Power Save - Standby(15)",
    "Power Cycle(16)",
    "Power Save - Warning(17)",
    "Paused(18)",
    "Not Ready(19)",
    "Not Configured(20)",
    "Quiesced(21)",
};

const char* CWin32ProcessorObject::_cpuStatusValues[] =
{
    "Unknown(0)",
    "CPU Enabled(1)",
    "CPU Disabled by User via BIOS Setup(2)",
    "CPU Disabled By BIOS(POST Error) (3)",
    "CPU is Idle(4)",
    "Reserved(5)",
    "Reserved(6)",
    "Other(7)",
};

const std::map<int, const char*> CWin32ProcessorObject::_cpuFamilyValues =
{
    { 1, "Other" },
    { 2, "Unknown" },
    { 3, "8086" },
    { 4, "80286" },
    { 5, "80386" },        // Intel386™ Processor
    { 6, "80486" },        // Intel486™ Processor
    { 7, "8087" },
    { 8, "80287" },
    { 9, "80387" },
    { 10, "80487" },
    { 11, "Pentium(R) brand" },    // Pentium Brand
    { 12, "Pentium(R) Pro" },      // Pentium Pro
    { 13, "Pentium(R) II" },       // Pentium II
    { 14, "Pentium(R) processor with MMX(TM) technology" },    // Pentium Processor with MMX™ Technology
    { 15, "Celeron(TM)" },             // Celeron™
    { 16, "Pentium(R) II Xeon(TM)" },  // Pentium II Xeon™
    { 17, "Pentium(R) III" },          // Pentium III
    { 18, "M1 Family" },
    { 19, "M2 Family" },
    //
    //
    //
    { 24, "K5 Family" },               // K5 Family
    { 25, "K6 Family" },               // K6 Family
    { 26, "K6 - 2" },                  // K6 - 2
    { 27, "K6 - 3" },                  // K6 - 3
    { 28, "AMD Athlon(TM) Processor Family" }, // AMD Duron™ Processor Family
    { 29, "AMD(R) Duron(TM) Processor" },      // AMD Athlon™ Processor Family
    { 30, "AMD29000 Family" },                 // AMD2900 Family
    { 31, "K6 - 2 +" },
    { 32, "Power PC Family" },
    { 33, "Power PC 601" },
    { 34, "Power PC 603" },
    { 35, "Power PC 603" },
    { 36, "Power PC 604" },
    { 37, "Power PC 620" },
    { 38, "Power PC X704" },
    { 39, "Power PC 750" },
    { 48, "Alpha Family" },
    { 49, "Alpha 21064" },
    { 50, "Alpha 21066" },
    { 51, "Alpha 21164" },
    { 52, "Alpha 21164PC" },
    { 53, "Alpha 21164a" },
    { 54, "Alpha 21264" },
    { 55, "Alpha 21364" },
    //
    //
    //
    { 64, "MIPS Family" },
    { 65, "MIPS R4000" },
    { 66, "MIPS R4200" },
    { 67, "MIPS R4400" },
    { 68, "MIPS R4600" },
    { 69, "MIPS R10000" },
    //
    //
    //
    { 80, "SPARC Family" },
    { 81, "SuperSPARC" },
    { 82, "microSPARC II" },
    { 83, "microSPARC IIep" },
    { 84, "UltraSPARC" },
    { 85, "UltraSPARC II" },
    { 86, "UltraSPARC IIi" },
    { 87, "UltraSPARC III" },
    { 88, "UltraSPARC IIIi" },
    //
    //
    //
    { 96, "68040" },
    { 97, "68xxx Family" },
    { 98, "68000" },
    { 99, "68010" },
    { 100, "68020" },
    { 101, "68030" },
    //
    //
    //
    { 112, "Hobbit Family" },
    //
    //
    //
    { 120, "Crusoe(TM) TM5000 Family" },       // Crusoe™ TM5000 Family
    { 121, "Crusoe(TM) TM3000 Family" },       // Crusoe™ TM3000 Family
    { 122, "Efficeon(TM) TM8000 Family" },     // Efficeon™ TM8000 Family
    //
    //
    //
    { 128, "Weitek" },
    //
    //
    //
    { 130, "Itanium(TM) Processor" },                  // Itanium™ Processor
    { 131, "AMD Athlon(TM) 64 Processor Family" },     // AMD Athlon™ 64 Processor Family
    { 132, "AMD Opteron(TM) Family" },                 // AMD Opteron™ Processor Family
    //
    //
    //
    { 144, "PA - RISC Family" },
    { 145, "PA - RISC 8500" },
    { 146, "PA - RISC 8000" },
    { 147, "PA - RISC 7300LC" },
    { 148, "PA - RISC 7200" },
    { 149, "PA - RISC 7100LC" },
    { 150, "PA - RISC 7100" },
    //
    //
    //
    { 160, "V30 Family" },
    //
    //
    //
    { 176, "Pentium(R) III Xeon(TM)" },                // Pentium III Xeon™ Processor
    { 177, "Pentium(R) III Processor with Intel(R) SpeedStep(TM) Technology" },    // Pentium III Processor with Intel SpeedStep™ Technology
    { 178, "Pentium(R) 4" },                           // Pentium 4
    { 179, "Intel(R) Xeon(TM)" },                      // Intel Xeon™
    { 180, "AS400 Family" },
    { 181, "Intel(R) Xeon(TM) processor MP" },         // Intel Xeon™ Processor MP
    { 182, "AMD AthlonXP(TM) Family" },                // AMD Athlon™ XP Family
    { 183, "AMD AthlonMP(TM) Family" },                // AMD Athlon™ MP Family
    { 184, "Intel(R) Itanium(R) 2" },                  // Intel Itanium 2
    { 185, "Intel Pentium M Processor" },
    //
    //
    //
    { 190, "K7" },
    //
    //
    //
    { 198, "Intel Core(TM) i7 - 2760QM" },             // Intel Core™ i7 - 2760QM
    //
    //
    //
    { 200, "IBM390 Family" },
    { 201, "G4" },
    { 202, "G5" },
    { 203, "G6" },
    { 204, "z / Architecture base" },
    //
    //
    //
    { 250, "i860" },
    { 251, "i960" },
    //
    //
    //
    { 260, "SH - 3" },
    { 261, "SH - 4" },
    //
    //
    //
    { 280, "ARM" },
    { 281, "StrongARM" },
    //
    //
    //
    { 300, "6x86" },
    { 301, "MediaGX" },
    { 302, "MII" },
    //
    //
    //
    { 320, "WinChip" },
    //
    //
    //
    { 350, "DSP" },
    //
    //
    //
    { 500, "Video Processor" }
};


const char* CWin32ProcessorObject::propertyNames[] =
{
    "AddressWidth",
    "Architecture",
    "AssetTag",
    "Availability",
    "Caption",
    "Characteristics",
    "ConfigManagerErrorCode",
    "ConfigManagerUserConfig",
    "CpuStatus",
    "CreationClassName",
    "CurrentClockSpeed",
    "CurrentVoltage",
    "DataWidth",
    "Description",
    "DeviceID",
    "ErrorCleared",
    "ErrorDescription",
    "ExtClock",
    "Family",
    "InstallDate",
    "L2CacheSize",
    "L2CacheSpeed",
    "L3CacheSize",
    "L3CacheSpeed",
    "LastErrorCode",
    "Level",
    "LoadPercentage",
    "Manufacturer",
    "MaxClockSpeed",
    "Name",
    "NumberOfCores",
    "NumberOfEnabledCore",
    "NumberOfLogicalProcessors",
    "OtherFamilyDescription",
    "PartNumber",
    "PNPDeviceID",
    "PowerManagementCapabilities",
    "PowerManagementSupported",
    "ProcessorId",
    "ProcessorType",
    "Revision",
    "Role",
    "SecondLevelAddressTranslationExtensions",
    "SerialNumber",
    "SocketDesignation",
    "Status",
    "StatusInfo",
    "Stepping",
    "SystemCreationClassName",
    "SystemName",
    "ThreadCount",
    "UniqueId",
    "UpgradeMethod",
    "Version",
    "VirtualizationFirmwareEnabled",
    "VMMonitorModeExtensions",
    "VoltageCaps",
    NULL
};

std::wostream& operator<<(std::wostream& os, const CWin32ProcessorObject::CCpuVoltage& v)
{
    os << v.Text().c_str();
    return os;
}

std::wostream& operator<<(std::wostream& os, const CWin32ProcessorObject::CCpuFrequency& f)
{
    os << f.Text().c_str();
    return os;
}

std::wostream& operator<<(std::wostream& os, const CWin32ProcessorObject::CCpuFamily& f)
{
    os << f.Text().c_str();
    return os;
}

std::wostream& operator<<(std::wostream& os, const CWin32ProcessorObject::CCpuStatus& s)
{
    os << s.Text().c_str();
    return os;
}

std::wostream& operator<<(std::wostream& os, const CWin32ProcessorObject::CArchitecture& a)
{
    os << a.Text().c_str();
    return os;
}

std::wostream& operator<<(std::wostream& os, const CWin32ProcessorObject::CAvailability& a)
{
    os << a.Text().c_str();
    return os;
}
