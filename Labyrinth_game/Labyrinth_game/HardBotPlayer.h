#pragma once
#include "BotAlgorithms.h"

class HardBotPlayer : protected BotAlgorithms, public Player
{
private:
	std::queue<Point> path;
public:
	void bot_hard_mod_algorithm(Labyrinth& labyrinth);
	void move(Labyrinth& labyrinth);
	HardBotPlayer(int x, int y, char sym);
	HardBotPlayer();
	HardBotPlayer(Point pos, char sym);
	void start(Labyrinth& labyrinth);
};