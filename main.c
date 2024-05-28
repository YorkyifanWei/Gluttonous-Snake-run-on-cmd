#ifndef HEADER_FILE
#define HEADER_FILE
#include "setting.h"
#include "functions.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#endif

// define global variable
extern int blocks[40][40];
extern SnakeCoord heads[3];
extern GameModern modern;
extern _Bool food;

int main(void)
{
    ConsoleSettings();
    char key;
    unsigned int count = 0;
    int i;
    _Bool flag = 1;
    while (flag)
    {
        Initial();
        count = 0;
        while (TRUE)
        {
            key = GetKeyBoard();
            if (food == 0)
                FoodRefresh();
            PrintScreen();
            key = KeyProcess(key);
            if (key == 'q' || (!heads[0].alive && !heads[1].alive && !heads[2].alive))
            {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
                printf("Game Over!\n");
                PrintScreen();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
                printf("\n");
                printf("The winner is \"%s\"\n", WinnerName());
                printf("\n");
                printf("Enter \'r\' to restart game, or enter any other key to quit game.\n");
                key = _getch();
                if (key != 'r')
                    flag = 0;
                break;
            }
            for (i = 0; i < modern.multiplayer; i++)
                if (heads[i].alive && count % heads[i].speed == 0)
                    SnakeMove(i);
            count += 1;
            count %= 720;
            Sleep(50);
            GotoXY(0, 0);
        }
    }
    system("cls");

    return 0;
}
