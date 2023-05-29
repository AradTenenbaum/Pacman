#pragma once
#include "Menu.h"

class Menu {
public:
	void display();
	void instructions();
	void settings(bool& isColors);
	void levels(int& level, bool& isInProgress);
	void difficulties(char& difficulty);
};