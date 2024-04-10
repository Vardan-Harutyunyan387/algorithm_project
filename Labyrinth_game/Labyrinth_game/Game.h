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
	char BOT = 'B';
	char PLAYER = 'P';
	char FIRE = 'F';
	char DEAD = 'X';
	char PLAYER_AND_BOT = 'U';
	bool add_fire(int x, int y);
private:
	HumanPlayer player;
	Labyrinth labyrinth;
	Player* bot_player;

	//std::vector<std::string> getDirectoryFiles(const fs::path& directory = fs::current_path(),
	//	const std::vector<std::string> extensions = {});
	char getKeyPress();
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
	void resetConsoleMode();
	
};

