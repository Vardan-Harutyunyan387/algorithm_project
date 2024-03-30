#include <iostream>
#include "Labyrinth.h"
#include "HumanPlayer.h"
#include "Game.h"

int main()
{
	enum Direction {
		RIGHT = 0,
		UP = 1,
		LEFT = 2,
		DOWN = 3
	};
    Labyrinth lab_1;
	lab_1.add_fire(1, 8);
	lab_1.change_bot_position({ 4, 6 });
	lab_1.fire_matrix_calc();
    HumanPlayer player_1(5, 6,'p');
	Game game(lab_1, player_1);
	game.play();
}

