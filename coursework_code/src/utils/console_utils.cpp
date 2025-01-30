#include "utils/console_utils.h"

void ClearScreen()
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return;
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
#else
    std::cout << "\033[2J\033[H"; // ANSI Escape Codes (Linux/macOS)
#endif
}

void Pause()
{
#ifdef _WIN32
    std::cout << "Нажмите любую клавишу для продолжения...";
    _getch();
#else
    std::cout << "Нажмите Enter для продолжения...";
    std::cin.get();
#endif
}
