#include "Game.h"
#include "Board.h"
#include "Ghost.h"
#include <conio.h>
#include <windows.h>
#include <typeinfo>
#include "utils.h"
#include <typeinfo>
#include <fstream>
#include <string>

using namespace std;

void Game::startMenu() {
	int choice;
	bool isPressedExit = false;
	while (!isPressedExit) {
		menu.display();
		cin >> choice;
		if (choice == 1) {
			init();
			run();
		}
		else if (choice == 6) {
			menu.levels(level, isInProgress);
		}
		else if (choice == 7) {
			menu.settings(isColors);
		}
		else if (choice == 8) {
			menu.instructions();
		}
		else if (choice == 9) {
			isPressedExit = true;
		}
	}
}

char board[HEIGHT][WIDTH];

void Game::init() {
	isErrorInInit = false;
	fstream newfile;
	newfile.open(formatStr("pacman_%02d.screen.txt", level), ios_base::in);


	gameObjects.clear();

	if (newfile.is_open()) {
		string tp;
		int i = 0;
		while (getline(newfile, tp)) {
			for (int j = 0; j <= tp.size(); j++) {
				Position pos = Position(j, i);
				if (tp[j] == '%') board[i][j] = SPACE;
				else if (tp[j] == '@') {
					Pacman* player = new Pacman(pos);
					gameObjects.push_back(player);
					setPlayer(player);
					board[i][j] = SPACE;
				}
				else if (tp[j] == '$') {
					gameObjects.push_back(new Ghost(pos));
					board[i][j] = SPACE;
				}
				else board[i][j] = tp[j];
			}
			i++;
		}
		newfile.close();
	}
	else {
		isErrorInInit = true;
		return;
	}
 
	clearScreen();

	gameBoard.setBoard(board);

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
	if (!isInProgress) lives = LIVES;
	draw();
}

void Game::run() {
	if (isErrorInInit) {
		clearScreen();
		gotoxy(0, 0);
		cout << "Error in init game -> file not exists" << endl;
		cout << "-------------------------------------" << endl;
		cout << "Press ENTER to back to the menu" << endl;
		char key = 0;
		do {
			if (_kbhit()) key = _getch();
		} while (key != ENTER);
		return;
	}

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
	Position spot;

	int possibleDirs[4] = { 0,0,0,0 };

	while (!isGameOver) {
		do {
			// count game iterations
			iteration++;

			if (((iteration % 10) == getRandomNumber(1, 10)) && (fruitAmount <= maxFruitAmount)) {
				spot = Position(getRandomNumber(0, WIDTH - 2), getRandomNumber(0, HEIGHT - 1));
				if (isFreeSpot(spot)) {
					fruitSpawn(spot);
				}
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
						static_cast<Pacman*>(gameObject)->move(key);
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
						//logScreen("not a valid move: %d", key);
					}
				}
				else if (typeid(*gameObject) == typeid(Ghost)) {
					if (iteration % 2 == 0) {
						// ghosts move
						getPossibleDirs(gameObject->getPos(), possibleDirs);
						gameBoard.drawPos(gameObject->getPos());
						//gameObject->move(getRandomMove(possibleDirs));
						static_cast<Ghost*>(gameObject)->smartMove(player->getPos(), possibleDirs);
						gameObject->draw();
					}

					//TEST
					//static_cast<Ghost*>(gameObject)->aStarSearch(gameBoard, gameObject->getPos(), player->getPos());
					//TEST

					// check if player on the same position of one of the ghosts
					// check if player or one of the ghosts swap places
					// drop one live if true
					if (player->isCollide(gameObject->getPos(), gameObject->getPrevPos())) {
						dropLive();
						initPositions();
						key = STAY;
						//logScreen("Hit by a ghost");
					}

					for (const auto& gameObject2 : gameObjects) {
						if (typeid(*gameObject2) == typeid(Fruit)) {
							if (gameObject->isCollide(gameObject2->getPos(), gameObject2->getPrevPos())) {
								deadFruits.push_back(static_cast<Fruit*>(gameObject2));
							}
						}
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
			isInProgress = false;
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
			isInProgress = true;
			level++;
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

void Game::fruitSpawn(Position& spot) {
	gameObjects.push_front(new Fruit(spot));
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
	//logScreen("Eat a fruit, gained %d points", fruit->getVal());
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

bool Game::isFreeSpot(Position& spot) {
	if (gameBoard.getPos(spot) == '#') return false;
	for (const auto& gameObject : gameObjects) {
		if (gameObject->getPos() == spot) return false;
	}
	return true;
}