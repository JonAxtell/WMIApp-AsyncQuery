#include "pch.h"
#include "CWin32BIOS.h"

const std::string CWin32BIOSObject::ObjectName("Win32_Bios");

const std::vector<std::string> CWin32BIOSObject::propertyNames =
{
    "BiosCharacteristics",
    "BIOSVersion",
    "BuildNumber",
    "Caption",
    "CodeSet",
    "CurrentLanguage",
    "Description",
    "EmbeddedControllerMajorVersion",
    "EmbeddedControllerMinorVersion",
    "IdentificationCode",
    "InstallableLanguages",
    "InstallDate",
    "LanguageEdition",
    "ListOfLanguages",
    "Manufacturer",
    "Name",
    "OtherTargetOS",
    "PrimaryBIOS",
    "ReleaseDate",
    "SerialNumber",
    "SMBIOSBIOSVersion",
    "SMBIOSMajorVersion",
    "SMBIOSMinorVersion",
    "SMBIOSPresent",
    "SoftwareElementID",
    "SoftwareElementState",
    "Status",
    "SystemBiosMajorVersion",
    "SystemBiosMinorVersion",
    "TargetOperatingSystem",
    "Version",
};
