#pragma once
#include "Player.h"

class EasyBotPlayer : public Player
{
public:
	EasyBotPlayer(int x, int y, char sym);
	EasyBotPlayer(Point pos, char sym);
	void move(Labyrinth& labyrinth);
	EasyBotPlayer();
};