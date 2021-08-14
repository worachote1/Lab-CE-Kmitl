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
	//Sleep(500);
	setcolor(2, 4);
	printf("<-0->");
}
void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(2,0);
	printf("     ");
}
int main() {
	//Lab 6
	//Decoration in Text-mode game

	//Let's play !!!
	char ch = ' ';
	int x = 38, y = 20;
	setcursor(0);
	draw_ship(x, y);

	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				if (x > 0) {
					erase_ship(x, y);
					draw_ship(--x, y);
				}

			}
			if (ch == 'd') {
				if (x < 80) {
					erase_ship(x, y);
					draw_ship(++x, y);				
				}
			}
			if (ch == 'w') {
				if (y > 0) {
					erase_ship(x, y);
					draw_ship(x, --y);
				}
			}
			if (ch == 's') {
				if (y < 40) {
					erase_ship(x, y);	
					draw_ship(x, ++y);
				}
			}

			fflush(stdin);
		}

		Sleep(100);
	} while (ch != 'x');

	
	return 0;
}