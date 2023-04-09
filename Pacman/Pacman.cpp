#include <iostream>
#include "Pacman.h"
#include "utils.h"

using namespace std;

void Pacman::move(int dir) {
	undraw();
	
	if ((dir == LEFT) || (dir == LEFT_L)) {
		if (pos.isTunnel(dir)) pos.setPos(WIDTH-2, pos.getY());
		else pos.addX(-1);
	}
	else if ((dir == RIGHT) || (dir == RIGHT_L)) {
		if (pos.isTunnel(dir)) pos.setPos(0, pos.getY());
		else pos.addX(1);
	}
	else if ((dir == UP) || (dir == UP_L)) {
		if (pos.isTunnel(dir)) pos.setPos(pos.getX(), HEIGHT - 1);
		else pos.addY(-1);
	}
	else if ((dir == DOWN) || (dir == DOWN_L)) {
		if (pos.isTunnel(dir)) pos.setPos(pos.getX(), 0);
		else pos.addY(1);
	}
}

void Pacman::draw() {
	gotoxyPos(pos);
	setElementColor(color);
	cout << sign;
	setElementColor(DEFAULT);
}

void Pacman::undraw() {
	gotoxyPos(pos);
	cout << ' ';
}

void Pacman::initPos() {
	undraw();
	pos.setPos(1, 1);
}