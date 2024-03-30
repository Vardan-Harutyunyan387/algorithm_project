#include "Game.h"
#include <iostream>
#include <cctype>
Game::Game(Labyrinth& _labyrinth, HumanPlayer _player_1):labyrinth(_labyrinth), player_1(_player_1)
{
    random_move = false;
}

void Game::difficulty_input() {
    std::cout << "Please choose the difficluty Number:\n"
        << "1. Rookie \n" 
        << "2. Easy\n" 
        << "3. Medium\n"
        << "4. Hard";
    std::cin >> difficulty;
    while (difficulty > 4 || difficulty < 0) {
        std::cout << "Wrong numbre. Please choose difficluty number again from 1 to 4\n";
        std::cin >> difficulty;
    }
}

void Game::difficulty_mod() {
    difficulty_input();
    if (difficulty == 1 || difficulty == 2) {
        random_move = true;
        return;
    }
    labyrinth.difficulty_algorithm(difficulty);
}

void Game::play()
{
    difficulty_mod();
    char input;

    labyrinth.fire_matrix_calc();
    while (true) {
        std::vector<std::string> mod_labyrinth(labyrinth.get_labyrinth()); // get labyrinth

        this->print_frame(mod_labyrinth); // print current labyrinth with player_1

        do {
            std::cin >> input;
            input = std::toupper(input);
            if (move_player(input, player_1))
            {
                break;
            }


        } while (true);
        if (random_move)
            labyrinth.bot_rand_moving(random_move);
        else
            labyrinth.bot_moving();
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

bool Game::move_player(int dir, Player& player)
{
    switch (dir) {
    case 'D':
        if (labyrinth.is_valid_move(player.player_loc.x, player.player_loc.y + 1))
        {
            player.player_loc.y += 1;
            return true;
        }
        return false;
    case 'W':
        if (labyrinth.is_valid_move(player.player_loc.x - 1, player.player_loc.y))
        {
            player.player_loc.x -= 1;
            return true;
        }
        return false;
    case 'A':
        if (labyrinth.is_valid_move(player.player_loc.x, player.player_loc.y - 1))
        {
            player.player_loc.y -= 1;
            return true;
        }
        return false;
    case 'S':
        if (labyrinth.is_valid_move(player.player_loc.x + 1, player.player_loc.y))
        {
            player.player_loc.x += 1;
            return true;
        }
        return false;
    default:
        return false;
    }
}
