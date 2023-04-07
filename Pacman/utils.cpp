#include <iostream>
#include "utils.h"
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdarg>

using namespace std;

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void gotoxyPos(Position pos) {
	gotoxy(pos.getX(), pos.getY());
}

void clearScreen()
{
	system("cls");
}

void hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);
}

void logScreen(Position oldPos, const char* format, ...) {
	gotoxy(0, 25);
	clearLine();

	va_list args;
	va_start(args, format);
	int len = vsnprintf(nullptr, 0, format, args);
	va_end(args);

	string str(len, ' ');
	va_start(args, format);
	vsnprintf(&str[0], len + 1, format, args);
	va_end(args);

	cout << str;

	gotoxyPos(oldPos);
}

void clearLine()
{
	cout << "\r" << string(80, ' ') << "\r" << flush;
}

string keyToDir(char key) {
	string moves[5] = { "Left", "Right", "Up", "Down", "Stay"};
	if (key == LEFT) {
		return moves[0];
	}
	else if (key == RIGHT) {
		return moves[1];
	}
	else if (key == UP) {
		return moves[2];
	}
	else if (key == DOWN) {
		return moves[3];
	}
	else if (key == STAY) {
		return moves[4];
	}

	return "Not a valid move";
}