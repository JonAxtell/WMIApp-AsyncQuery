#include "pch.h"
#include "CWin32Processor.h"

const std::string CWin32ProcessorObject::ObjectName("Win32_Processor");

const std::vector<std::wstring> CWin32ProcessorObject::_architectureValues =
{
    L"x86",
    L"MIPS",
    L"Alpha",
    L"PowerPC",
    L"",
    L"ARM",
    L"ia64",
    L"",
    L"",
    L"x64"
};

const std::vector<std::wstring> CWin32ProcessorObject::_availabilityValues =
{
    L"",
    L"Other(1)",
    L"Unknown(2)",
    L"Running / Full Power(3)",
    L"Warning(4)",
    L"In Test(5)",
    L"Not Applicable(6)",
    L"Power Off(7)",
    L"Off Line(8)",
    L"Off Duty(9)",
    L"Degraded(10)",
    L"Not Installed(11)",
    L"Install Error(12)",
    L"Power Save - Unknown(13)",
    L"Power Save - Low Power Mode(14)",
    L"Power Save - Standby(15)",
    L"Power Cycle(16)",
    L"Power Save - Warning(17)",
    L"Paused(18)",
    L"Not Ready(19)",
    L"Not Configured(20)",
    L"Quiesced(21)",
};

const std::vector<std::wstring> CWin32ProcessorObject::_cpuStatusValues =
{
    L"Unknown(0)",
    L"CPU Enabled(1)",
    L"CPU Disabled by User via BIOS Setup(2)",
    L"CPU Disabled By BIOS(POST Error) (3)",
    L"CPU is Idle(4)",
    L"Reserved(5)",
    L"Reserved(6)",
    L"Other(7)",
};

