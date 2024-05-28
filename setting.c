#include "setting.h"
#include <conio.h>
#include <windows.h>

// global variables from main.c
int blocks[40][40];// '-1':None; '-2:wall; '-3':food; '0~2':snake head; '>=3':snake body
SnakeCoord heads[3];
GameModern modern;
_Bool food = 0;

/* Set the console font to ensure that the characters are square words of the same length and width */
void ConsoleSettings(void)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 15;
    cfi.dwFontSize.Y = 15;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, _countof(cfi.FaceName), L"Raster");
    SetCurrentConsoleFontEx(handle, FALSE, &cfi);

    CONSOLE_CURSOR_INFO cursor = {1, 0};
    SetConsoleCursorInfo(handle, &cursor);
}
