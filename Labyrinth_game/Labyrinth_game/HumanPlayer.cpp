#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int x, int y, char sym, const Labyrinth& _labyrinth):sym(sym), labyrinth(_labyrinth)
{
	player_loc = Point(x, y);
}

bool HumanPlayer::move_player(int dir)
{
    switch (dir) {
    case 'D':
        if (labyrinth.is_valid_move(player_loc.x, player_loc.y + 1))
        {
            player_loc.y += 1;
            return true;
        }
        return false;
    case 'W':
        if (labyrinth.is_valid_move(player_loc.x - 1, player_loc.y))
        {
            player_loc.x -= 1;
            return true;
        }
        return false;
    case 'A':
        if (labyrinth.is_valid_move(player_loc.x, player_loc.y - 1))
        {
            player_loc.y -= 1;
            return true;
        }
        return false;
    case 'S':
        if (labyrinth.is_valid_move(player_loc.x + 1, player_loc.y))
        {
            player_loc.x += 1;
            return true;
        }
        return false;
    default:
        return false;
    }
}

