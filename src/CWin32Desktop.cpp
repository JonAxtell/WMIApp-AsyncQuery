#include "pch.h"
#include "CWin32Desktop.h"

const char* CWin32DesktopObject::ObjectName = "Win32_Desktop";

const char* CWin32DesktopObject::propertyNames[] =
{
    "Caption",
    "Description",
    "SettingID",
    "BorderWidth",
    "CoolSwitch",
    "CursorBlinkRate",
    "DragFullWindows",
    "GridGranularity",
    "IconSpacing",
    "IconTitleFaceName",
    "IconTitleSize",
    "IconTitleWrap",
    "Name",
    "Pattern",
    "ScreenSaverActive",
    "ScreenSaverExecutable",
    "ScreenSaverSecure",
    "ScreenSaverTimeout",
    "Wallpaper",
    "WallpaperStretched",
    "WallpaperTiled",
    NULL
};
