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
    setcolor(6, 6);
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
    setcolor(6, 5);
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
    //setcursor(0);
    char ch = ' ';
    int x = 38, y = 20;
    int count = 20;
    bool STOP = false;
    bool RIGHT = false;
    bool LEFT = false;
    int bullet =  0 ;
    int bx, by; //bullet distance
    int Sx, Sy; //star distance
    int score = 0;
    //star position
    int PosSx[20];
    int PosSy[20];
    
    draw_ship(x, y);
    //random 20 stars
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
         
                    if (bullet == 0)
                    {
                        bullet = 1;
                        bx = x + 3;
                        by = y - 1;
                        
                        draw_bullet(bx, by);
                        Beep(500, 60);
                       
                    }
                
            }
            fflush(stdin);
        }
     
            if (bullet != 0)
            {
                int isCollide = 0;
                for (int pos = 0; pos < 20; pos++)
                {
                    if (bx == PosSx[pos] && by == PosSy[pos])
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
                erase_bullet(bx, by);
                if (by == 1 || isCollide==1)
                {
                    bullet = 0;
                }
                else
                {
                    setcolor(6, 6);
                    draw_bullet(bx, --by);
                }

            }
            Score(0, 0, score);
       
        
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



