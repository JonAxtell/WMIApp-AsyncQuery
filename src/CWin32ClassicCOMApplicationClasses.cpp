#include "pch.h"
#include "CWin32ClassicCOMApplicationClasses.h"

const char* CWin32ClassicCOMApplicationClassesObject::ObjectName = "Win32_ClassicCOMApplicationClasses";

const char* CWin32ClassicCOMApplicationClassesObject::propertyNames[] =
{
    "PartComponent",
    "GroupComponent",
    NULL
};

std::wstring CWin32ClassicCOMApplicationClassesObject::PartComponentGUID()
{
    std::wstring part = (*Properties().at(PROP_PartComponent)).FromBSTR();
    size_t open = part.find_first_of(L'{');
    size_t close = part.find_last_of(L'}');
    if ((open == std::wstring::npos) || (close == std::wstring::npos))
    {
        return L"";
    }
    return part.substr(open, close);
}

std::wstring CWin32ClassicCOMApplicationClassesObject::GroupComponentGUID()
{
    std::wstring group = (*Properties().at(PROP_GroupComponent)).FromBSTR();
    size_t open = group.find_first_of(L'{');
    size_t close = group.find_last_of(L'}');
    if ((open == std::wstring::npos) || (close == std::wstring::npos))
    {
        return L"";
    }
    return group.substr(open, close);
}

