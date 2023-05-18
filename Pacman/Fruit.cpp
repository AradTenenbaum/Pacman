#include "Fruit.h"
#include <iostream>
#include <cstdlib>
#include "utils.h"

using namespace std;

void Fruit::initPos() {
	int random = getRandomNumber(1, 3);
	if(random == 1) pos.setPos(5, 22);
	if (random == 2) pos.setPos(77, 1);
	if (random == 3) pos.setPos(47, 10);
}

void Fruit::turn() {
	ttl--;
}