#include "Player.h"
#include <iostream>
Player::Player() {}
Player::Player(int x, int y, char sym) :sym(sym)
{
	position = Point(x, y);
}
Player::Player(Point pos, char sym): position(pos),sym(sym) {}

bool Player::change_position(Point pos, Labyrinth& labyrinth) {
    if (!labyrinth.is_valid_move(pos)) {
        return false;
    }
    labyrinth.labyrinth[position.y][position.x] = labyrinth.SPACE;
    labyrinth.labyrinth[pos.y][pos.x] = sym;
    position = pos;
    return true;
}

void Player::move(Labyrinth &labyrinth)
{
    std::cout << "do nothing" << std::endl;
}
