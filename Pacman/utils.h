#pragma once
#include "utils.h"
#include "Position.h"
#include <string>

using namespace std;

enum {
	LEFT = 'A', RIGHT = 'D', UP = 'W', DOWN = 'X', STAY = 'S',
	LEFT_L = 'a', RIGHT_L = 'd', UP_L = 'w', DOWN_L = 'x', STAY_L = 's',
	RED = 4, BLUE = 1, YELLOW = 14, GRAY = 8, BRIGHT_GREEN = 2, DEFAULT = 15,
	WHITE = 7, PURPLE = 5,
	WIDTH = 81, HEIGHT = 24
};
void gotoxy(int x, int y);
void gotoxyPos(Position pos);
void clearScreen();
void hideCursor();
void clearLine();
void logScreen(const char* format, ...);
bool isSamePos(Position p1, Position p2);
bool isOnBounds(int x, int y);
void setElementColor(int color);
int getRandomMove(int possibleDirs[]);
int getRandomNumber(int min, int max);
int getRandomColor();