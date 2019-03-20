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
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return false;
#endif
    }
    if (IsArray() || !CheckType(VT_BOOL))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.boolVal == VARIANT_TRUE;
}

//#################################################################################################################################
//
signed char CVariant::FromI1() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_I1))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.cVal;
}

//#################################################################################################################################
//
signed short CVariant::FromI2() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_I2))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.iVal;
}

//#################################################################################################################################
//
signed long CVariant::FromI4() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_I4))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.lVal;
}

//#################################################################################################################################
//
signed long long CVariant::FromI8() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_I8))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.llVal;
}

//#################################################################################################################################
//
unsigned char CVariant::FromUI1() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_UI1))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.bVal;
}

//#################################################################################################################################
//
unsigned short CVariant::FromUI2() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_UI2))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.uiVal;
}

//#################################################################################################################################
//
unsigned long CVariant::FromUI4() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_UI4))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.ulVal;
}

//#################################################################################################################################
//
unsigned long long CVariant::FromUI8() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_UI8))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.ullVal;
}

//#################################################################################################################################
//
int CVariant::FromInt() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_INT))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.intVal;
}

//#################################################################################################################################
//
float CVariant::FromFloat() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_R4))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.fltVal;
}

//#################################################################################################################################
//
double CVariant::FromDouble() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return 0;
#endif
    }
    if (IsArray() || !CheckType(VT_R8))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.dblVal;
}

//#################################################################################################################################
//
std::wstring CVariant::FromDecimal() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return L"";
#endif
    }
    if (IsArray() || !CheckType(VT_DECIMAL))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    BSTR str;
    HRESULT hr;
    if ((hr = VarBstrFromDec(&_variant.decVal, 0, LOCALE_NOUSEROVERRIDE, &str)) != S_OK)
    {
        throw hr;
    }
    return std::wstring(str);
}

//#################################################################################################################################
//
std::wstring CVariant::FromCurrency() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return L"";
#endif
    }
    if (IsArray() || !CheckType(VT_CY))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    BSTR str;
    HRESULT hr;
    if ((hr = VarBstrFromCy(_variant.cyVal, 0, LOCALE_NOUSEROVERRIDE, &str)) != S_OK)
    {
        throw hr;
    }
    return std::wstring(str);
}

//#################################################################################################################################
//
std::wstring CVariant::FromBSTR() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return L"";
#endif
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
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return L"";
#endif
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
std::vector<signed char> CVariant::FromArrayI1() const
{
    std::vector<signed char> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_I1))
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
        signed char elem;
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
std::vector<signed short> CVariant::FromArrayI2() const
{
    std::vector<signed short> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_I2))
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
        signed short elem;
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
std::vector<signed long> CVariant::FromArrayI4() const
{
    std::vector<signed long> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_I4))
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
        signed long elem;
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
std::vector<signed long long> CVariant::FromArrayI8() const
{
    std::vector<signed long long> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_I8))
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
        signed long long elem;
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
std::vector<unsigned char> CVariant::FromArrayUI1() const
{
    std::vector<unsigned char> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_UI1))
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
        unsigned char elem;
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
std::vector<unsigned short> CVariant::FromArrayUI2() const
{
    std::vector<unsigned short> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_UI2))
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
        unsigned short elem;
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
std::vector<unsigned long> CVariant::FromArrayUI4() const
{
    std::vector<unsigned long> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_UI4))
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
        unsigned long elem;
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
std::vector<unsigned long long> CVariant::FromArrayUI8() const
{
    std::vector<unsigned long long> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_UI8))
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
        unsigned long long elem;
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
std::vector<int> CVariant::FromArrayInt() const
{
    std::vector<int> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_INT))
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
        int elem;
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
std::vector<float> CVariant::FromArrayFloat() const
{
    std::vector<float> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_R4))
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
        float elem;
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
std::vector<double> CVariant::FromArrayDouble() const
{
    std::vector<double> array;
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
    }
    if (!IsArray() || !CheckType(VT_R8))
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
        double elem;
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
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return array;
#endif
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

//#################################################################################################################################
//
void* CVariant::FromReference() const
{
    if (NullOrEmpty())
    {
#ifdef CVARIANT_THROW_ON_NULL_OR_EMPTY
        throw (HRESULT)ERROR_INVALID_VARIANT;
#else
        return nullptr;
#endif
    }
    if (IsArray() || !CheckType(VT_PTR))
    {
        throw (HRESULT)ERROR_INVALID_VARIANT;
    }
    return _variant.byref;
}

//#################################################################################################################################
//
bool CVariant::operator==(const bool& other) const
{
    if (this->Type() != VT_BOOL)
    {
        return false;
    }
    return (static_cast<bool>(this->_variant.boolVal) == other);
}

