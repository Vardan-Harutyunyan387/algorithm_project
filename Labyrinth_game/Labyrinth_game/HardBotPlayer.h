#pragma once
#include "BotAlgorithms.h"

class HardBotPlayer : protected BotAlgorithms, public Player
{
private:
	std::queue<Point> path;
public:
	void bot_hard_mod_algorithm(Labyrinth& labyrinth);
	void move(Labyrinth& labyrinth) override;
	HardBotPlayer(int x, int y, char sym);
	HardBotPlayer();
	HardBotPlayer(Point pos, char sym, Labyrinth& labyrinth);
	void start(Labyrinth& labyrinth);
};