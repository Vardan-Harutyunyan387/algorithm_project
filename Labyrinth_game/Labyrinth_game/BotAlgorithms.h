#pragma once
#include "Player.h"

class BotAlgorithms
{
protected:
	void queue_reverse(std::queue<Point>& q);
	void queue_pusher_all_positions(std::queue<Point>& path_queue, Point pos, Labyrinth& labyrinth);
	void queue_pusher_all_positions(std::queue<int>& value_queue, std::queue<Point>& path_queue, Point pos, int val, Labyrinth& labyrinth);
	void queue_pusher(std::queue<Point>& path_queue, Point pos, int x, int y, Labyrinth& labyrinth);
	void queue_pusher(std::queue<int>& value_queue, std::queue<Point>& path_queue, Point pos, int x, int y, int val, Labyrinth& labyrinth);
	void bot_mod_main_algorithm(std::vector<std::vector<int>>& shortest_path_matrix, Labyrinth& labyrinth, Point& position);
	bool bot_shortest_path_algorithm(Point current, std::vector<std::vector<int>> shortest_path_matrix, std::queue<Point>& shortest_path, Labyrinth& labyrinth);
	bool bot_shorter_path_checker(Point current, int x, int y, std::vector<std::vector<int>> shortest_path_matrix, Labyrinth& labyrinth);

	
};

