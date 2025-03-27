#pragma once

namespace Engine
{
    class DebugConsole {
    public:
        void ShowConsole(bool visible);

        DebugConsole();
        ~DebugConsole();

    private:

        DebugConsole(const DebugConsole& rhs) = delete;
        DebugConsole& operator=(const DebugConsole& rhs) = delete;
    };
}
