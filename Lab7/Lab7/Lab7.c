#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<stdbool.h>
char cursor(int x, int y)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2]; COORD c = { x,y }; DWORD num_read;
    if (
        !ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

        return '\0';
    else
        return buf[0];
}

void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_bullet(int x, int y)
{
    gotoxy(x, y);
    printf("^");
}
void erase_bullet(int x, int y)
{
    gotoxy(x, y);
    printf(" ");
}
void draw_ship(int x, int y)
{
    gotoxy(x, y);
    printf(" <-0-> ");
}
void erase_ship(int x, int y)
{
    gotoxy(x, y);
    printf("        ");
}
void draw_star(int x, int y)
{
    gotoxy(x, y);
    setcolor(rand() % 5, 0);
    printf("*");
}
void Score(int x, int y, int score)
{
    gotoxy(x, y);
    setcolor(3, 4);
    printf("SCORE = %d", score);
}
int main()
{
    int i, j;
    srand(time(NULL));
    setcursor(0);
    char ch = ' ';
    int x = 38, y = 20;
    int count = 20;
    bool STOP = false;
    bool LEFT = false;
    bool RIGHT = false;
    int bullet[5] = { 0 };
    int bx[5], by[5];
    int Sx, Sy;
    int score = 0;
    int PosSx[20];
    int PosSy[20];
    setcolor(6, 5);
    draw_ship(x, y);

    for (int star = 0; star < 20; star++)
    {
        Sy = rand() % 6 + 2;
        Sx = rand() % 80 + 10;
        draw_star(Sx, Sy);
        PosSx[star] = Sx;
        PosSy[star] = Sy;
    }

    do {
        // setcolor(6,0);
        if (_kbhit())
        {
            ch = _getch();
            if (ch == 'a')
            {
                LEFT = true;
                STOP = false;
                RIGHT = false;
            }
            if (ch == 'd')
            {
                LEFT = false;
                STOP = false;
                RIGHT = true;
            }
            if (ch == 's')
            {
                LEFT = false;
                STOP = true;
                RIGHT = false;
            }
            if (ch == ' ')
            {
                for (int i = 0; i < 5; i++)
                {
                    if (bullet[i] == 0)
                    {
                        bullet[i] = 1;
                        bx[i] = x + 3;
                        by[i] = y - 1;
                        setcolor(6, 6);
                        draw_bullet(bx[i], by[i]);
                        Beep(500, 60);
                        break;
                    }
                }
            }
            fflush(stdin);
        }
        for (int i = 0; i < 5; i++)
        {
            if (bullet[i] != 0)
            {
                int isCollide = 0;
                for (int pos = 0; pos < 20; pos++)
                {
                    if (bx[i] == PosSx[pos] && by[i] == PosSy[pos])
                    {
                        isCollide = 1;
                        score++;
                        //respawn star if it was hit
                        Sy = rand() % 6 + 2;
                        Sx = rand() % 80 + 10;
                        draw_star(Sx, Sy);
                    }
                }

                setcolor(6, 0);
                erase_bullet(bx[i], by[i]);
                if (by[i] == 1 || isCollide==1)
                {
                    bullet[i] = 0;
                }
                else
                {
                    setcolor(6, 6);
                    draw_bullet(bx[i], --by[i]);
                }

            }
            Score(0, 0, score);
        }
        if ((LEFT == 1) && (x > 0))
        {
            setcolor(6, 0);
            erase_ship(x, y);
            setcolor(6, 5);
            gotoxy(x, y);
            draw_ship(--x, y);
        }
        if (STOP == 1)
        {
            setcolor(6, 5);
            draw_ship(x, y);
        }
        if ((RIGHT == 1) && (x < 110))
        {
            setcolor(6, 0);
            erase_ship(x, y);
            setcolor(6, 5);
            gotoxy(x, y);
            draw_ship(++x, y);
        }
        Sleep(100);
    } while (ch != 'x');

    return 0;
}



