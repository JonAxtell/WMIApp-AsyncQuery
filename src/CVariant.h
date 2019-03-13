#pragma once

#include "pch.h"
#include <oaidl.h>
#include <cstdio>
#include <string>
#include <vector>
#include <stdint.h>

//#################################################################################################################################
//
// Encapsulates the windows VARIANT type with methods to convert into standard C++ types.
// Only for use as a read only object.
//
class CVariant
{
public:
    //CVariant() : _variant() {};
    CVariant(const VARIANT& variant) : _variant(variant) {}
    ~CVariant() {}
    CVariant& operator=(const CVariant& v) 
    {
        _variant = v._variant;
        return *this;
    }

    VARTYPE Type() { return _variant.vt; }

    bool FromBool() const;
    uint8_t FromI1() const;
    uint16_t FromI2() const;
    uint32_t FromI4() const;
    std::wstring FromBSTR() const;
    std::wstring FromDATETIME() const;
    std::vector<uint8_t> FromArrayI1() const;
    std::vector<uint16_t> FromArrayI2() const;
    std::vector<uint32_t> FromArrayI4() const;
    std::vector<std::wstring> FromArrayBSTR() const;

private:
    bool NullOrEmpty() const;
    bool IsArray() const;
    bool CheckType(enum VARENUM type) const;

    VARIANT _variant;
};
