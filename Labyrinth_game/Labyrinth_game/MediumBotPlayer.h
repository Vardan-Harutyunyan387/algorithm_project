#pragma once
#include "BotAlgorithms.h"

class MediumBotPlayer : protected BotAlgorithms, public Player
{
private:
	std::queue<Point> path;
public:
	bool make_path_longer(std::queue<Point> shortest_path, std::queue<Point>& longer_path, std::vector<std::vector<int>> shortest_path_matrix, Labyrinth& labyrinth);
	void bot_medium_mod_algorithm(Labyrinth& labyrinth);
	void move(Labyrinth& labyrinth);
	bool one_member_two_step_cycle(std::queue<Point>& path, int x, int y, std::vector<std::vector<int>> const shortest_path_matrix, Labyrinth& const labyrinth);
	MediumBotPlayer(int x, int y, char sym);
	void bot_medium_algorithm_calc(std::queue<Point>& path, std::vector<std::vector<int>> const shortest_path_matrix, Labyrinth& const labyrinth);
	bool two_step_cycle(std::queue<Point>& path, std::vector<std::vector<int>> const shortest_path_matrix, Labyrinth& const labyrinth);
	bool two_step_cycle_allowed(std::queue<Point> path, std::vector<std::vector<int>> const shortest_path_matrix, Labyrinth& const labyrinth);
	MediumBotPlayer();
	MediumBotPlayer(Point pos, char sym, Labyrinth& labyrinth);
	void start(Labyrinth& labyrinth);
};