#include "pch.h"
#include "CWBEMObject.h"

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
// Throws:
//      HRESULT
//
void CWBEMObject::Populate(const std::vector<std::string>& propertyNames, IWbemClassObject __RPC_FAR * pwbemObj)
{
    _properties.clear();
    _properties.reserve(propertyNames.size());
    for (unsigned int i = 0; i < propertyNames.size(); ++i)
    {
        VARIANT var;
        std::wstring name;
        name.append(propertyNames.at(i).begin(), propertyNames.at(i).end());
        HRESULT hres = pwbemObj->Get(name.c_str(), 0, &var, 0, 0);
        if (FAILED(hres))
        {
            var.vt = VT_NULL;
            std::cout << std::string("CWBEMObject::Populate Failed to get ") + propertyNames.at(i) + std::string(". Error code = 0x") + NumberToHex(hres) << std::endl;
            //throw std::runtime_error(std::string("CWBEMObject::Populate Failed to get ") + propertyNames.at(i) + std::string(". Error code = 0x") + NumberToHex(hres));
        }
        std::shared_ptr<CVariant> cvar = std::make_shared<CVariant>(var);
        _properties.push_back(cvar);
    }
}
