#pragma once
#include "Labyrinth.h"
#include "HumanPlayer.h"

class Game
{
public:
	Game(Labyrinth& _labyrinth, HumanPlayer _player_1);
	void start_game();
private:
	HumanPlayer player_1;
	Labyrinth& labyrinth;

	void print_frame(std::vector<std::string>& mod_labyrinth);
	
};

