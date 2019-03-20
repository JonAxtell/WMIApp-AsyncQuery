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
    // Default constructor
    CVariant() { _variant.vt = VT_EMPTY; };

    // Copy constructors
    CVariant(const CVariant& variant) { _variant = variant._variant; }
    CVariant(const VARIANT& variant) { _variant = variant; }

    // Move constructors
    CVariant(CVariant&& variant) { _variant = variant._variant; }
    CVariant(VARIANT&& variant) { _variant = variant; }

    // Assignment operators
    CVariant& operator=(CVariant v) 
    {
        this->swap(v);
        return *this;
    }
    CVariant& operator=(CVariant&& v)
    {
        this->swap(v);
        return *this;
    }
    ~CVariant() { _variant.vt = VT_EMPTY; }

    // Public swap function for use in move operations
    friend void swap(CVariant& first, CVariant& second)
    {
        first.swap(second);
    }

    void swap(CVariant &other)
    {
        using std::swap;

        swap(_variant, other._variant);
    }

    const VARTYPE Type() const { return _variant.vt; }

    // Conversion methods
    bool FromBool() const;
    signed char FromI1() const;
    signed short FromI2() const;
    signed long FromI4() const;
    signed long long FromI8() const;
    unsigned char FromUI1() const;
    unsigned short FromUI2() const;
    unsigned long FromUI4() const;
    unsigned long long FromUI8() const;
    int FromInt() const;
    float FromFloat() const;
    double FromDouble() const;
    std::wstring FromDecimal() const;
    std::wstring FromCurrency() const;
    std::wstring FromBSTR() const;
    std::wstring FromDATETIME() const;
    std::vector<signed char> FromArrayI1() const;
    std::vector<signed short> FromArrayI2() const;
    std::vector<signed long> FromArrayI4() const;
    std::vector<signed long long> FromArrayI8() const;
    std::vector<unsigned char> FromArrayUI1() const;
    std::vector<unsigned short> FromArrayUI2() const;
    std::vector<unsigned long> FromArrayUI4() const;
    std::vector<unsigned long long> FromArrayUI8() const;
    std::vector<int> FromArrayInt() const;
    std::vector<float> FromArrayFloat() const;
    std::vector<double> FromArrayDouble() const;
    std::vector<std::wstring> FromArrayBSTR() const;
    void* FromReference() const;

    // Convert any variant into string form
    std::wstring ToString() const;

    // Conversion methods when using casting
    explicit operator bool() const { return FromBool(); }
    explicit operator signed char() const { return FromI1(); }
    explicit operator signed short() const { return FromI2(); }
    explicit operator signed long() const { return FromI4(); }
    explicit operator signed long long() const { return FromI8(); }
    explicit operator unsigned char() const { return FromUI1(); }
    explicit operator unsigned short() const { return FromUI2(); }
    explicit operator unsigned long() const { return FromUI4(); }
    explicit operator unsigned long long() const { return FromUI8(); }
    explicit operator int() const { return FromInt(); }
    explicit operator float() const { return FromFloat(); }
    explicit operator double() const { return FromDouble(); }
    explicit operator std::wstring() const
    { 
        switch (_variant.vt)
        {
            case VT_DECIMAL:
            {
                return FromDecimal();
            }
            case VT_CY:
            {
                return FromCurrency();
            }
            case VT_DATE:
            {
                return FromDATETIME();
            }
            default:
            {
                return FromBSTR();
            }
        }
    }

    // Logical operators
    bool operator==(const CVariant& other) const;
    bool operator==(const CVariant* other) const;
    bool operator!=(const CVariant& other) const;
    bool operator!=(const CVariant* other) const;

    // Useful logical operators, limited to common types
    bool operator==(const bool& other) const;
    bool operator==(const int& other) const;

    // Streaming operators
    friend std::wostream& operator<<(std::wostream& os, const CVariant& v);

private:
    bool NullOrEmpty() const;
    bool IsArray() const;
    bool CheckType(enum VARENUM type) const;

    VARIANT _variant;
};
