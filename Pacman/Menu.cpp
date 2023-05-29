#include "Menu.h"
#include "utils.h"
#include <iostream>
#include <conio.h>

using namespace std;

void Menu::display() {
	clearScreen();
	gotoxy(0, 0);
	cout << "----Welcome To The Pacman Game----" << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(5) Choose difficulty" << endl;
	cout << "(6) Change Level from a file" << endl;
	cout << "(7) Settings" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
	cout << "----------------------------------" << endl;
}

void Menu::instructions() {
	clearScreen();
	gotoxy(0, 0);
	cout << "------Instructions and keys------" << endl;
	cout << "The objective of the game is to eat all of the dots placed in the maze while avoiding four colored ghosts" << endl;
	cout << "keys:" << endl;
	cout << "Left  -> a|A" << endl;
	cout << "Right -> d|D" << endl;
	cout << "Up    -> w|W" << endl;
	cout << "Down  -> x|X" << endl;
	cout << "Stay  -> s|S" << endl;
	cout << "Pause -> ESC" << endl;
	cout << "---------------------------------" << endl;
	cout << "Press ENTER to continue" << endl;
	char key = 0;
	do {
		if (_kbhit()) key = _getch();
	} while (key != ENTER);
}

void Menu::levels(int& level, bool& isInProgress) {
	char key = 0;
	int newLevel = 0;
	clearScreen();
	gotoxy(0, 0);
	cout << "------Levels--------" << endl;
	cout << "level: " << level << endl;
	cout << "(D) level-up" << endl;
	cout << "(A) level-down" << endl;
	cout << "(S) enter a level from file: pacman_(level).screen.txt" << endl;
	cout << "--------------------" << endl;
	cout << "Press ENTER to continue" << endl;
	do {
		if (_kbhit()) key = _getch();
		if (key == 'D' || key == 'd') {
			isInProgress = false;
			level++;
			clearScreen();
			gotoxy(0, 0);
			cout << "------Levels--------" << endl;
			cout << "level: " << level << endl;
			cout << "(D) level-up" << endl;
			cout << "(A) level-down" << endl;
			cout << "(S) enter a level from file: pacman_(level).screen.txt" << endl;
			cout << "--------------------" << endl;
			cout << "Press ENTER to continue" << endl;
			key = 0;
		}
		if (key == 'A' || key == 'a') {
			isInProgress = false;
			if(level > 1) level--;
			clearScreen();
			gotoxy(0, 0);
			cout << "------Levels--------" << endl;
			cout << "level: " << level << endl;
			cout << "(D) level-up" << endl;
			cout << "(A) level-down" << endl;
			cout << "(S) enter a level from file: pacman_(level).screen.txt" << endl;
			cout << "--------------------" << endl;
			cout << "Press ENTER to continue" << endl;
			key = 0;
		}
		if (key == 'S' || key == 's') {
			isInProgress = false;
			clearScreen();
			gotoxy(0, 0);
			cout << "------Levels--------" << endl;
			cout << "Level: ";
			cin >> newLevel;
			level = newLevel;
			clearScreen();
			gotoxy(0, 0);
			cout << "------Levels--------" << endl;
			cout << "level: " << level << endl;
			cout << "(D) level-up" << endl;
			cout << "(A) level-down" << endl;
			cout << "(S) enter a level to use for a file: pacman_(level).screen.txt" << endl;
			cout << "--------------------" << endl;
			cout << "Press ENTER to continue" << endl;
			key = 0;
		}
	} while (key != ENTER);
}

void Menu::settings(bool& isColors) {
	char key = 0;
	clearScreen();
	gotoxy(0, 0);
	cout << "------Settings------" << endl;
	cout << "colors: " << (isColors ? "on" : "off") << endl;
	cout << "(SPACE) Set colors" << endl;
	cout << "--------------------" << endl;
	cout << "Press ENTER to continue" << endl;
	do {
		if (_kbhit()) key = _getch();
		if (key == SPACE) {
			isColors = !isColors;
			clearScreen();
			gotoxy(0, 0);
			cout << "------Settings------" << endl;
			cout << "colors: " << (isColors ? "on" : "off") << endl;
			cout << "(SPACE) Set colors" << endl;
			cout << "--------------------" << endl;
			cout << "Press ENTER to continue" << endl;
			key = 0;
		}
	} while (key != ENTER);
}

void Menu::difficulties(char& difficulty) {
	char key = 0;
	clearScreen();
	gotoxy(0, 0);
	cout << "------Difficulties--------" << endl;
	cout << "difficulty: " << difficulty << endl;
	cout << "(a) BEST" << endl;
	cout << "(b) GOOD" << endl;
	cout << "(c) NOVICE" << endl;
	cout << "--------------------" << endl;
	cout << "Press ENTER to continue" << endl;
	do {
		if (_kbhit()) key = _getch();
		if (key == 'A' || key == 'a') {
			difficulty = 'a';
			clearScreen();
			gotoxy(0, 0);
			cout << "------Difficulties--------" << endl;
			cout << "difficulty: " << difficulty << endl;
			cout << "(a) BEST" << endl;
			cout << "(b) GOOD" << endl;
			cout << "(c) NOVICE" << endl;
			cout << "--------------------" << endl;
			cout << "Press ENTER to continue" << endl;
			key = 0;
		}
		if (key == 'B' || key == 'b') {
			difficulty = 'b';
			clearScreen();
			gotoxy(0, 0);
			cout << "------Difficulties--------" << endl;
			cout << "difficulty: " << difficulty << endl;
			cout << "(a) BEST" << endl;
			cout << "(b) GOOD" << endl;
			cout << "(c) NOVICE" << endl;
			cout << "--------------------" << endl;
			cout << "Press ENTER to continue" << endl;
			key = 0;
		}
		if (key == 'C' || key == 'c') {
			difficulty = 'c';
			clearScreen();
			gotoxy(0, 0);
			cout << "------Difficulties--------" << endl;
			cout << "difficulty: " << difficulty << endl;
			cout << "(a) BEST" << endl;
			cout << "(b) GOOD" << endl;
			cout << "(c) NOVICE" << endl;
			cout << "--------------------" << endl;
			cout << "Press ENTER to continue" << endl;
			key = 0;
		}
	} while (key != ENTER);
}