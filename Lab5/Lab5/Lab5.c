#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
void gotoxy(int x,int y) {
	COORD c = { x, y}; //แสดงผลที่บรรทัด y ตัวอักษรที่ x โดย 1 บรรทัดมี 80 ตัวอักษร
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int a,int b) {
	//for (int i = 1; i <= 60; i++) {
	//	gotoxy(a+i, b);
	//	Sleep(500);
	//	printf("<-0->");
	//	//system("cls");
	//}
	gotoxy(a,b);
	Sleep(0);
	printf("<-0->");
}
void erase_ship(int x, int y) {
	gotoxy(x,y);
	printf("     ");
}
int main() {
	//Lab 5
	//Movement and display in Text-mode game
	//ใช้ประมาณ y = 25 ให้อยู่ล่างสุด
	
	// set size of window
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

