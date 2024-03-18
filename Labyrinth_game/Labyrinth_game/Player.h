#pragma once
#include "Point.h"
#include "Labyrinth.h"
class Player
{
public:
	char sym;
	Point player_loc;

	Player(int x, int y, char sym);
};