//#################################################################################################################################
//
bool CVariant::operator==(const int& other) const
{
    switch (this->Type())
    {
        case VT_INT:
        {
            return (this->_variant.iVal == other);
        }
        case VT_I1:
        {
            return (this->_variant.cVal == other);
        }
        case VT_I2:
        {
            return (this->_variant.iVal == other);
        }
        case VT_I4:
        {
            return (this->_variant.lVal == other);
        }
        case VT_I8:
        {
            return (this->_variant.llVal == other);
        }
    }
    return false;
}

//#################################################################################################################################
//
bool CVariant::operator==(const CVariant& other) const
{
    if (this->Type() != other.Type())
    {
        return false;
    }
    switch (this->Type())
    {
        case VT_EMPTY:
        case VT_NULL:
        {
            return true;
        }
        case VT_BOOL:
        {
            return this->_variant.boolVal == other._variant.boolVal;
        }
        case VT_I1:
        {
            return this->_variant.cVal == other._variant.cVal;
        }
        case VT_I2:
        {
            return this->_variant.iVal == other._variant.iVal;
        }
        case VT_I4:
        {
            return this->_variant.lVal == other._variant.lVal;
        }
        case VT_I8:
        {
            return this->_variant.llVal == other._variant.llVal;
        }
        case VT_UI1:
        {
            return this->_variant.bVal == other._variant.bVal;
        }
        case VT_UI2:
        {
            return this->_variant.uiVal == other._variant.uiVal;
        }
        case VT_UI4:
        {
            return this->_variant.ulVal == other._variant.ulVal;
        }
        case VT_UI8:
        {
            return this->_variant.ullVal == other._variant.ullVal;
        }
        case VT_INT:
        {
            return this->_variant.intVal == other._variant.intVal;
        }
        case VT_R4:
        {
            return this->_variant.fltVal == other._variant.fltVal;
        }
        case VT_R8:
        {
            return this->_variant.dblVal == other._variant.dblVal;
        }
        case VT_BSTR:
        {
            return this->_variant.bstrVal == other._variant.bstrVal;
        }
        case VT_CY:
        {
            return this->_variant.cyVal.int64 == other._variant.cyVal.int64;
        }
        case VT_DATE:
        {
            return this->_variant.date == other._variant.date;
        }
    }
    throw (HRESULT)ERROR_INVALID_VARIANT;
}

//#################################################################################################################################
//
bool CVariant::operator==(const CVariant* other) const
{
    return *this == *other;
}

//#################################################################################################################################
//
bool CVariant::operator!=(const CVariant& other) const
{
    return !(*this == other);
}

//#################################################################################################################################
//
bool CVariant::operator!=(const CVariant* other) const
{
    return !(*this == *other);
}

//#################################################################################################################################
//
std::wostream& operator<<(std::wostream& os, const CVariant& v)
{
    switch (v.Type())
    {
        case VT_EMPTY:
        {
            os << L"EMPTY";
            break;
        }
        case VT_NULL:
        {
            os << L"NULL";
            break;
        }
        case VT_BOOL:
        {
            if ((bool)(v._variant.boolVal))
            {
                os << L"True";
            }
            else
            {
                os << L"False";
            }
            break;
        }
        case VT_I1:
        {
            os << (signed int)v._variant.cVal;          // Cast to int to get number not ASCII character
            break;
        }
        case VT_I2:
        {
            os << v._variant.iVal;
            break;
        }
        case VT_I4:
        {
            os << v._variant.lVal;
            break;
        }
        case VT_I8:
        {
            os << v._variant.llVal;
            break;
        }
        case VT_UI1:
        {
            os << (unsigned int)v._variant.bVal;        // Cast to int to get number not ASCII character
            break;
        }
        case VT_UI2:
        {
            os << v._variant.uiVal;
            break;
        }
        case VT_UI4:
        {
            os << v._variant.ulVal;
            break;
        }
        case VT_UI8:
        {
            os << v._variant.ullVal;
            break;
        }
        case VT_INT:
        {
            os << v._variant.intVal;
            break;
        }
        case VT_R4:
        {
            os << v._variant.fltVal;
            break;
        }
        case VT_R8:
        {
            os << v._variant.dblVal;
            break;
        }
        case VT_BSTR:
        {
            os << v.FromBSTR();
            break;
        }
        case VT_CY:
        {
            os << v.FromCurrency();
            break;
        }
        case VT_DATE:
        {
            os << v.FromDATETIME();
            break;
        }
        default:
        {
            os << L"????";
            break;
        }
    }
    return os;
}

std::wstring CVariant::ToString() const
{
    std::wstringstream strstream;

    strstream << _variant;
    return strstream.str();
}

//=================================================================================================================================
//
bool CVariant::NullOrEmpty() const
{
    if (Type() == VT_NULL || Type() == VT_EMPTY)
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
    if (Type() & (VT_VECTOR | VT_ARRAY | VT_BYREF))
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
    if ((Type() & VT_TYPEMASK) == type)
    {
        // Is right type of individual, vector, array or reference
        return true;
    }
    return false;
}
