#include "Game.h"
#include <iostream>
#include <cctype>
Game::Game(Labyrinth& _labyrinth, HumanPlayer _player_1):labyrinth(_labyrinth), player_1(_player_1)
{
}

void Game::start_game()
{
    char input;

    while (true) {
        std::vector<std::string> mod_labyrinth(labyrinth.get_labyrinth()); // get labyrinth

        this->print_frame(mod_labyrinth); // print current labyrinth with player_1

        do {
            std::cin >> input;
            input = std::toupper(input);
            if (player_1.move_player(input))
            {
                break;
            }


        } while (true);

        labyrinth.fire_expand();
    }

}

void Game::print_frame(std::vector<std::string>& mod_labyrinth)
{
    mod_labyrinth[player_1.player_loc.x][player_1.player_loc.y] = player_1.sym;
    for (const auto& i : mod_labyrinth)
    {
        std::cout << i << std::endl;
    }
}
