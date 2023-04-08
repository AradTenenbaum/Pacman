#pragma once
#include <iostream>
#include "Board.h"
#include "Position.h"

using namespace std;

class Board {
    enum { WIDTH = 81, HEIGHT = 24 };
    char board[HEIGHT][WIDTH];
    int breadCurmbs = 611;
public:
    Board();
    void print() const;
    char get(int x, int y) const {
        return board[y][x];
    }
    bool isNoBreadCrumbs();
    void setPos(Position pos, char c);
};