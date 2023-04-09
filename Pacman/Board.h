#pragma once
#include <iostream>
#include "Board.h"
#include "Position.h"
#include "utils.h"

using namespace std;

class Board {
    enum { WIDTH = 81, HEIGHT = 24 };
    char board[HEIGHT][WIDTH];
    int breadCurmbs = 611;
    char color = DEFAULT;
public:
    Board();
    void print();
    char get(int x, int y) const {
        return board[y][x];
    }
    bool isNoBreadCrumbs();
    void setPos(Position pos, char c);
    void setColor(int _color) { color = _color; };
};