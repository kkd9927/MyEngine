#include "Engine/Runtime/DebugConsole.h"

#include <windows.h>
#include <iostream>

namespace Engine
{
    void DebugConsole::ShowConsole(bool visible) {
        HWND consoleWindow = GetConsoleWindow();
        if (consoleWindow) {
            ShowWindow(consoleWindow, visible ? SW_SHOW : SW_HIDE);
        }
    }

    DebugConsole::DebugConsole() {
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        freopen("CONIN$", "r", stdin);
        freopen("CONERR$", "w", stderr);
    }

    DebugConsole::~DebugConsole() {
        FreeConsole();
    }
}