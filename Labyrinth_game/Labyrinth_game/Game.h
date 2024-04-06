#pragma once
#include "Labyrinth.h"
#include "Bot.h"
#include "HumanPlayer.h"
#include "EasyBotPlayer.h"
#include "RookieBotPlayer.h"
#include "HardBotPlayer.h"
#include "FireAi.h"

class Game
{
public:
	Game(Labyrinth& _labyrinth, HumanPlayer _player);
	Game(Labyrinth& _labyrinth);
	void play();
	char BOT = 'o';
	char PLAYER = 'O';
	char FIRE = '@';
	bool add_fire(int x, int y);
private:
	HumanPlayer player;
	void find_exites();
	Labyrinth labyrinth;
	void initialize();
	void difficulty_mod();
	void difficulty_input();
	int difficulty;
	void fire_expanding(Point pos, int x, int y);
	void fire_expand();
	void fire_matrix_calc();
	std::queue<FireAi> fire_loc;
	EasyBotPlayer EasyBot;
	RookieBotPlayer RookieBot;
	HardBotPlayer HardBot;
	void print_frame(std::vector<std::string>& mod_labyrinth);
	bool move_player(int dir, Player& player);
	
};

