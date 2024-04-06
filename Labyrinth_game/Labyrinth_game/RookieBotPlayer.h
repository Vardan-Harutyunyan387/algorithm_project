#pragma once
#include "Player.h"

class RookieBotPlayer : public Player
{
public:
	RookieBotPlayer();
	RookieBotPlayer(int x, int y, char sym);
	RookieBotPlayer(Point pos, char sym);
	void move(Labyrinth& labyrinth);

};