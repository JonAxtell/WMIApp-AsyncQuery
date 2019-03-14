#pragma once

#include "pch.h"
#include "CVariant.h"
#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#ifndef __MINGW_GCC_VERSION
#pragma comment(lib, "wbemuuid.lib")
#endif
#include <vector>
#include <memory>

//#################################################################################################################################
//
// Template that insantiates potentially multiple instances of CWBEMObjects.
//
// The template provides the constructor, destructor and assignment operater to handle the array of pointers to the possibly
// multiple number of objects. Pointers to the CWBEMObjects are used as the individual WBEM objects derive from the CWBEMObject
// class and they can be different sizes.
//
template<class CWBEMOBJECT>
class TWBEMObjects
{
public:
    // Default constructor
    TWBEMObjects() {}

    // Copy constructor (does a deep copy of the whole vector)
    TWBEMObjects(const TWBEMObjects& objs)
    {
        for (auto p : objs._objects)
        {
            _objects.push_back(new CWBEMOBJECT(*p));
        }
    }

    // Move constructor (just transfers the vector)
    TWBEMObjects(TWBEMObjects&& objs)
    {
        _objects = objs._objects;
        objs.clear();
    }

    // Destructor, deletes all objects in the vector
    ~TWBEMObjects()
    {
        for (typename std::vector<CWBEMOBJECT* >::iterator o = _objects.begin(); o != _objects.end(); ++o)
        {
            delete (*o);
            (*o) = nullptr;
        }
        _objects.clear();
    }

    // Copy assignment (does a deep copy of the whole vector)
    TWBEMObjects& operator=(const TWBEMObjects& objs)
    {
        for (auto p : objs._objects)
        {
            _objects.push_back(new CWBEMOBJECT(p));
        }
        return *this;
    }

    // Move assignment (just transfers the vector)
    TWBEMObjects& operator=(TWBEMObjects&& objs)
    {
        _objects = objs._objects;
        objs.clear();
        return *this;
    }

    // Some methods to provide an interface similar to std::vector's
    CWBEMOBJECT* at(int i) { return _objects.at(i); }
    void push_back(const CWBEMOBJECT& obj) { _objects.push_back(obj); }
    void push_back(CWBEMOBJECT&& obj) { _objects.push_back(&obj); }
    size_t size() { return _objects.size(); }
    void clear() { _objects.clear(); }

    std::vector<CWBEMOBJECT* >& Objects() { return _objects; }

private:
    std::vector<CWBEMOBJECT* > _objects;
};
