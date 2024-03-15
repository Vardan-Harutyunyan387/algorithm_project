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
	Point finish_1;
	Point finish_2;
	int rows;
	int cols;
	std::queue<Point> fire_loc;
public:
	Labyrinth();
	bool is_valid_move(int x, int y) const;
	bool is_valid_move(Point p) const;
	bool add_fire(int x, int y);
	void fire_expand();
	const std::vector<std::string>& get_labyrinth() const;

};

