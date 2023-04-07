#include "Game.h"
#include "Board.h"
#include <conio.h>
#include <windows.h>
#include "utils.h"

void Game::displayMenu() {
	clearScreen();
	gotoxy(0, 0);
	cout << "----Welcome To The Pacman Game----" << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
	cout << "----------------------------------" << endl;
}

void Game::displayInstructions() {
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

void Game::init() {
	clearScreen();
	player.initPos();
	points = 0;
	lives = LIVES;
	draw();
}

void Game::run() {
	hideCursor();
	int move = 0;
	char key = 0;
	char prevKey = 0;
	bool isStay = true;	
	bool isGameOver = false;

	while (!isGameOver) {
		do {
			if (_kbhit()) {
				prevKey = key;
				key = _getch();
				isStay = ((key == STAY) || (key == STAY_L));
			}
			if (isValidMove(key) && !isStay) {
				player.move(key);
				if (onBreadCurmb()) {
					addPoints(10);
					gameBoard.setPos(player.getPos(), ' ');
				}
				player.draw();

				// TODO: check for win

			}
			else if (!isStay) {
				logScreen(player.getPos(), "not valid move: %d", key);
				dropLive();
			}
			Sleep(400);
		} while (key != ESC && lives > 0);

		if (key == ESC) {
			pause();
			draw();
			key = prevKey;
		}

		if (lives == 0) {
			isGameOver = true;
		}
	}
}

void Game::pause() {
	char key = 0;
	clearScreen();
	cout << "----Game is paused----" << endl;
	cout << "(ESC) Continue" << endl;
	cout << "----------------------" << endl;
	do {
		if (_kbhit()) key = _getch();
	} while (key != ESC);
}

bool Game::isValidMove(int dir) {
	Position&& newPos = player.getPos().posAfterMove(dir);
	char gamePosObj = gameBoard.get(newPos.getX(), newPos.getY());
	if (gamePosObj == '#') {
		return false;
	}
	return true;
}

bool Game::onBreadCurmb() {
	Position&& pos = player.getPos();
	char gamePosObj = gameBoard.get(pos.getX(), pos.getY());
	if (gamePosObj == '*') {
		return true;
	}
	return false;
}

void Game::addPoints(int add) {
	points += add;
	setStats();
}
void Game::dropLive() {
	lives--;
	setStats();
}

void Game::setStats() {
	gotoxy(0, 24);
	clearLine();
	cout << "Remaining Lives: " << string(lives, '$') << "   Points: " << points;
	gotoxyPos(player.getPos());
}

void Game::draw() {
	clearScreen();
	gameBoard.print();
	player.draw();
	setStats();
}