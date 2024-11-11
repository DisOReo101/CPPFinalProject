#include "ConsoleHelper.h"

const HANDLE COUT_H = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleHelper::ClearConsole()
{
    //Handle different operating systems
#ifdef _WIN32
    system("cls");
#elif _WIN64
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleHelper::SetConsoleTextColor(unsigned short Color)
{
    SetConsoleTextAttribute(COUT_H, Color);
}
