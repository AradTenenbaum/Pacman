#pragma once
#include "Position.h"
#include "utils.h"

class GameObject {
protected:
	Position pos;
	Position prevPos;
	const char sign;
	char color = DEFAULT;
public:
	GameObject(char _sign, char _color) : sign(_sign), color(_color) {};
	virtual ~GameObject() = default;
	virtual void move(int dir);
	virtual void initPos() = 0;
	void setColor(int _color) { color = _color; };
	Position getPrevPos() { return prevPos; };
	Position getPos() { return pos; };
	bool isCollide(const Position& _pos, const Position& _prevPos) const;
	void draw();
};