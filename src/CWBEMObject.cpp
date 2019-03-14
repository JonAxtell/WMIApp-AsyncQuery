#include "pch.h"
#include "CWBEMObject.h"

const char* CWBEMObject::_availabilityValues[] =
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

const char* CWBEMObject::_configManagerErrorCodeValues[] =
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

//#################################################################################################################################
//
// Retrieves all the data for a WBEM object and populates the array of variants
//
// Parameters:
//      propertyNames - vector of strings of all the properties known to the object
//      pObjElem - pointer to WBEM object
//
// Members:
//      _properties
//
// Notes:
// Uncomment the throw or std::cout line if unrecognised properties are an error or should be noted
//
void CWBEMObject::Populate(const char** propertyNames, IWbemClassObject __RPC_FAR * pwbemObj)
{
    _properties.clear();
    _properties.reserve(PropertyCount());
    for (unsigned int i = 0; i < PropertyCount(); ++i)
    {
        // Convert the ASCII propery name into UTF16 for the call to the Windows API
        std::wstring name(propertyNames[i], propertyNames[i] + strlen(propertyNames[i]));

        // Get the property's value
        VARIANT var;
        HRESULT hres = pwbemObj->Get(name.c_str(), 0, &var, 0, 0);
        if (FAILED(hres))
        {
            var.vt = VT_NULL;
            //std::cout << std::string("CWBEMObject::Populate Failed to get ") + propertyNames[i] + std::string(". Error code = 0x") + NumberToHex(hres) << std::endl;
            //throw std::runtime_error(std::string("CWBEMObject::Populate Failed to get ") + propertyNames.at(i) + std::string(". Error code = 0x") + NumberToHex(hres));
        }

        // Convert the Windows VARIANT type into a CVariant for internal use and put into the list of properties for the object
        _properties.push_back(new CVariant(var));
    }
}

//#################################################################################################################################
//
std::wostream& operator<<(std::wostream& os, const CWBEMObject::CAvailability& a)
{
    os << a.Text().c_str();
    return os;
}

//#################################################################################################################################
//
std::wostream& operator<<(std::wostream& os, const CWBEMObject::CConfigManagerErrorCode& e)
{
    os << e.Text().c_str();
    return os;
}
