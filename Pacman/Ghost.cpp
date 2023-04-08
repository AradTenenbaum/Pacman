#include "Ghost.h"
#include <iostream>
#include <cstdlib>
#include "utils.h"
using namespace std;

void Ghost::move(int possibleDirs[], char prevChar) {

	gotoxyPos(pos);
	cout << prevChar;

	int dir, dirIndex = 0, numOfDirs = 0;
	for (int i = 0; i < 4; i++) {
		if (possibleDirs[i] == 1) numOfDirs++;
	}
	dir = rand() % 4;
	int i = 0;
	int newIndex = (dir % numOfDirs);
	while (newIndex >= 0) {
		if (possibleDirs[dirIndex] == 1) newIndex--;
		dirIndex++;
	}
	dirIndex--;
	if (dirIndex == 0) {
		pos.addX(-1);
	}
	if (dirIndex == 1) {
		pos.addX(1);
	}
	if (dirIndex == 2) {
		pos.addY(-1);
	}
	if (dirIndex == 3) {
		pos.addY(1);
	}

}

void Ghost::draw() {
	gotoxyPos(pos);
	cout << sign;
}

void Ghost::undraw() {
	gotoxyPos(pos);
	cout << ' ';
}

void Ghost::initPos() {
	pos.setPos(66, 21);
}