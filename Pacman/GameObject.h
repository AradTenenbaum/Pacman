#pragma once
#include "GameObject.h"
#include "Position.h"
#include "utils.h"
class GameObject {
protected:
	enum { LEFT, RIGHT, UP, DOWN };
	Position pos;
	Position prevPos;
	Position startPos;
	const char sign;
	char color = DEFAULT;
	int movesNum = 0;
	int counter = 0;
public:
	GameObject(char _sign, char _color, Position& _startPos) : sign(_sign), color(_color), startPos(_startPos) {};
	virtual ~GameObject() = default;
	virtual void move(int dir);
	void setColor(int _color) { color = _color; };
	void setStartPos(int x, int y) { startPos.setPos(x, y); };
	void initPos() { pos.setPos(startPos.getX(), startPos.getY()); };
	Position getPrevPos() { return prevPos; };
	Position getPos() { return pos; };
	int getMovesNum() { return movesNum; };
	void startCounter() { counter = movesNum; };
	bool isXMovesPassed(int x) { return ((movesNum - counter) == x); };
	bool isCollide(const Position& _pos, const Position& _prevPos) const;
	void increaseMovesNum() { movesNum++; };
	void draw();
};