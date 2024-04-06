#pragma once
#include "BotAlgorithms.h"

class FireAi : protected BotAlgorithms, public Player
{
private:
public:

	void fire_matrix_calc_algorithm(Labyrinth& labyrinth);
	FireAi(int x, int y, char sym);
	FireAi();
	FireAi(Point pos, char sym);
};