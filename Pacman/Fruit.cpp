#include "Fruit.h"
#include <iostream>
#include <cstdlib>
#include "utils.h"

using namespace std;

void Fruit::move(int dir) {
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

void Fruit::initPos() {
	pos.setPos(5, 22);
}