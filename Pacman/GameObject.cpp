#include <iostream>
#include "GameObject.h"
#include "utils.h"

using namespace std;

void GameObject::draw() {
	gotoxyPos(pos);
	setElementColor(color);
	cout << sign;
	setElementColor(DEFAULT);
}

bool GameObject::isCollide(const Position& _pos, const Position& _prevPos) const {
	return (_pos == pos) || ((_prevPos == pos) && (prevPos == _pos));
}

void GameObject::move(int dir) {
	prevPos = pos;
	movesNum++;

	if (dir == LEFT) {
		pos.addX(-1);
	}
	if (dir == RIGHT) {
		pos.addX(1);
	}
	if (dir == UP) {
		pos.addY(-1);
	}
	if (dir == DOWN) {
		pos.addY(1);
	}
}