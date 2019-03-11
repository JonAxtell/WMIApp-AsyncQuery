#include "pch.h"
#include "cvariant.h"
#include <sstream>
#include <iostream>

//#################################################################################################################################
//
bool CVariant::FromBool() const
{
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return false;
    }
    if (IsArray() || !CheckType(VT_BOOL))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.boolVal == VARIANT_TRUE;
}

//#################################################################################################################################
//
uint8_t CVariant::FromI1() const
{
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return 0;
    }
    if (IsArray() || (!CheckType(VT_I1) && !CheckType(VT_UI1)))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.bVal;
}

//#################################################################################################################################
//
uint16_t CVariant::FromI2() const
{
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return 0;
    }
    if (IsArray() || (!CheckType(VT_I2) && !CheckType(VT_UI2)))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.iVal;
}

//#################################################################################################################################
//
uint32_t CVariant::FromI4() const
{
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return 0;
    }
    if (IsArray() || (!CheckType(VT_I4) && !CheckType(VT_UI4)))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.lVal;
}

//#################################################################################################################################
//
std::wstring CVariant::FromBSTR() const
{
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return L"";
    }
    if (IsArray() || !CheckType(VT_BSTR))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return std::wstring(V_BSTR(&_variant));
}

//#################################################################################################################################
//
std::wstring CVariant::FromDATETIME() const
{
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return L"";
    }
    if (IsArray() || !CheckType(VT_I2))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    USHORT dosDate;
    USHORT dosTime;
    VariantTimeToDosDateTime(_variant.date, &dosDate, &dosTime);
    std::wostringstream buf;
    buf << ((dosDate & 0xFE00) >> 9) << "/" << ((dosDate & 0x1E0) >> 5) << "/" << ((dosDate & 0x001F) >> 0) <<
        ((dosTime & 0xF800) >> 11) << ":" << ((dosTime & 0x07E) >> 5) << ":" << ((dosTime & 0x001F) >> 0);
    return buf.str();
}

//#################################################################################################################################
//
std::vector<uint8_t> CVariant::FromArrayI1() const
{
    std::vector<uint8_t> array;
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return array;
    }
    if (!IsArray() || (!CheckType(VT_I1) && !CheckType(VT_UI1)))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    SAFEARRAY *pSafeArray = _variant.parray;
    long lower;
    long upper;
    SafeArrayGetLBound(pSafeArray, 1, &lower);
    SafeArrayGetUBound(pSafeArray, 1, &upper);
    for (long i = lower; i <= upper; ++i)
    {
        uint8_t elem;
        HRESULT hres = SafeArrayGetElement(pSafeArray, &i, &elem);
        if (FAILED(hres))
        {
            throw hres;
        }
        array.push_back(elem);
    }
    SafeArrayDestroy(pSafeArray);
    return array;
}

//#################################################################################################################################
//
std::vector<uint16_t> CVariant::FromArrayI2() const
{
    std::vector<uint16_t> array;
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return array;
    }
    if (!IsArray() || (!CheckType(VT_I2) && !CheckType(VT_UI2)))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    SAFEARRAY *pSafeArray = _variant.parray;
    long lower;
    long upper;
    SafeArrayGetLBound(pSafeArray, 1, &lower);
    SafeArrayGetUBound(pSafeArray, 1, &upper);
    for (long i = lower; i <= upper; ++i)
    {
        uint16_t elem;
        HRESULT hres = SafeArrayGetElement(pSafeArray, &i, &elem);
        if (FAILED(hres))
        {
            throw hres;
        }
        array.push_back(elem);
    }
    SafeArrayDestroy(pSafeArray);
    return array;
}

//#################################################################################################################################
//
std::vector<uint32_t> CVariant::FromArrayI4() const
{
    std::vector<uint32_t> array;
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return array;
    }
    if (!IsArray() || (!CheckType(VT_I4) && !CheckType(VT_UI4)))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    SAFEARRAY *pSafeArray = _variant.parray;
    long lower;
    long upper;
    SafeArrayGetLBound(pSafeArray, 1, &lower);
    SafeArrayGetUBound(pSafeArray, 1, &upper);
    for (long i = lower; i <= upper; ++i)
    {
        uint32_t elem;
        HRESULT hres = SafeArrayGetElement(pSafeArray, &i, &elem);
        if (FAILED(hres))
        {
            throw hres;
        }
        array.push_back(elem);
    }
    SafeArrayDestroy(pSafeArray);
    return array;
}

//#################################################################################################################################
//
std::vector<std::wstring> CVariant::FromArrayBSTR() const
{
    std::vector<std::wstring> array;
    if (NullOrEmpty())
    {
        //throw (HRESULT)ERROR_INVALID_VARIANT;
        return array;
    }
    if (!IsArray() || !CheckType(VT_BSTR))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    SAFEARRAY *pSafeArray = _variant.parray;
    long lower;
    long upper;
    SafeArrayGetLBound(pSafeArray, 1, &lower);
    SafeArrayGetUBound(pSafeArray, 1, &upper);
    for (long i = lower; i <= upper; ++i)
    {
        BSTR elem;
        HRESULT hres = SafeArrayGetElement(pSafeArray, &i, &elem);
        if (FAILED(hres))
        {
            throw hres;
        }
        array.push_back(std::wstring(elem));
    }
    SafeArrayDestroy(pSafeArray);
    return array;
}

//=================================================================================================================================
//
bool CVariant::NullOrEmpty() const
{
    if (_variant.vt == VT_NULL || _variant.vt == VT_EMPTY)
    {
        // Is null or empty.
        return true;
    }
    return false;
}

//=================================================================================================================================
//
bool CVariant::IsArray() const
{
    if (_variant.vt & (VT_VECTOR | VT_ARRAY | VT_BYREF))
    {
        // Is an array/vector/reference.
        return true;
    }
    return false;
}

//=================================================================================================================================
//
bool CVariant::CheckType(enum VARENUM type) const
{
    if ((_variant.vt & VT_TYPEMASK) == type)
    {
        // Is right type of individual, vector, array or reference
        return true;
    }
    return false;
}
