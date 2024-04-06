#pragma once
#include <vector>
#include <string>
#include <queue>
#include "Point.h"


//#include "HumanPlayer.h"

class Labyrinth
{
private:
	Point finish_1;
	Point finish_2;
	Point bot_position;
	std::queue<Point> bot_path;
	int rows;
	
	bool bot_shorter_path_checker(Point current, int x, int y, std::vector<std::vector<int>> shortest_path_matrix);
	int cols;
	bool check_if_win(Point p);
	bool add_two_path_all_positions(std::queue<Point> path, Point finish);
	bool bot_shortest_path_algorithm(Point current, std::vector<std::vector<int>> shortest_path_matrix, std::queue<Point>& shortest_path);
public:

	Point get_finish(int n);
	void set_finish(int n, Point pos);
	int get_rows();
	int get_cols();
	std::vector<std::vector<int>> fire_matrix;
	char WALL = '#';
	char SPACE = '.';
	char FIRE = '@';
	char BOT = 'o';
	char PLAYER = 'O';
	std::vector<std::string> labyrinth;
	void bot_mod_main_algorithm(std::vector<std::vector<int>>& shortest_path_matrix);
	Labyrinth();
	void bot_hard_mod_algorithm();
	void bot_medium_mod_algorithm();
	bool add_two_path(std::queue<Point> path, int x, int y, Point finish);
	bool is_valid_move(int x, int y) const;
	bool is_valid_move(Point p) const;
	void change_bot_position(Point pos);
	const std::vector<std::string>& get_labyrinth() const;
	bool is_finish(Point p);
	bool is_fire(Point p);

};

