#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y) {
	COORD c = { x, y }; //display at order of character x and line y
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int a, int b) {
	gotoxy(a, b);

	setcolor(2, 4);
	printf("<-0->");
}
void draw_bullet(int a,int b) {
	gotoxy(a,b);
	setcolor(2, 4);
	printf("^");
}
void erase_bullet(int a,int b) {
	gotoxy(a, b);
	setcolor(2, 0);
	printf(" ");
}
void erase_ship(int a, int b) {
	gotoxy(a, b);
	setcolor(2,0);
	printf("     ");
}
int main() {
	//Lab 6
	//Decoration in Text-mode game

	//Let's play !!!
	char ch = ' ';
	int x = 38, y = 40;
	setcursor(0);
	draw_ship(x, y);
	bool LEFT = false;
	bool RIGHT = false;
	bool STOP = false;
	int bullet[5] = { 0 };
	int bx[5];
	int by[5];

	do {
		if (_kbhit()) {
			ch = _getch();
			//check keyborad press
			if (ch == 'a') {
					LEFT = true;
					RIGHT = false;
					STOP = false;
			}
			if (ch == 'd') {
				LEFT = false;
				RIGHT = true;
				STOP = false;
			}
			if (ch == 's') {
				LEFT = false;
				RIGHT = false;
				STOP = true;				
			}
			//set bullet status if press space bar
			if (ch == ' ') {
				for (int i = 0; i < 5;i++) {
					if (bullet[i]==0) {
						bullet[i] = 1;
						bx[i] = x + 3;
						by[i] = y + 1;
						draw_bullet(bx[i], by[i]);
						break;
					}
				}
			}
		}
		fflush(stdin);
		//check direction
		//move left
		if (LEFT == 1 && x > 0) {
			erase_ship(x, y);
			draw_ship(--x, y);
		}
		//move right
		if (RIGHT == 1 && x < 80) {
			erase_ship(x, y);
			draw_ship(++x, y);
		}
		//stop moiving when press s
		if (STOP == 1) {
			draw_ship(x, y);
		}
		//shoot if bullet state is 1
		for (int i = 0; i < 5;i++) {
			if (bullet[i] != 0 && by[i]>0) {
				erase_bullet(bx[i], by[i]);
				by[i] -= 1;
				draw_bullet(bx[i], by[i]);
			}
		}
		//erase bullet if it hit the top
		for (int i = 0; i < 5;i++) {
			if (by[i]==0) {
				erase_bullet(bx[i], by[i]);
			}
		}

		Sleep(100);
	} while (ch != 'x');

	
	return 0;
}