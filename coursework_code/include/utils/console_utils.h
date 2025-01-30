#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <conio.h> // Для _getch()
#else
#include <unistd.h>
#endif

// очистка экрана консоли
void ClearScreen();

// ожидание нажатия клавиши
void Pause();

#endif // CONSOLE_UTILS_H