#pragma once
#include "utils.h"
#include "Position.h"
#include <string>

using namespace std;



enum { LEFT = 'A', RIGHT = 'D', UP = 'W', DOWN = 'X', STAY = 'S',
	   LEFT_L = 'a', RIGHT_L = 'd', UP_L = 'w', DOWN_L = 'x', STAY_L = 's'
};
void gotoxy(int x, int y);
void gotoxyPos(Position pos);
void clearScreen();
void hideCursor();
void clearLine();
void logScreen(Position oldPos, const char* format, ...);
string keyToDir(char key);