#include <iostream>
#include "EasyBotPlayer.h"

EasyBotPlayer::EasyBotPlayer()  {}
EasyBotPlayer::EasyBotPlayer(int x, int y, char sym): Player(x,y,sym) {}
EasyBotPlayer::EasyBotPlayer(Point pos, char sym): Player(pos,sym) {}

//Doing random move
void EasyBotPlayer::move(Labyrinth& labyrinth) {


    srand((unsigned)time(NULL));
    int x = 0, y = 0;
    while (true) {
        x = (rand() % 3) - 1;
        if(x == 0)
            y = (rand() % 3) - 1;
        if (!labyrinth.is_valid_move(this->position.x + x, this->position.y + y) || (labyrinth.labyrinth[position.y + y][x + position.x + x] == labyrinth.FIRE) || (x == 0 && y == 0)) {
            continue;
        }
        break;
    }
    change_position(Point(this->position.x + x, this->position.y + y), labyrinth);

}