#pragma once
#include "BotAlgorithms.h"

class MediumBotPlayer : protected BotAlgorithms, public Player
{
private:
	std::queue<Point> path;
public:
	void bot_medium_mod_algorithm(Labyrinth& labyrinth);
	void move(Labyrinth& labyrinth);
	MediumBotPlayer(int x, int y, char sym);
	MediumBotPlayer();
	MediumBotPlayer(Point pos, char sym, Labyrinth& labyrinth);
	void start(Labyrinth& labyrinth);
};