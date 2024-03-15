#pragma once
#include "Point.h"
#include "Labyrinth.h"
class Player
{
public:
	char sym;
	Point player_loc;
	virtual bool move_player(int dir) = 0; // 0-right 1-up 2-left 3-down 
};

