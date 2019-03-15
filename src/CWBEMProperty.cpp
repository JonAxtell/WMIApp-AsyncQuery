#include "pch.h"
#include "CWBEMProperty.h"

//#################################################################################################################################
//
const char* CWBEMProperty_Availability::_values[] =
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

std::wostream& operator<<(std::wostream& os, const CWBEMProperty_Availability& a)
{
    os << a.Text().c_str();
    return os;
}

//#################################################################################################################################
//
const char* CWBEMProperty_ConfigManagerErrorCode::_values[] =
{
    "This device is working properly. (0)",
    "This device is not configured correctly. (1)",
    "Windows cannot load the driver for this device. (2)",
    "The driver for this device might be corrupted, or your system may be running low on memory or other resources. (3)",
    "This device is not working properly.One of its drivers or your registry might be corrupted. (4)",
    "The driver for this device needs a resource that Windows cannot manage. (5)",
    "The boot configuration for this device conflicts with other devices. (6)",
    "Cannot filter. (7)",
    "The driver loader for the device is missing. (8)",
    "This device is not working properly because the controlling firmware is reporting the resources for the device incorrectly. (9)",
    "This device cannot start. (10)",
    "This device failed. (11)",
    "This device cannot find enough free resources that it can use. (12)",
    "Windows cannot verify this device's resources. (13)",
    "This device cannot work properly until you restart your computer. (14)",
    "This device is not working properly because there is probably a re - enumeration problem. (15)",
    "Windows cannot identify all the resources this device uses. (16)",
    "This device is asking for an unknown resource type. (17)",
    "Reinstall the drivers for this device. (18)",
    "Failure using the VxD loader. (19)",
    "Your registry might be corrupted. (20)",
    "System failure : Try changing the driver for this device.If that does not work, see your hardware documentation.Windows is removing this device. (21)",
    "This device is disabled. (22)",
    "System failure : Try changing the driver for this device.If that doesn't work, see your hardware documentation. (23)",
    "This device is not present, is not working properly, or does not have all its drivers installed. (24)",
    "Windows is still setting up this device. (25)",
    "Windows is still setting up this device. (26)",
    "This device does not have valid log configuration. (27)",
    "The drivers for this device are not installed. (28)",
    "This device is disabled because the firmware of the device did not give it the required resources. (29)",
    "This device is using an Interrupt Request(IRQ) resource that another device is using. (30)",
    "This device is not working properly because Windows cannot load the drivers required for this device. (31)",
};

std::wostream& operator<<(std::wostream& os, const CWBEMProperty_ConfigManagerErrorCode& e)
{
    os << e.Text().c_str();
    return os;
}
