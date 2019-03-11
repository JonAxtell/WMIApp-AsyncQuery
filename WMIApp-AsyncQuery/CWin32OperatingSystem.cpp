#include "pch.h"
#include "CWin32OperatingSystem.h"

const std::string CWin32OperatingSystemObject::ObjectName("Win32_OperatingSystem");

static const std::vector<std::string> OperatingSystemSKUNames =
{
    "An unknown product",                                                           //0
    "Ultimate",                                                                     //1
    "Home Basic",                                                                   //2
    "Home Premium",                                                                 //3
    "Enterprise",                                                                   //4
    "Home Basic N",                                                                 //5
    "Business",                                                                     //6
    "Server Standard",                                                              //7
    "Server Datacenter(full installation)",                                         //8
    "Windows Small Business Server",                                                //9
    "Server Enterprise(full installation)",                                         //10
    "Starter",                                                                      //11
    "Server Datacenter(core installation)",                                         //12
    "Server Standard(core installation)",                                           //13
    "Server Enterprise(core installation)",                                         //14
    "Server Enterprise for Itanium - based Systems",                                //15
    "Business N",                                                                   //16
    "Web Server(full installation)",                                                //17
    "HPC Edition",                                                                  //18
    "Windows Storage Server 2008 R2 Essentials",                                    //19
    "Storage Server Express",                                                       //20
    "Storage Server Standard",                                                      //21
    "Storage Server Workgroup",                                                     //22
    "Storage Server Enterprise",                                                    //23
    "Windows Server 2008 for Windows Essential Server Solutions",                   //24
    "Small Business Server Premium",                                                //25
    "Home Premium N",                                                               //26
    "Enterprise N",                                                                 //27
    "Ultimate N",                                                                   //28
    "Web Server(core installation)",                                                //29
    "Windows Essential Business Server Management Server",                          //30
    "Windows Essential Business Server Security Server",                            //31
    "Windows Essential Business Server Messaging Server",                           //32
    "Server Foundation",                                                            //33
    "Windows Home Server 2011",                                                     //34
    "Windows Server 2008 without Hyper - V for Windows Essential Server Solutions", //35
    "Server Standard without Hyper - V",                                            //36
    "Server Datacenter without Hyper - V(full installation)",                       //37
    "Server Enterprise without Hyper - V(full installation)",                       //38
    "Server Datacenter without Hyper - V(core installation)",                       //39
    "Server Standard without Hyper - V(core installation)",                         //40
    "Server Enterprise without Hyper - V(core installation)",                       //41
    "Microsoft Hyper - V Server",                                                   //42
    "Storage Server Express(core installation)",                                    //43
    "Storage Server Standard(core installation)",                                   //44
    "Storage Server Workgroup(core installation)",                                  //45
    "Storage Server Enterprise(core installation)",                                 //46
    "Starter N",                                                                    //47
    "Professional",                                                                 //48
    "Professional N",                                                               //49
    "Windows Small Business Server 2011 Essentials",                                //50
    "Server For SB Solutions",                                                      //51
    "Server Solutions Premium",                                                     //52
    "Server Solutions Premium(core installation)",                                  //53
    "Server For SB Solutions EM",                                                   //54
    "Server For SB Solutions EM",                                                   //55
    "Windows MultiPoint Server",                                                    //56
    "",                                                                             //57
    "",                                                                             //58
    "Windows Essential Server Solution Management",                                 //59
    "Windows Essential Server Solution Additional",                                 //60
    "Windows Essential Server Solution Management SVC",                             //61
    "Windows Essential Server Solution Additional SVC",                             //62
    "Small Business Server Premium(core installation)",                             //63
    "Server Hyper Core V",                                                          //64
    "",                                                                             //65
    "Starter E",                                                                    //66
    "Home Basic E",                                                                 //67
    "Home Premium E",                                                               //68
    "Professional E",                                                               //69
    "Enterprise E",                                                                 //70
    "Ultimate E",                                                                   //71
    "Server Enterprise(evaluation installation)",                                   //72
    "",                                                                             //73
    "",                                                                             //74
    "",                                                                             //75
    "Windows MultiPoint Server Standard(full installation)",                        //76
    "Windows MultiPoint Server Premium(full installation)",                         //77
    "",                                                                             //78
    "Server Standard(evaluation installation)",                                     //79
    "Server Datacenter(evaluation installation)",                                   //80
    "",                                                                             //81
    "",                                                                             //82
    "",                                                                             //83
    "Enterprise N(evaluation installation)",                                        //84
    "",                                                                             //85
    "",                                                                             //86
    "",                                                                             //87
    "",                                                                             //88
    "",                                                                             //89
    "",                                                                             //90
    "",                                                                             //91
    "",                                                                             //92
    "",                                                                             //93
    "",                                                                             //94
    "Storage Server Workgroup(evaluation installation)",                            //95
    "Storage Server Standard(evaluation installation)",                             //96
    "",                                                                             //97
    "Windows 8 N",                                                                  //98
    "Windows 8 China",                                                              //99
    "Windows 8 Single Language",                                                    //100
    "Windows 8",                                                                    //101
    "",                                                                             //102
    "Professional with Media Center",                                               //103
};

const std::vector<std::string> CWin32OperatingSystemObject::propertyNames =
{
    "BootDevice",
    "BuildNumber",
    "BuildType",
    "Caption",
    "CodeSet",
    "CountryCode",
    "CreationClassName",
    "CSCreationClassName",
    "CSDVersion",
    "CSName",
    "CurrentTimeZone",
    "DataExecutionPrevention_Available",
    "DataExecutionPrevention_32BitApplications",
    "DataExecutionPrevention_Drivers",
    "DataExecutionPrevention_SupportPolicy",
    "Debug",
    "Description",
    "Distributed",
    "EncryptionLevel",
    "ForegroundApplicationBoost",
    "FreePhysicalMemory",
    "FreeSpaceInPagingFiles",
    "FreeVirtualMemory",
    "InstallDate",
    "LargeSystemCache",
    "LastBootUpTime",
    "LocalDateTime",
    "Locale",
    "Manufacturer",
    "MaxNumberOfProcesses",
    "MaxProcessMemorySize",
    "MUILanguages",
    "Name",
    "NumberOfLicensedUsers",
    "NumberOfProcesses",
    "NumberOfUsers",
    "OperatingSystemSKU",
    "Organization",
    "OSArchitecture",
    "OSLanguage",
    "OSProductSuite",
    "OSType",
    "OtherTypeDescription",
    "PAEEnabled",
    "PlusProductID",
    "PlusVersionNumber",
    "PortableOperatingSystem",
    "Primary",
    "ProductType",
    "QuantumLength",
    "QuantumType",
    "RegisteredUser",
    "SerialNumber",
    "ServicePackMajorVersion",
    "ServicePackMinorVersion",
    "SizeStoredInPagingFiles",
    "Status",
    "SuiteMask",
    "SystemDevice",
    "SystemDirectory",
    "SystemDrive",
    "TotalSwapSpaceSize",
    "TotalVirtualMemorySize",
    "TotalVisibleMemorySize",
    "Version",
    "WindowsDirectory",
};
