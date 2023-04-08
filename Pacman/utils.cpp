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
	static int x = 25;
	static int offset = 0;

	gotoxy(0, x + offset);
	offset = (offset + 1) % 5;
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

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool isSamePos(Position p1, Position p2) {
	return (p1.getX() == p2.getX()) && (p1.getY() == p2.getY());
}