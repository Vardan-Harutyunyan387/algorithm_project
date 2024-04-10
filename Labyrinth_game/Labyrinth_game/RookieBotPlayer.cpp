#include <iostream>
#include "RookieBotPlayer.h"

RookieBotPlayer::RookieBotPlayer() {}
RookieBotPlayer::RookieBotPlayer(int x, int y, char sym) : Player(x, y, sym) {}
RookieBotPlayer::RookieBotPlayer(Point pos, char sym) : Player(pos, sym) {}

//Doing random move
void RookieBotPlayer::move(Labyrinth& labyrinth) {
    srand((unsigned)time(NULL));
    int x = 0, y = 0;
    while (true) {
        x = (rand() % 3) - 1;
        if (x == 0)
            y = (rand() % 3) - 1;
        if (!labyrinth.is_valid_move(this->position.x + x, this->position.y + y) || (x == 0 && y == 0)) {
            continue;
        }
        break;
    }
    change_position(Point(this->position.x + x, this->position.y + y), labyrinth);
}