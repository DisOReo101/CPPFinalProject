#pragma once
#include <windows.h>

constexpr int
    GREEN = 0x20,
    YELLOW = 0x60,
    GRAY = 0x80,
    RESET = 0x07;

class ConsoleHelper
{
public:
    static void ClearConsole();
    static void SetConsoleTextColor(unsigned short Color);
};
