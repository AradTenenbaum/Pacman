#include "Position.h"
#include "utils.h"

Position Position::posAfterMove(int dir) {
	Position newPos = Position(x, y);
	if ((dir == LEFT) || (dir == LEFT_L)) {
		newPos.addX(-1);
	}
	else if ((dir == RIGHT) || (dir == RIGHT_L)) {
		newPos.addX(1);
	}
	else if ((dir == UP) || (dir == UP_L)) {
		newPos.addY(-1);
	}
	else if ((dir == DOWN) || (dir == DOWN_L)) {
		newPos.addY(1);
	}
	return newPos;
}

void Position::setPos(int _x, int _y) {
	x = _x;
	y = _y;
}