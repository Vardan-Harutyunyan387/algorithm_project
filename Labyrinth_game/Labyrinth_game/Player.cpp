#include "Player.h"

Player::Player(int x, int y, char sym) :sym(sym)
{
	player_loc = Point(x, y);
}
