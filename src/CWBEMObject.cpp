#include "pch.h"
#include "CWBEMObject.h"

//#################################################################################################################################
//
std::vector<CWBEMObject::index_property_t> CWBEMObject::Properties(enum VARENUM type) const
{
    std::vector<index_property_t> props;

    for (auto &p : _properties)
    {
        if (p->Type() == type)
        {
            index_property_t item;
            item.first = static_cast<int>(&p - &_properties[0]);
            item.second = p;
            props.push_back(item);
        }
    }
    return props;
}

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
        _properties.push_back(new CWBEMProperty(var));
    }
}
