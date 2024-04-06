#pragma once
#include "Point.h"
#include "Labyrinth.h"
class Player
{
private:
public:
	char sym;
	Point position;
	bool change_position(Point pos, Labyrinth& labyrinth);
	Player();
	Player(int x, int y, char sym);
	Player(Point pos, char sym);
};