const std::map<int, std::wstring> CWin32ProcessorObject::_cpuFamilyValues =
{
    { 1, L"Other" },
    { 2, L"Unknown" },
    { 3, L"8086" },
    { 4, L"80286" },
    { 5, L"80386" },        // Intel386™ Processor
    { 6, L"80486" },        // Intel486™ Processor
    { 7, L"8087" },
    { 8, L"80287" },
    { 9, L"80387" },
    { 10, L"80487" },
    { 11, L"Pentium(R) brand" },    // Pentium Brand
    { 12, L"Pentium(R) Pro" },      // Pentium Pro
    { 13, L"Pentium(R) II" },       // Pentium II
    { 14, L"Pentium(R) processor with MMX(TM) technology" },    // Pentium Processor with MMX™ Technology
    { 15, L"Celeron(TM)" },             // Celeron™
    { 16, L"Pentium(R) II Xeon(TM)" },  // Pentium II Xeon™
    { 17, L"Pentium(R) III" },          // Pentium III
    { 18, L"M1 Family" },
    { 19, L"M2 Family" },
    //
    //
    //
    { 24, L"K5 Family" },               // K5 Family
    { 25, L"K6 Family" },               // K6 Family
    { 26, L"K6 - 2" },                  // K6 - 2
    { 27, L"K6 - 3" },                  // K6 - 3
    { 28, L"AMD Athlon(TM) Processor Family" }, // AMD Duron™ Processor Family
    { 29, L"AMD(R) Duron(TM) Processor" },      // AMD Athlon™ Processor Family
    { 30, L"AMD29000 Family" },                 // AMD2900 Family
    { 31, L"K6 - 2 +" },
    { 32, L"Power PC Family" },
    { 33, L"Power PC 601" },
    { 34, L"Power PC 603" },
    { 35, L"Power PC 603" },
    { 36, L"Power PC 604" },
    { 37, L"Power PC 620" },
    { 38, L"Power PC X704" },
    { 39, L"Power PC 750" },
    { 48, L"Alpha Family" },
    { 49, L"Alpha 21064" },
    { 50, L"Alpha 21066" },
    { 51, L"Alpha 21164" },
    { 52, L"Alpha 21164PC" },
    { 53, L"Alpha 21164a" },
    { 54, L"Alpha 21264" },
    { 55, L"Alpha 21364" },
    //
    //
    //
    { 64, L"MIPS Family" },
    { 65, L"MIPS R4000" },
    { 66, L"MIPS R4200" },
    { 67, L"MIPS R4400" },
    { 68, L"MIPS R4600" },
    { 69, L"MIPS R10000" },
    //
    //
    //
    { 80, L"SPARC Family" },
    { 81, L"SuperSPARC" },
    { 82, L"microSPARC II" },
    { 83, L"microSPARC IIep" },
    { 84, L"UltraSPARC" },
    { 85, L"UltraSPARC II" },
    { 86, L"UltraSPARC IIi" },
    { 87, L"UltraSPARC III" },
    { 88, L"UltraSPARC IIIi" },
    //
    //
    //
    { 96, L"68040" },
    { 97, L"68xxx Family" },
    { 98, L"68000" },
    { 99, L"68010" },
    { 100, L"68020" },
    { 101, L"68030" },
    //
    //
    //
    { 112, L"Hobbit Family" },
    //
    //
    //
    { 120, L"Crusoe(TM) TM5000 Family" },       // Crusoe™ TM5000 Family
    { 121, L"Crusoe(TM) TM3000 Family" },       // Crusoe™ TM3000 Family
    { 122, L"Efficeon(TM) TM8000 Family" },     // Efficeon™ TM8000 Family
    //
    //
    //
    { 128, L"Weitek" },
    //
    //
    //
    { 130, L"Itanium(TM) Processor" },                  // Itanium™ Processor
    { 131, L"AMD Athlon(TM) 64 Processor Family" },     // AMD Athlon™ 64 Processor Family
    { 132, L"AMD Opteron(TM) Family" },                 // AMD Opteron™ Processor Family
    //
    //
    //
    { 144, L"PA - RISC Family" },
    { 145, L"PA - RISC 8500" },
    { 146, L"PA - RISC 8000" },
    { 147, L"PA - RISC 7300LC" },
    { 148, L"PA - RISC 7200" },
    { 149, L"PA - RISC 7100LC" },
    { 150, L"PA - RISC 7100" },
    //
    //
    //
    { 160, L"V30 Family" },
    //
    //
    //
    { 176, L"Pentium(R) III Xeon(TM)" },                // Pentium III Xeon™ Processor
    { 177, L"Pentium(R) III Processor with Intel(R) SpeedStep(TM) Technology" },    // Pentium III Processor with Intel SpeedStep™ Technology
    { 178, L"Pentium(R) 4" },                           // Pentium 4
    { 179, L"Intel(R) Xeon(TM)" },                      // Intel Xeon™
    { 180, L"AS400 Family" },
    { 181, L"Intel(R) Xeon(TM) processor MP" },         // Intel Xeon™ Processor MP
    { 182, L"AMD AthlonXP(TM) Family" },                // AMD Athlon™ XP Family
    { 183, L"AMD AthlonMP(TM) Family" },                // AMD Athlon™ MP Family
    { 184, L"Intel(R) Itanium(R) 2" },                  // Intel Itanium 2
    { 185, L"Intel Pentium M Processor" },
    //
    //
    //
    { 190, L"K7" },
    //
    //
    //
    { 198, L"Intel Core(TM) i7 - 2760QM" },             // Intel Core™ i7 - 2760QM
    //
    //
    //
    { 200, L"IBM390 Family" },
    { 201, L"G4" },
    { 202, L"G5" },
    { 203, L"G6" },
    { 204, L"z / Architecture base" },
    //
    //
    //
    { 250, L"i860" },
    { 251, L"i960" },
    //
    //
    //
    { 260, L"SH - 3" },
    { 261, L"SH - 4" },
    //
    //
    //
    { 280, L"ARM" },
    { 281, L"StrongARM" },
    //
    //
    //
    { 300, L"6x86" },
    { 301, L"MediaGX" },
    { 302, L"MII" },
    //
    //
    //
    { 320, L"WinChip" },
    //
    //
    //
    { 350, L"DSP" },
    //
    //
    //
    { 500, L"Video Processor" }
};


const std::vector<std::string> CWin32ProcessorObject::propertyNames =
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
};
