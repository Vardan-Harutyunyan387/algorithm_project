#pragma once
#include "Labyrinth.h"
//#include "Bot.h"
#include "HumanPlayer.h"
#include "EasyBotPlayer.h"
#include "RookieBotPlayer.h"
#include "HardBotPlayer.h"
#include "MediumBotPlayer.h"
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
	Labyrinth labyrinth;
	Player* bot_player;
	bool have_winner = 0;
	std::string endgame_message;

	void find_exites();
	void initialize();
	void difficulty_input();
	int difficulty;
	void fire_expanding(Point pos, int x, int y);
	void fire_expand();
	void fire_matrix_calc();
	std::queue<FireAi> fire_loc;
	EasyBotPlayer EasyBot;
	RookieBotPlayer RookieBot;
	HardBotPlayer HardBot;
	MediumBotPlayer MediumBot;
	void print_frame(const std::vector<std::string>& mod_labyrinth) const;
	bool check_winner();
	Point move_to_dir(char dir, Point loc);
	
};

