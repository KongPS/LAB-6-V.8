#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#include <stdio.h>
#include <conio.h>
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(2, 4);
    printf("<-O->");
}
void erase_ship(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(0, 0);
    printf("     ");
}
void erase_R(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(0, 0);
    printf(" ");
}
void ammo(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(1, 4);
    printf("A");
}

int main()
{
    int ammoC = 0;//???????????
    int left = 5, right = 6, front = 7, space = 8, stop = 0, i;
    setcursor(0);
    char ch = ' ';
    int x = 38, y = 20;
    int c[5], d[5];
    int direction = 1000;
    int ammoINFO[5] = { 0,0,0,0,0 };
    int ammos = 0;
    draw_ship(x, 20);
    do {
        while (1)
        {
            if (_kbhit())
            {
                ch = _getch();
                if (ch == 'a') { direction = left; }
                if (ch == 'd') { direction = right; }
                if (ch == ' ') { ammos = 1; }
            }
            if (direction == left && x > 1)
            {
                erase_ship(x, y);
                draw_ship(--x, y);
            }
            if (direction == right & x < 79)
            {
                erase_ship(x, y);
                draw_ship(++x, y);
            }
            if (ammos == 1 && ammoINFO[ammoC] != 1)
            {
                ammoINFO[ammoC] = 1;
                c[ammoC] = x + 2;
                d[ammoC] = y - 1;
                ammos = 0;
                ammoC++;
            }
            Sleep(100);

            if (ammoC > 4)
            {
                ammoC = 0;
            }
            fflush(stdin);

            for (i = 0; i < 5; i++)
            {
                if (ammoINFO[i] == 1)
                {
                    erase_R(c[i], d[i]);
                    if (d[i] == 1)
                    {
                        ammoINFO[i] = 0;
                    }
                    else
                    {
                        ammo(c[i], --d[i]);
                    }
                }
            }
        }
        Sleep(100);
    } while (ch != 'x');
    return 0;
}