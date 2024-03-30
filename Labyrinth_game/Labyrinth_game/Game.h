#pragma once
#include "Labyrinth.h"
#include "HumanPlayer.h"

class Game
{
public:
	Game(Labyrinth& _labyrinth, HumanPlayer _player_1);
	void play();
private:
	HumanPlayer player_1;
	Labyrinth& labyrinth;
	void initialize_variables();
	void difficulty_mod();
	void difficulty_input();
	int difficulty;
	bool random_move;
	void print_frame(std::vector<std::string>& mod_labyrinth);
	bool move_player(int dir, Player& player);
	
};

