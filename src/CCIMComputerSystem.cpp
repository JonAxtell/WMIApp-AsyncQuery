#include "pch.h"
#include "CCIMComputerSystem.h"

const std::string CCIMComputerSystemObject::ObjectName("CIM_ComputerSystem");

const std::vector<std::string> CCIMComputerSystemObject::propertyNames =
{
    "Caption",
    "Description",
    "InstallDate",
    "Status",
    "CreationClassName",
    "Name",
    "PrimaryOwnerContact",
    "PrimaryOwnerName",
    "Roles",
    "NameFormat",
};
