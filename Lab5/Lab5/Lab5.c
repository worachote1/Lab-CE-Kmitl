#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
void gotoxy(int x,int y) {
	COORD c = { x, y}; //display at order of character x and line y
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int a,int b) {
	gotoxy(a,b);
	Sleep(500);
	printf("<-0->");
}
void erase_ship(int x, int y) {
	gotoxy(x,y);
	printf("     ");
}
int main() {
	//Lab 5
	//Movement and display in Text-mode game
	
	
	// set size of window (now i don't use these code below , instead of these,Right Click on title bar of your running console application
	//-Select Properties
	//-Select Layout
	//-Then set the window size.)
	/*
	CONSOLE_SCREEN_BUFFER_INFOEX consolesize;

	consolesize.cbSize = sizeof(consolesize);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfoEx(hConsole, &consolesize);

	COORD c;
	c.X = 80;
	c.Y = 40;
	consolesize.dwSize = c;

	consolesize.srWindow.Left = 0;
	consolesize.srWindow.Right = 80;
	consolesize.srWindow.Top = 0;
	consolesize.srWindow.Bottom = 40;

	SetConsoleScreenBufferInfoEx(hConsole, &consolesize);
	*/
	//Let's play !!!
	char ch = ' ';
	int x = 38, y = 20;
	draw_ship(x,y);
	
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { 
				if (x>0) {
					erase_ship(x, y);
					draw_ship(--x, y);
				}
				
			}
			if (ch == 'd') { 
				if (x<80) {
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

	//341234123412341234123412341234123412341234123412341234123412341234123412341234
		return 0;
	}

