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
	int rows;
	int cols;

public:
	Labyrinth();
	Labyrinth(const std::string& filename);
	Point get_finish(int n);
	void set_finish(int n, Point pos);

	int get_rows();
	int get_cols();

	std::vector<std::vector<int>> fire_matrix;

	char WALL = '#';
	char SPACE = '.';
	char FIRE = 'F';

	std::vector<std::string> labyrinth;

	//bool add_two_path(std::queue<Point> path, int x, int y, Point finish);
	bool is_valid_move(int x, int y) const;
	bool is_valid_move(Point p) const;

	const std::vector<std::string>& get_labyrinth() const;

	bool is_finish(Point p);
	bool is_fire(Point p);
	bool is_fire_next_turn(Point p);

};

