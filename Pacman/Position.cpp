#include "Position.h"
#include "utils.h"

Position Position::posAfterMove(int dir) {
	Position newPos = Position(x, y);

	if ((dir == LEFT) || (dir == LEFT_L) || (dir == 0)) {
		newPos.addX(-1);
	}
	else if ((dir == RIGHT) || (dir == RIGHT_L) || (dir == 1)) {
		newPos.addX(1);
	}
	else if ((dir == UP) || (dir == UP_L) || (dir == 2)) {
		newPos.addY(-1);
	}
	else if ((dir == DOWN) || (dir == DOWN_L) || (dir == 3)) {
		newPos.addY(1);
	}
	return newPos;
}

void Position::setPos(int _x, int _y) {
	x = _x;
	y = _y;
}

bool Position::isTunnel(int dir) {
	if ((dir == LEFT) || (dir == LEFT_L)) {
		return (x == 0);
	}
	else if ((dir == RIGHT) || (dir == RIGHT_L)) {
		return (x == (WIDTH - 2));
	}
	else if ((dir == UP) || (dir == UP_L)) {
		return (y == 0);
	}
	else if ((dir == DOWN) || (dir == DOWN_L)) {
		return (y == (HEIGHT - 1));
	}
	return false;
}