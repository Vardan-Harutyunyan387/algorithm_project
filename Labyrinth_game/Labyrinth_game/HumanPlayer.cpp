#include "HumanPlayer.h"


HumanPlayer::HumanPlayer() {}
HumanPlayer::HumanPlayer(int x, int y, char sym) : Player(x, y, sym) {}
HumanPlayer::HumanPlayer(Point pos, char sym) : Player(pos, sym) {}