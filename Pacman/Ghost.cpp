#include "Ghost.h"
#include <iostream>
#include <cstdlib>
#include "utils.h"
using namespace std;

void Ghost::move(int dir) {
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



void Ghost::initPos() {
	pos.setPos(66, 21);
}