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