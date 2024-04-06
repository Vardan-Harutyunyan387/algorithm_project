#pragma once
#include "Player.h"
#include "Labyrinth.h"

class HumanPlayer: public Player
{
public:
	HumanPlayer();
	HumanPlayer(Point pos, char sym);
	HumanPlayer(int x, int y, char sym);
	bool move_player(int dir, Labyrinth& labyrinth);
};

