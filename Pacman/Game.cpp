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
	cout << "(7) Settings" << endl;
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

void Game::displaySettings() {
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
			setColors();
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

void Game::init() {
	clearScreen();
	gameBoard = Board();
	if (isColors) {
		player.setColor(YELLOW);
		ghost1.setColor(RED);
		ghost2.setColor(BLUE);
		gameBoard.setColor(BRIGHT_GREEN);
	} 
	else {
		player.setColor(DEFAULT);
		ghost1.setColor(DEFAULT);
		ghost2.setColor(DEFAULT);
		gameBoard.setColor(DEFAULT);
	}
	player.initPos();
	ghost1.initPos();
	ghost2.initPos();
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
	bool isWin = false;
	int iteration = 0;

	int ghost1PossibleDirs[4] = { 0,0,0,0 };
	int ghost2PossibleDirs[4] = { 0,0,0,0 };

	while (!isGameOver) {
		do {
			iteration++;

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

				// check for win
				if (gameBoard.isNoBreadCrumbs()) {
					isWin = true;
				}
			}
			else if (!isStay) {
				logScreen("not valid move: %d", key);
			}

			if (iteration % 2 == 0) {
				// ghosts move
				getPossibleDirs(ghost1.getPos(), ghost1PossibleDirs);
				getPossibleDirs(ghost2.getPos(), ghost2PossibleDirs);

				//logScreen("ghost1: left->%d right->%d up->%d down->%d", ghost1PossibleDirs[0], ghost1PossibleDirs[1], ghost1PossibleDirs[2], ghost1PossibleDirs[3]);
				//logScreen("ghost2: left->%d right->%d up->%d down->%d", ghost2PossibleDirs[0], ghost2PossibleDirs[1], ghost2PossibleDirs[2], ghost2PossibleDirs[3]);

				ghost1.move(ghost1PossibleDirs, gameBoard.get(ghost1.getPos().getX(), ghost1.getPos().getY()));
				ghost1.draw();
				ghost2.move(ghost2PossibleDirs, gameBoard.get(ghost2.getPos().getX(), ghost2.getPos().getY()));
				ghost2.draw();
			}

			logScreen("State: pacman-(%d,%d), ghost1-(%d,%d), ghost2-(%d,%d)", 
				player.getPos().getX(), player.getPos().getY(), 
				ghost1.getPos().getX(), ghost1.getPos().getY(), 
				ghost2.getPos().getX(), ghost2.getPos().getY());

			// TODO: check swap places
			if (isSamePos(ghost1.getPos(), player.getPos()) || 
				isSamePos(ghost2.getPos(), player.getPos())) {
				dropLive();
				player.initPos();
				ghost1.initPos();
				ghost2.initPos();
				draw();
				key = 0;
				logScreen("Hit by a ghost");
			}

			Sleep(200);
		} while (key != ESC && lives > 0 && !isWin);

		if (key == ESC) {
			pause();
			draw();
			key = prevKey;
		}

		if (lives == 0) {
			clearScreen();
			cout << "----Game Over----" << endl;
			cout << "Press any key to return to menu" << endl;
			char key = 0;
			do {
				if (_kbhit()) key = _getch();
			} while (key == 0);
			isGameOver = true;
		}
		if (isWin) {
			clearScreen();
			cout << "----You win----" << endl;
			cout << "Press any key to return to menu" << endl;
			char key = 0;
			do {
				if (_kbhit()) key = _getch();
			} while (key == 0);
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
	cout << "Remaining Lives: " << string(lives, '@') << "   Points: " << points;
	gotoxyPos(player.getPos());
}

void Game::draw() {
	clearScreen();
	gameBoard.print();
	player.draw();
	ghost1.draw();
	ghost2.draw();
	setStats();
}

void Game::getPossibleDirs(Position pos, int possibleDirs[]) {
	if (gameBoard.get(pos.getX() - 1, pos.getY()) != '#' && isOnBounds(pos.getX() - 1, pos.getY())) possibleDirs[0] = 1;
	else possibleDirs[0] = 0;
	if (gameBoard.get(pos.getX() + 1, pos.getY()) != '#' && isOnBounds(pos.getX() + 1, pos.getY())) possibleDirs[1] = 1;
	else possibleDirs[1] = 0;
	if (gameBoard.get(pos.getX(), pos.getY() - 1) != '#' && isOnBounds(pos.getX(), pos.getY() - 1)) possibleDirs[2] = 1;
	else possibleDirs[2] = 0;
	if (gameBoard.get(pos.getX(), pos.getY() + 1) != '#' && isOnBounds(pos.getX(), pos.getY() + 1)) possibleDirs[3] = 1;
	else possibleDirs[3] = 0;
}