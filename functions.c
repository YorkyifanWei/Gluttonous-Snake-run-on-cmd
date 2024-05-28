#include "setting.h"
#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// global variables from main.c
extern int blocks[40][40];
extern SnakeCoord heads[3];
extern GameModern modern;
extern _Bool food;

void GotoXY(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}
char *WinnerName(void)
{
    if (heads[0].score >= heads[1].score && heads[0].score >= heads[2].score)
        return heads[0].name;
    else if (heads[1].score >= heads[2].score)
        return heads[1].name;
    else
        return heads[2].name;
}
/* Gets keyboard input without blocking other operations */
char GetKeyBoard(void)
{
    char key = 0;
    if (_kbhit())
        key = _getch();
    return key;
}
void PrintTitle(void)
{
    int i;
    for (i = 0; i < 34; i++)
        printf("-");
    printf("Gluttonous Snake");
    for (i = 0; i < 34; i++)
        printf("-");
    printf("\n");
}
void Initial(void)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 16;
    cfi.dwFontSize.Y = 24;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, _countof(cfi.FaceName), L"Raster");
    SetCurrentConsoleFontEx(handle, FALSE, &cfi);
    int i, j;
    _Bool flag = 1;
    char str[10];
    char difficulties[4][7] = {"Simple", "Normal", "Hard", "Hell"};
    char sizes[3][7] = {"Small", "Normal", "Large"};
    SetConsoleTextAttribute(handle, YELLOW);
    PrintTitle();
    Sleep(1000);
    system("cls");

    /* enter modern.difficulty */
    PrintTitle();
    printf("The game has four difficulties:\nSimple, Normal, Hard, Hell.\n");
    printf("The speed of snake and the size of map are different in different difficulties.\n");
    printf("Please choose the difficulty: ");
    while (TRUE)
    {
        scanf("%s", str);
        switch (str[0])
        {
            case 'S':
            {
                modern.difficulty = 0;
                flag = 0;
                for (i = 1; i < 6; i++)
                    if (str[i] != difficulties[0][i])
                    {
                        flag = 1;
                        break;
                    }
                break;
            }
            case 'N':
            {
                modern.difficulty = 1;
                flag = 0;
                for (i = 1; i < 6; i++)
                    if (str[i] != difficulties[1][i])
                    {
                        flag = 1;
                        break;
                    }
                break;
            }
            case 'H':
            {
                switch (str[1])
                {
                    case 'a':
                    {
                        modern.difficulty = 2;
                        flag = 0;
                        for (i = 2; i < 4; i++)
                            if (str[i] != difficulties[2][i])
                            {
                                flag = 1;
                                break;
                            }
                        break;
                    }
                    case 'e':
                    {
                        modern.difficulty = 3;
                        flag = 0;
                        for (i = 2; i < 4; i++)
                            if (str[i] != difficulties[3][i])
                            {
                                flag = 1;
                                break;
                            }
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
        if (flag)
        {
            system("cls");
            PrintTitle();
            printf("The game has four difficulties:\nSimple, Normal, Hard, Hell.\n");
            printf("The speed of snake and the size of map are different in different difficulties.\n");
            SetConsoleTextAttribute(handle, RED);
            printf("(You enter wrong difficulty. Now please enter again.)\n");
            SetConsoleTextAttribute(handle, YELLOW);
            printf("Please choose the difficulty: ");
        }
        else
            break;
    }
    Sleep(500);
    system("cls");

    /* enter modern.size */
    PrintTitle();
    printf("The game has three sizes:\nSmall, Normal, Large.\n");
    printf("Please choose the size: ");
    flag = 1;
    while (TRUE)
    {
        scanf("%s", str);
        switch (str[0])
        {
            case 'S':
            {
                modern.size = 2;
                flag = 0;
                for (i = 1; i < 5; i++)
                    if (str[i] != sizes[0][i])
                    {
                        flag = 1;
                        break;
                    }
                break;
            }
            case 'N':
            {
                modern.size = 3;
                flag = 0;
                for (i = 1; i < 6; i++)
                    if (str[i] != sizes[1][i])
                    {
                        flag = 1;
                        break;
                    }
                break;
            }
            case 'L':
            {
                modern.size = 4;
                flag = 0;
                for (i = 1; i < 5; i++)
                    if (str[i] != sizes[2][i])
                    {
                        flag = 1;
                        break;
                    }
                break;
            }
            default:
                break;
        }
        if (flag)
        {
            system("cls");
            PrintTitle();
            printf("The game has three sizes:\nSmall, Normal, Large.\n");
            SetConsoleTextAttribute(handle, RED);
            printf("(You enter wrong size. Now please enter again.)\n");
            SetConsoleTextAttribute(handle, YELLOW);
            printf("Please choose the size: ");
        }
        else
            break;
    }
    Sleep(500);
    system("cls");

    /* enter modern.multiplayer */
    PrintTitle();
    printf("The game allow at most three players.\n");
    printf("How many players(arabic numeral): ");
    while (TRUE)
    {
        scanf("%s", str);
        if (str[0] == '1' || str[0] == '2' || str[0] == '3')
            break;
        else
        {
            Sleep(500);
            system("cls");
            PrintTitle();
            printf("The game allow at most three players.\n");
            SetConsoleTextAttribute(handle, RED);
            printf("(You enter wrong number. Now please enter again.)\n");
            SetConsoleTextAttribute(handle, YELLOW);
            printf("How many players(arabic numeral): ");
        }
    }
    modern.multiplayer = str[0] - '0';
    Sleep(500);
    system("cls");

    /* enter heads[].name */
    PrintTitle();
    printf("Now please enter the name%s of player%s.\n", (modern.multiplayer == 1) ? "" : "s", (modern.multiplayer == 1) ? "" : "s");
    for (i = 0; i < modern.multiplayer; i++)
    {
        printf("Please enter the name of player %d: ", i + 1);
        scanf("%s", heads[i].name);
    }
    Sleep(500);
    system("cls");

    /* initialize info */
    modern.height = modern.size * 9;
    modern.width = modern.height;
    for (i = 0; i < modern.height; i++)
        for (j = 0; j < modern.width; j++)
        {
            if (i * j == 0 || i == modern.height - 1 || j == modern.width - 1)
                blocks[i][j] = -2;
            else
                blocks[i][j] = -1;
        }
    for (i = 0; i < 3; i++)
        heads[i].score = heads[i].alive = 0;
    for (i = 0; i < modern.multiplayer; i++)
    {
        heads[i].x = heads[i].t_x = heads[i].y = heads[i].t_y = (modern.height / (modern.multiplayer + 1)) * (i + 1);
        blocks[heads[i].x][heads[i].y] = i;
        heads[i].alive = 1;
        heads[i].speed = 9 - modern.difficulty;
        heads[i].direct = 'l';
    }
    food = 0;

    /* game start */
    PrintTitle();
    printf("Now Game Start!");
    Sleep(1000);
    system("cls");
    SetConsoleTextAttribute(handle, WHITE);
    cfi.dwFontSize.X = 15;
    cfi.dwFontSize.Y = 15;
    SetCurrentConsoleFontEx(handle, FALSE, &cfi);
}
char KeyProcess(char key)
{
    switch (key)
    {
        case 'p':
        {
            printf("Now you paused the game\nPlease press any key to continue!");
            _getch();
            system("cls");
            key = 0;
            break;
        }
        case 'q':
        {
            printf("Are you sure you want to quit the game?\nPress \'q\' again to quit!\nPress any other key to continue!");
            key = _getch();
            system("cls");
            key = (key == 'q') ? 'q' : 0;
            break;
        }
        case 'w':
        {
            if (heads[0].direct != 'd')
                heads[0].direct = 'u';
            key = 0;
            break;
        }
        case 's':
        {
            if (heads[0].direct != 'u')
                heads[0].direct = 'd';
            key = 0;
            break;
        }
        case 'a':
        {
            if (heads[0].direct != 'r')
                heads[0].direct = 'l';
            key = 0;
            break;
        }
        case 'd':
        {
            if (heads[0].direct != 'l')
                heads[0].direct = 'r';
            key = 0;
            break;
        }
        default:
        {
            if (modern.multiplayer == 1)
            {
                key = 0;
                break;
            }
            switch (key)
            {
                case 'y':
                {
                    if (heads[1].direct != 'd')
                        heads[1].direct = 'u';
                    key = 0;
                    break;
                }
                case 'h':
                {
                    if (heads[1].direct != 'u')
                        heads[1].direct = 'd';
                    key = 0;
                    break;
                }
                case 'g':
                {
                    if (heads[1].direct != 'r')
                        heads[1].direct = 'l';
                    key = 0;
                    break;
                }
                case 'j':
                {
                    if (heads[1].direct != 'l')
                        heads[1].direct = 'r';
                    key = 0;
                    break;
                }
                default:
                {
                    if (modern.multiplayer == 2)
                    {
                        key = 0;
                        break;
                    }
                    switch (key)
                    {
                        case 'o':
                        {
                            if (heads[2].direct != 'd')
                                heads[2].direct = 'u';
                            key = 0;
                            break;
                        }
                        case 'l':
                        {
                            if (heads[2].direct != 'u')
                                heads[2].direct = 'd';
                            key = 0;
                            break;
                        }
                        case 'k':
                        {
                            if (heads[2].direct != 'r')
                                heads[2].direct = 'l';
                            key = 0;
                            break;
                        }
                        case ';':
                        {
                            if (heads[2].direct != 'l')
                                heads[2].direct = 'r';
                            key = 0;
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    return key;
}
void PrintScreen(void)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    int i, j;
    char difficulties[4][7] = {"Simple", "Normal", "Hard", "Hell"};

    /* print game interface */
    SetConsoleTextAttribute(handle, FAINT_YELLOW);
    PrintTitle();
    for (i = 0; i < modern.height; i++)
    {
        for (j = 0; j < modern.width; j++)
        {
            switch (blocks[i][j])
            {
                case -1:
                {
                    printf(" ");
                    break;
                }
                case -2:
                {
                    SetConsoleTextAttribute(handle, PURPLE);
                    printf("#");
                    break;
                }
                case -3:
                {
                    SetConsoleTextAttribute(handle, YELLOW);
                    printf("*");
                    break;
                }
                default:
                {
                    switch (blocks[i][j] % 3)
                    {
                        case 0:// heads[0]
                        {
                            SetConsoleTextAttribute(handle, RED);
                            if (blocks[i][j] == 0)
                                printf("@");
                            else
                                printf("O");
                            break;
                        }
                        case 1:// heads[1]
                        {
                            SetConsoleTextAttribute(handle, GREEN);
                            if (blocks[i][j] == 1)
                                printf("@");
                            else
                                printf("O");
                            break;
                        }
                        case 2:// heads[2]
                        {
                            SetConsoleTextAttribute(handle, BLUISH);
                            if (blocks[i][j] == 2)
                                printf("@");
                            else
                                printf("O");
                            break;
                        }
                    }
                    break;
                }
            }
        }
        SetConsoleTextAttribute(handle, WHITE);

        /* print game mode */
        printf("  ");
        SetConsoleTextAttribute(handle, FAINT_YELLOW);
        switch (i)
        {
            case 0:
            {
                printf("Game Version: v0.3.1d");
                break;
            }
            case 1:
            {
                printf("Author: YorkyifanWei.");
                break;
            }
            case 2:
            {
                printf("(You can download history versions on Github)");
                break;
            }
            case 3:
            {
                printf("Map Size: %d x %d", modern.height, modern.width);
                break;
            }
            case 4:
            {
                printf("Game Difficulty: %s", difficulties[modern.difficulty]);
                break;
            }
            case 5:
            {
                printf("Players: ");
                for (j = 0; j < modern.multiplayer; j++)
                {
                    if (heads[j].alive == 0)
                        SetConsoleTextAttribute(handle, GREY);
                    else
                        SetConsoleTextAttribute(handle, (j == 0) ? RED : ((j == 1) ? GREEN : BLUISH));
                    printf("%s", heads[j].name);
                    if (j != modern.multiplayer - 1)
                        printf(", ");
                }
                break;
            }
            case 6:
            {
                if (heads[0].alive)
                    SetConsoleTextAttribute(handle, RED);
                else
                    SetConsoleTextAttribute(handle, GREY);
                printf("%s: %d", heads[0].name, heads[0].score);
                break;
            }
            default:
            {
                if (modern.multiplayer >= 2)
                {
                    if (i == 7)
                    {
                        if (heads[1].alive)
                            SetConsoleTextAttribute(handle, GREEN);
                        else
                            SetConsoleTextAttribute(handle, GREY);
                        printf("%s: %d", heads[1].name, heads[1].score);
                    }
                    else if (modern.multiplayer == 3 && i == 8)
                    {
                        if (heads[2].alive)
                            SetConsoleTextAttribute(handle, BLUISH);
                        else
                            SetConsoleTextAttribute(handle, GREY);
                        printf("%s: %d", heads[2].name, heads[2].score);
                    }
                }
                break;
            }
        }

        printf("\n");
    }

    /* print key configuration */
    SetConsoleTextAttribute(handle, WHITE);
    printf("Press \'p\' to pause, \'q\' to quit.\n");
    SetConsoleTextAttribute(handle, FAINT_YELLOW);
    printf("Key Configuration:\n");
    SetConsoleTextAttribute(handle, RED);
    printf("P1: up:\'w\' down:\'s\' left:\'a\' right:\'d\'\n");
    if (modern.multiplayer > 1)
    {
        SetConsoleTextAttribute(handle, GREEN);
        printf("P2: up:\'y\' down:\'h\' left:\'g\' right:\'j\'\n");
        if (modern.multiplayer == 3)
        {
            SetConsoleTextAttribute(handle, BLUISH);
            printf("P3: up:\'o\' down:\'l\' left:\'k\' right:\';\'\n");
        }
    }
    SetConsoleTextAttribute(handle, WHITE);
}
void SnakeMove(int player_code)
{
    int x_next = heads[player_code].x + (heads[player_code].direct == 'd') - (heads[player_code].direct == 'u');
    int y_next = heads[player_code].y + (heads[player_code].direct == 'r') - (heads[player_code].direct == 'l');
    int hit = SnakeHit(player_code);
    int tail = blocks[heads[player_code].t_x][heads[player_code].t_y];
        if (hit == -1)
        {
            heads[player_code].alive = FALSE;
            for (int i = 0; i < modern.height; i++)
                for (int j = 0; j < modern.width; j++)
                    if (blocks[i][j] >= 0 && blocks[i][j] % 3 == player_code)
                        blocks[i][j] = -1;
        }
        else if (hit == 1)
            heads[player_code].score += 1;
        if (hit >= 0)
        {
            _Bool flag = !hit;
            for (int i = 0; i < modern.height; i++)
                for (int j = 0; j < modern.width; j++)
                {
                    if (blocks[i][j] >= 0 && blocks[i][j] % 3 == player_code)
                        blocks[i][j] += 3;
                    if (flag && hit == 0 && blocks[i][j] == tail)
                    {
                        blocks[heads[player_code].t_x][heads[player_code].t_y] = -1;
                        heads[player_code].t_x = i;
                        heads[player_code].t_y = j;
                    }
                }
            heads[player_code].x = x_next;
            heads[player_code].y = y_next;
            blocks[x_next][y_next] = player_code;
        }
    tail = blocks[heads[player_code].t_x][heads[player_code].t_y];
    tail /= 15;
    if (tail > 5)
        tail = 5;
    heads[player_code].speed = 9 - modern.difficulty - tail;
}
int SnakeHit(int player_code)
{
    int x_next = heads[player_code].x + (heads[player_code].direct == 'd') - (heads[player_code].direct == 'u');
    int y_next = heads[player_code].y + (heads[player_code].direct == 'r') - (heads[player_code].direct == 'l');
    switch (blocks[x_next][y_next])
    {
        case -1:
            return 0;
        case -2:
            return -1;
        case -3:
        {
            food = 0;
            return 1;
        }
        default:
            return -1;
    }
}
void FoodRefresh(void)
{
    int f_x, f_y;
    srand((int)time(0));
    do
    {
        f_x = rand() % modern.height;
        f_y = rand() % modern.width;
    } while (f_x * f_y == 0 || f_x == modern.height - 1 || f_y == modern.width - 1 || blocks[f_x][f_y] != -1);
    blocks[f_x][f_y] = -3;
    food = 1;
}
