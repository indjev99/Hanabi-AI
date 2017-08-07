#ifndef CONSOLE_HANDLE_H_INCLUDED
#define CONSOLE_HANDLE_H_INCLUDED

#include<windows.h>

const HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

#endif // CONSOLE_HANDLE_H_INCLUDED
