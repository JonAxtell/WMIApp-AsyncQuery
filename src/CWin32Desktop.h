#pragma once

#include "pch.h"
#include "CWBEMObjectSink.h"
#include "CWBEMObjectQuery.h"
#include "CWBEMObject.h"
#include "CVariant.h"
#include <string>
#include <vector>

//#################################################################################################################################
//
class CWin32DesktopObject : public CWBEMObject
{
public:
    static const char* ObjectName;

    enum propertyEnum
    {
        PROP_Caption,
        PROP_Description,
        PROP_SettingID,
        PROP_BorderWidth,
        PROP_CoolSwitch,
        PROP_CursorBlinkRate,
        PROP_DragFullWindows,
        PROP_GridGranularity,
        PROP_IconSpacing,
        PROP_IconTitleFaceName,
        PROP_IconTitleSize,
        PROP_IconTitleWrap,
        PROP_Name,
        PROP_Pattern,
        PROP_ScreenSaverActive,
        PROP_ScreenSaverExecutable,
        PROP_ScreenSaverSecure,
        PROP_ScreenSaverTimeout,
        PROP_Wallpaper,
        PROP_WallpaperStretched,
        PROP_WallpaperTiled,
    };

    CWin32DesktopObject() {}
    CWin32DesktopObject(const CWin32DesktopObject&) = default;
    CWin32DesktopObject(CWin32DesktopObject&&) = default;
    ~CWin32DesktopObject() {}
    CWin32DesktopObject& operator=(const CWin32DesktopObject&) = default;
    CWin32DesktopObject& operator=(CWin32DesktopObject&&) = default;

    const char* PropertyName(int prop) { return propertyNames[prop]; }

    std::wstring Caption() { return (*Properties().at(PROP_Caption)).FromBSTR(); }
    std::wstring Description() { return (*Properties().at(PROP_Description)).FromBSTR(); }
    std::wstring Name() { return (*Properties().at(PROP_Name)).FromBSTR(); }

public:
    static const char* propertyNames[];
};
