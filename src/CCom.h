#pragma once

#include "pch.h"

//#################################################################################################################################
//
class CCOM
{
public:
    // COINIT_MULTITHREADED or COINIT_APARTMENTTHREADED
    CCOM(COINIT model);
    ~CCOM();

    void InitializeSecurity();

private:
    CCOM(const CCOM&) = delete;
    CCOM& operator=(const CCOM&) = delete;
    CCOM* operator&() = delete;
};
