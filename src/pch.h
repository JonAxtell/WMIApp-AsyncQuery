// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
//#define _CRTDBG_MAP_ALLOC  
#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

#include <windows.h>
#include <string>

#ifdef __MINGW_GCC_VERSION
#define ERROR_INVALID_VARIANT   604L
#endif

template <typename I> std::string NumberToHex(I w, size_t hex_len = sizeof(I) << 1)
{
    static const char* digits = "0123456789ABCDEF";
    std::string rc(hex_len, '0');
    for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
    {
        rc[i] = digits[(w >> j) & 0x0f];
    }
    return rc;
}

//implement our own conversion functions

//------------------------//
// Convert char * to BSTR //
//------------------------//
inline BSTR ConvertStringToBSTR(const char* pSrc)
{
    if (!pSrc) return NULL;

    DWORD cwch;

    BSTR wsOut(NULL);

    if ((cwch = ::MultiByteToWideChar(CP_ACP, 0, pSrc, -1, NULL, 0)) != 0)//get size minus NULL terminator
    {
        cwch--;
        wsOut = ::SysAllocStringLen(NULL, cwch);
        if (wsOut)
        {
            if (!::MultiByteToWideChar(CP_ACP, 0, pSrc, -1, wsOut, cwch))
            {
                if (ERROR_INSUFFICIENT_BUFFER == ::GetLastError())
                {
                    return wsOut;
                }
                ::SysFreeString(wsOut);//must clean up
                wsOut = NULL;
            }
        }

    };

    return wsOut;
};

//------------------------//
// Convert BSTR to char * //
//------------------------//
inline char* ConvertBSTRToString(BSTR pSrc)
{
    if (!pSrc) return NULL;

    //convert even embeded NULL
    DWORD cb, cwch = ::SysStringLen(pSrc);

    char *szOut = NULL;

    if ((cb = ::WideCharToMultiByte(CP_ACP, 0, pSrc, cwch + 1, NULL, 0, 0, 0)) != 0)
    {
        szOut = new char[cb];
        if (szOut)
        {
            szOut[cb - 1] = '\0';

            if (!::WideCharToMultiByte(CP_ACP, 0, pSrc, cwch + 1, szOut, cb, 0, 0))
            {
                delete[]szOut;//clean up if failed;
                szOut = NULL;
            }
        }
    }

    return szOut;
};

#endif //PCH_H
