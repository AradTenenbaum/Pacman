#include <iostream>
#include <random>
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

void logScreen(const char* format, ...) {
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

}

void clearLine()
{
	cout << "\r" << string(80, ' ') << "\r" << flush;
}

void setElementColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool isSamePos(Position p1, Position p2) {
	return (p1.getX() == p2.getX()) && (p1.getY() == p2.getY());
}

bool isOnBounds(int x, int y) {
	return (x < (WIDTH - 1) && (x >= 0) && (y < HEIGHT) && (y >= 0));
}

int getRandomMove(int possibleDirs[]) {
	int dir, dirIndex = 0, numOfDirs = 0;
	for (int i = 0; i < 4; i++) {
		if (possibleDirs[i] == 1) numOfDirs++;
	}
	dir = rand() % numOfDirs;
	int i = 0;
	int newIndex = (dir % numOfDirs);
	while (newIndex >= 0) {
		if (possibleDirs[dirIndex] == 1) newIndex--;
		dirIndex++;
	}
	dirIndex--;

	return dirIndex;
}

int getRandomNumber(int min, int max) {
	random_device rd;                           
	mt19937 eng(rd());                          
	uniform_int_distribution<int> distribution(min, max);  
	return distribution(eng);
}