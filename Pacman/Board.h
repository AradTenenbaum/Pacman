#pragma once
#include <iostream>
#include "Board.h"
#include "Position.h"
#include "utils.h"

class Board {
    enum { WIDTH = 81, HEIGHT = 24, WALL= '#', BREAD_CRUMB = '*' };
    char board[HEIGHT][WIDTH];
    int breadCurmbs = 611;
    char color = DEFAULT;
public:
    Board();
    void setBoard(char _board[HEIGHT][WIDTH]);
    //char[HEIGHT][WIDTH] getBoard() { return board; };
    void print();
    char get(int x, int y) const {
        return board[y][x];
    }
    char getPos(const Position& pos) const {
        return board[pos.getY()][pos.getX()];
    }
    bool isNoBreadCrumbs();
    void setPos(const Position& pos, char c);
    void setColor(int _color) { color = _color; };
    void drawPos(const Position& pos);
};