#include "Ghost.h"
#include <iostream>
#include <cstdlib>
#include "utils.h"
#include "Board.h"
#include <set>
#include <stack>
#include "Position.h"
#include <math.h>

using namespace std;

void Ghost::smartMove(const Position& target, int possibleDirs[]) {
	prevPos = pos;
	movesNum++;

	int dir = -1;
	if (target.getX() < pos.getX() && (possibleDirs[0] == 1)) {
		dir = 0;
	}
	else if (target.getX() > pos.getX() && (possibleDirs[1] == 1)) {
		dir = 1;
	}
	else if (target.getY() < pos.getY() && (possibleDirs[2] == 1)) {
		dir = 2;
	}
	else if (target.getY() > pos.getY() && (possibleDirs[3] == 1)) {
		dir = 3;
	}

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

/*

---This is A* algorithm, I'm not using it now, maybe I will in the next excersise---

struct cell {
	int parent_i, parent_j;
	double f, g, h;
};

struct fPos {
	double f;
	Position pos;
	fPos(double _f, Position _pos) : f(_f), pos(_pos) {}
	bool operator<(const fPos& other) const noexcept { 
		if (this->f < other.f) return true;
		else if (this->f > other.f) return false;
		else {
			if (this->pos.getX() < other.pos.getX()) return true;
			else if (this->pos.getX() > other.pos.getX()) return false;
			else return (this->pos.getY() < other.pos.getY());
		}
	};
};

bool isValid(Position& pos)
{
	return pos.getX() >= 0 && pos.getX() < (WIDTH-1) && pos.getY() >= 0 && pos.getY() < HEIGHT;
}

bool isUnBlocked(Board board, Position& pos)
{
	return board.getPos(pos) != WALL;
}

double calculateHValue(Position& temp, const Position& dest)
{
	return abs(temp.getX() - dest.getX()) + abs(temp.getY() - dest.getY());
}

void tracePath(cell cellDetails[HEIGHT][WIDTH], const Position& dest)
{
	int row = dest.getY();
	int col = dest.getX();

	stack<Position> Path;

	while (!(cellDetails[row][col].parent_i == row
		&& cellDetails[row][col].parent_j == col)) {
		Path.push(Position(col, row));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(Position(col, row));
	while (!Path.empty()) {
		Position p = Path.top();
		Path.pop();
		logScreen("-> (%d,%d) ", p.getX(), p.getY());
	}
}


Position posAfterDir(Position& ind, int dir) {
	int newX = ind.getX();
	int newY = ind.getY();
	if (dir == 0) newX -= 1;
	if (dir == 1) newX += 1;
	if (dir == 2) newY -= 1;
	if (dir == 3) newY += 1;
	return Position(newX, newY);
}

void paintRed(int x, int y) {
	setElementColor(90);
	gotoxy(x, y);
	cout << " ";
	setElementColor(DEFAULT);
}

void paintGreen(int x, int y) {
	setElementColor(102);
	gotoxy(x, y);
	cout << " ";
	setElementColor(DEFAULT);

}

void Ghost::aStarSearch(Board board, const Position& src, const Position& dest) {
	bool closedList[HEIGHT][WIDTH];
	memset(closedList, false, sizeof(closedList));

	int directions[] = { 0, 1, 2, 3 };

	cell cellDetails[HEIGHT][WIDTH];
	int i, j;
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}
	i = src.getY(), j = src.getX();
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	set<fPos> openList;
	fPos temp = fPos(0.0, Position(j, i));
	openList.insert(temp);
	paintGreen(j, i);

	bool foundDest = false;

	while (!openList.empty()) {
		fPos q = *openList.begin();
		openList.erase(openList.begin());

		i = q.pos.getY();
		j = q.pos.getX();
		closedList[i][j] = true;
		paintRed(j, i);

		if (i == 2 && j == 25) {
			int a = 5;
		}

		double gNew, hNew, fNew;

		for (int dir : directions) {
			Position tempPos = posAfterDir(q.pos, dir);

			if (isValid(tempPos)) {
				if (tempPos == dest) {
					cellDetails[tempPos.getY()][tempPos.getX()].parent_i = i;
					cellDetails[tempPos.getY()][tempPos.getX()].parent_j = j;
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				}

				else if (!closedList[tempPos.getY()][tempPos.getX()] && isUnBlocked(board, tempPos)) {
					gNew = cellDetails[i][j].g + 1.0;
					hNew = calculateHValue(tempPos, dest);
					fNew = gNew + hNew;

					if (cellDetails[tempPos.getY()][tempPos.getX()].f == FLT_MAX
						|| cellDetails[tempPos.getY()][tempPos.getX()].f > fNew) {
						openList.insert(fPos(fNew, Position(tempPos.getX(), tempPos.getY())));
						paintGreen(tempPos.getX(), tempPos.getY());

						cellDetails[tempPos.getY()][tempPos.getX()].f = fNew;
						cellDetails[tempPos.getY()][tempPos.getX()].g = gNew;
						cellDetails[tempPos.getY()][tempPos.getX()].h = hNew;
						cellDetails[tempPos.getY()][tempPos.getX()].parent_i = i;
						cellDetails[tempPos.getY()][tempPos.getX()].parent_j = j;
					}
				}
			}
		}


	}
	if (!foundDest)
		logScreen("Failed to find the Destination Cell\n");
}
*/
