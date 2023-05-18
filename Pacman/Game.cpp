#include "Game.h"
#include "Board.h"
#include <conio.h>
#include <windows.h>
#include <typeinfo>
#include "utils.h"
#include <typeinfo>

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

	gameObjects.clear();
	gameObjects.push_back(new Pacman());
	setPlayer(static_cast<Pacman*>(gameObjects.front()));
	for (int i = 0; i < maxGhostsAmount; i++) {
		gameObjects.push_back(new Ghost());
	}
 

	clearScreen();

	gameBoard = Board();

	if (isColors) {
		for (const auto& gameObject : gameObjects) {
			if(typeid(*gameObject) == typeid(Pacman)) {
				(gameObject)->setColor(YELLOW);
			}
			else if (typeid(*gameObject) == typeid(Ghost)) {
				(gameObject)->setColor(getRandomColor());
			}
		}
		gameBoard.setColor(BRIGHT_GREEN);
	} 
	else {
		for (const auto& gameObject : gameObjects) {
			(gameObject)->setColor(DEFAULT);
		}
		gameBoard.setColor(DEFAULT);
	}

	initPositions();
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
	Fruit* toEatFruit = nullptr;
	list<Fruit*> deadFruits;

	int possibleDirs[4] = { 0,0,0,0 };

	while (!isGameOver) {
		do {
			// count game iterations
			iteration++;

			if (((iteration % 10) == getRandomNumber(1, 10)) && (fruitAmount <= maxFruitAmount)) {
				fruitSpawn();
				fruitAmount++;
			}

			// check for key change
			if (_kbhit()) {
				prevKey = key;
				key = _getch();
				isStay = ((key == STAY) || (key == STAY_L));
			}

			for (const auto& gameObject : gameObjects) {
				if (typeid(*gameObject) == typeid(Pacman)) {
					if(isValidMove(key) && !isStay) {
						gameBoard.drawPos(gameObject->getPos());
						gameObject->move(key);
						// check if breadcrumb exist for increasing points
						if (onBreadCurmb()) {
							addPoints(10);
							gameBoard.setPos(gameObject->getPos(), ' ');
						}
						gameObject->draw();

						// check for win
						if (gameBoard.isNoBreadCrumbs()) {
							isWin = true;
						}
					}
					else if (!isStay) {
						logScreen("not a valid move: %d", key);
					}
				}
				else if (typeid(*gameObject) == typeid(Ghost)) {
					if (iteration % 2 == 0) {
						// ghosts move
						getPossibleDirs(gameObject->getPos(), possibleDirs);
						gameBoard.drawPos(gameObject->getPos());
						gameObject->move(getRandomMove(possibleDirs));
						gameObject->draw();
					}

					// check if player on the same position of one of the ghosts
					// check if player or one of the ghosts swap places
					// drop one live if true
					if (player->isCollide(gameObject->getPos(), gameObject->getPrevPos())) {
						dropLive();
						initPositions();
						key = 0;
						logScreen("Hit by a ghost");
					}
					
				}
				else if (typeid(*gameObject) == typeid(Fruit)) {
					if (iteration % 4 == 0) {
						getPossibleDirs(gameObject->getPos(), possibleDirs);
						gameBoard.drawPos(gameObject->getPos());
						gameObject->move(getRandomMove(possibleDirs));
						static_cast<Fruit*>(gameObject)->turn();
						gameObject->draw();
					}

					if (player->isCollide(gameObject->getPos(), gameObject->getPrevPos())) {
						toEatFruit = static_cast<Fruit*>(gameObject);
					}
					else if(static_cast<Fruit*>(gameObject)->isDead()) {
						deadFruits.push_back(static_cast<Fruit*>(gameObject));
					}
				}
			}

			if (toEatFruit) {
				eatFruit(static_cast<Fruit*>(toEatFruit));
				fruitAmount--;
				toEatFruit = nullptr;
			}

			for (Fruit* f : deadFruits) {
				fruitDisappear(f);
			}
			deadFruits.clear();

			Sleep(speed);
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

void Game::initPositions() {
	for (const auto& gameObject : gameObjects) gameObject->initPos();
	draw();
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
	Position&& newPos = player->getPos().posAfterMove(dir);
	char gamePosObj = gameBoard.getPos(newPos);
	if (gamePosObj == '#') {
		return false;
	}
	return true;
}

bool Game::onBreadCurmb() {
	Position&& pos = player->getPos();
	char gamePosObj = gameBoard.getPos(pos);
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
	gotoxyPos(player->getPos());
}

void Game::draw() {
	clearScreen();
	gameBoard.print();
	for (const auto& gameObject : gameObjects) {
		gameObject->draw();
	}
	setStats();
}

void Game::fruitSpawn() {
	gameObjects.push_front(new Fruit());
	gameObjects.front()->initPos();
	if (isColors) gameObjects.front()->setColor(getRandomColor());
	gameObjects.front()->draw();
}

void Game::fruitDisappear(Fruit* fruit) {
	fruitAmount--;
	gameBoard.drawPos(fruit->getPos());
	gameObjects.remove_if([fruit](GameObject* obj) {
		return obj == fruit;
	});
}

void Game::eatFruit(Fruit* fruit) {
	logScreen("Eat a fruit, gained %d points", fruit->getVal());
	points += fruit->getVal();
	setStats();
	fruitDisappear(fruit);
	player->draw();
}

void Game::getPossibleDirs(const Position& pos, int possibleDirs[]) {
	if (gameBoard.get(pos.getX() - 1, pos.getY()) != '#' && isOnBounds(pos.getX() - 1, pos.getY())) possibleDirs[0] = 1;
	else possibleDirs[0] = 0;
	if (gameBoard.get(pos.getX() + 1, pos.getY()) != '#' && isOnBounds(pos.getX() + 1, pos.getY())) possibleDirs[1] = 1;
	else possibleDirs[1] = 0;
	if (gameBoard.get(pos.getX(), pos.getY() - 1) != '#' && isOnBounds(pos.getX(), pos.getY() - 1)) possibleDirs[2] = 1;
	else possibleDirs[2] = 0;
	if (gameBoard.get(pos.getX(), pos.getY() + 1) != '#' && isOnBounds(pos.getX(), pos.getY() + 1)) possibleDirs[3] = 1;
	else possibleDirs[3] = 0;
}