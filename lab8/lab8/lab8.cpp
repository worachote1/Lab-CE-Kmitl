#include <windows.h>
#include<iostream>
#define screen_x 80
#define screen_y 25
#define scount 80
HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
COORD characterPos = { 0,0 };
COORD star[scount];
COORD bufferSize = { screen_x,screen_y };
COORD ship;
CHAR_INFO consoleBuffer[screen_x * screen_y];
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
int HP = 10;
const char* ship_model = "<-0->";
int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}
void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos,
		&windowSize);
}
void clear_buffer() {
	for (int y = 0; y < screen_y; ++y) {
		for (int x = 0; x < screen_x; ++x) {
			consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
		}
	}
}
void init_star() {
	for (size_t i = 0; i < 80; i++)
	{
		star[i] = { rand() % 80,rand() % 29 };
	}
}
void star_fall()
{
	int i;
	for (i = 0; i < scount; i++) {
		if (star[i].Y >= screen_y - 1) {
			star[i] = { (rand() % screen_x),rand() % 5 };
		}
		else {
			star[i].Y += 1;
			if (star[i].Y == ship.Y)
			{
				for (short x = -2; x <= 2; x++)
				{
					if (star[i].X == ship.X + x)
					{
						HP--;
						star[i] = { (rand() % screen_x),1 };
						break;
					}
				}
			}
		}

	}
}
void fill_star_to_buffer()
{
	for (size_t i = 0; i < 80; i++)
	{
		consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar = '*';
		consoleBuffer[star[i].X + screen_x * star[i].Y].Attributes = 7;
	}

}
void fill_ship_to_buffer(int color)
{
	for (size_t i = 0; i < 5; i++)
	{
		consoleBuffer[ship.X + screen_x * ship.Y + i].Char.AsciiChar = ship_model[i];
		consoleBuffer[ship.X + screen_x * ship.Y + i].Attributes = color;
	}



}
int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}


int main()
{
	int color = 1;
	bool play = true;
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setConsole(screen_x, screen_y);
	setMode();
	srand(time(NULL));
	init_star();
	while (play && HP > 0)
	{
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT &&
					eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						play = false;
					}
					printf("press : %c\n", eventBuffer[i].Event.KeyEvent.uChar.AsciiChar);
					if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c' || eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'C')
					{
						color = rand() % 15 + 1;
					}
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState &
						FROM_LEFT_1ST_BUTTON_PRESSED) {
						color = rand() % 15 + 1;
					}

					if (posx >= 0 && posx <= 77)
					{
						ship.X = posx - 2;
					}

					ship.Y = posy;
				}
			}
			delete[] eventBuffer;
		}

		star_fall();
		clear_buffer();
		fill_star_to_buffer();
		fill_ship_to_buffer(color);
		fill_buffer_to_console();
		Sleep(100);
	}
	return 0;
}
