#include "HardBotPlayer.h"
#include<iostream>

HardBotPlayer::HardBotPlayer() {}
HardBotPlayer::HardBotPlayer(int x, int y, char sym) : Player(x, y, sym) {}
HardBotPlayer::HardBotPlayer(Point pos, char sym, Labyrinth& labyrinth) : Player(pos, sym)
{
    this->start(labyrinth);
}


void HardBotPlayer::bot_hard_mod_algorithm(Labyrinth& labyrinth) {
    std::queue<Point> shortest_path_1, shortest_path_2;
    std::vector<std::vector<int>> shortest_path_matrix(labyrinth.get_rows(), std::vector<int>(labyrinth.get_cols(), 1001));
    bot_mod_main_algorithm(shortest_path_matrix, labyrinth, position);

    bool first_path = bot_shortest_path_algorithm(labyrinth.get_finish(1), shortest_path_matrix, shortest_path_1, labyrinth);
    bool second_path = bot_shortest_path_algorithm(labyrinth.get_finish(2), shortest_path_matrix, shortest_path_2, labyrinth);
    queue_reverse(shortest_path_2);
    queue_reverse(shortest_path_1);
    //check wich path is shortest for our 2 finishes
    if (!second_path || (first_path && shortest_path_2.size() > shortest_path_1.size())) {
        path = shortest_path_1;
        return;
    }
    path = shortest_path_2;
}


void HardBotPlayer::start(Labyrinth& labyrinth) {
    bot_hard_mod_algorithm(labyrinth);
}



void HardBotPlayer::move(Labyrinth& labyrinth) {
    if (path.empty())
        return;
    change_position(path.front() , labyrinth);
    path.pop();
}

