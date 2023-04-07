﻿#include "Board.h"
#include <string>

Board::Board() : board{ {"################################################################################"}, 
						{"#*************#**************#*************************************************#"}, // 77 breadcrumbs
						{"#*************#***********************************#****************************#"}, // 77 breadcrumbs
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#****************************#********************#****************************#"}, // 77
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#****************************#********************#****************************#"}, // 77
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#****************************#********************#****************************#"}, // 77
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#****************************#********************#****************************#"}, // 77
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#####*###*###########**###########################################*#############"}, // 5
						{"#****************************#********************#****************************#"}, // 77
						{"################################################################################"}} 
{}

void Board::print() const {
	for (string line : board) {
		cout << line << endl;
	}
}

void Board::setPos(Position pos, char c) {
	if (board[pos.getY()][pos.getX()] == '*') breadCurmbs--;
	board[pos.getY()][pos.getX()] = c;
}