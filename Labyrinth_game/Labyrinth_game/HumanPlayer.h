#pragma once
#include "Player.h"
#include "Labyrinth.h"

class HumanPlayer:public Player
{
private:
	const Labyrinth& labyrinth;

public:
	char sym;
	Point player_loc;
	HumanPlayer(int x, int y, char sym, const Labyrinth& _labyrinth);
	bool move_player(int dir) override;
};

