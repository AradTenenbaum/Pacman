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
	return isSamePos(_pos, pos) || (isSamePos(_prevPos, pos) && (isSamePos(prevPos, _pos)));
}

void GameObject::move(int dir) {
	prevPos = pos;

	if (dir == 0) {
		pos.addX(-1);
	}
	if (dir == 1) {
		pos.addX(1);
	}
	if (dir == 2) {
		pos.addY(-1);
	}
	if (dir == 3) {
		pos.addY(1);
	}
}