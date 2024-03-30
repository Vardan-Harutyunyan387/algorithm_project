#pragma once
#include <vector>
#include <string>
#include <queue>
#include "Point.h"

//#include "HumanPlayer.h"

class Labyrinth
{
private:
	std::vector<std::string> labyrinth;
	std::vector<std::vector<int>> fire_matrix;
	Point finish_1;
	Point finish_2;
	Point bot_position;
	char WALL = '#';
	char SPACE = '.';
	char FIRE = '@';
	char BOT = 'o';
	char PLAYER = 'O';
	std::queue<Point> bot_path;
	int rows;
	
	bool bot_shorter_path_checker(Point current, int x, int y, std::vector<std::vector<int>> shortest_path_matrix);
	int cols;
	void rookie_algorithm();
	void easy_algorithm();
	void fire_expanding(Point pos, int x, int y);
	bool check_if_win(Point p);
	bool add_two_path_all_positions(std::queue<Point> path, Point finish);
	bool bot_shortest_path_algorithm(Point current, std::vector<std::vector<int>> shortest_path_matrix, std::queue<Point>& shortest_path);
	std::queue<Point> fire_loc;
public:
	void bot_mod_main_algorithm(std::vector<std::vector<int>>& shortest_path_matrix);
	Labyrinth();
	void bot_rand_moving(bool avoid_fire);
	void difficulty_algorithm(int difficulty);
	void bot_moving();
	void bot_hard_mod_algorithm();
	void bot_medium_mod_algorithm();
	bool add_two_path(std::queue<Point> path, int x, int y, Point finish);
	void queue_reverse(std::queue<Point>& q);
	bool is_valid_move(int x, int y) const;
	bool is_valid_move(Point p) const;
	bool add_fire(int x, int y);
	void fire_expand();
	void fire_matrix_calc();
	void change_bot_position(Point pos);
	void queue_pusher(std::queue<Point>& path_queue, Point pos, int x, int y);
	void queue_pusher(std::queue<int>& path_value_queue, std::queue<Point>& path_queue, Point pos, int x, int y, int val);
	void queue_pusher_all_positions(std::queue<int>& path_value_queue, std::queue<Point>& path_queue, Point pos, int val);
	void queue_pusher_all_positions(std::queue<Point>& path_queue, Point pos);
	const std::vector<std::string>& get_labyrinth() const;
	bool is_finish(Point p);
	bool is_fire(Point p);

};

