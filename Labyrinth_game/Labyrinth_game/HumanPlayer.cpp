#include "HumanPlayer.h"


HumanPlayer::HumanPlayer() {}
HumanPlayer::HumanPlayer(int x, int y, char sym) : Player(x, y, sym) {}
HumanPlayer::HumanPlayer(Point pos, char sym) : Player(pos, sym) {}

bool HumanPlayer::move_player(int dir, Labyrinth& labyrinth)
{
    switch (dir) {
    case 'D':
        if (labyrinth.is_valid_move(position.x + 1, position.y))
        {
            this->change_position(Point(position.x + 1, position.y), labyrinth);
            return true;
        }
        return false;
    case 'W':
        if (labyrinth.is_valid_move(position.x, position.y - 1))
        {
            this->change_position(Point(position.x, position.y - 1), labyrinth);
            return true;
        }
        return false;
    case 'A':
        if (labyrinth.is_valid_move(position.x - 1, position.y))
        {
            this->change_position(Point(position.x - 1, position.y), labyrinth);
            return true;
        }
        return false;
    case 'S':
        if (labyrinth.is_valid_move(position.x, position.y + 1))
        {
            this->change_position(Point(position.x, position.y + 1), labyrinth);
            return true;
        }
        return false;
    default:
        return false;
    }

}
