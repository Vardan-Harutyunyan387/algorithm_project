#include <iostream>
#include <cstdlib> 
#include <fstream>
#include "Labyrinth.h"
#include "FireAi.h"

Labyrinth::Labyrinth()
{
	labyrinth = {
        "########.#",
        "..##...#.#",
        "#.##O#.#.#",
        "#.##.#.#.#",
        "#....#.#.#",
        "######.#.#",
        "#....o...#",
        "#@########",
        "#......@.#",
        "##########"
    };
    finish_1 = Point(-1, -1);
    finish_2 = Point(-1, -1);
    rows = 10;
    cols = 10;
    fire_matrix = std::vector<std::vector<int>>(rows, std::vector<int> (cols, 1001));
}

Labyrinth::Labyrinth(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        labyrinth.push_back(line);
    }
    file.close();

    finish_1 = Point(-1, -1);
    finish_2 = Point(-1, -1);
    rows = 20;
    cols = 20;
    fire_matrix = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 1001));

}

Point Labyrinth::get_finish(int n) {
    if (n == 1)
        return finish_1;
    if (n == 2)
        return finish_2;
    return Point(-1, -1);
}
int Labyrinth::get_rows() {
    return rows;
}
int Labyrinth::get_cols() {
    return cols;
}

bool Labyrinth::is_valid_move(int x, int y) const
{
    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return false;  // Out of bounds
    return labyrinth[y][x] != WALL;  // Not a wall
}

bool Labyrinth::is_valid_move(Point p) const
{
    if (p.x < 0 || p.x >= cols || p.y < 0 || p.y >= rows)
        return false;  // Out of bounds
    return labyrinth[p.y][p.x] != WALL;  // Not a wall
}
void Labyrinth::set_finish(int n, Point pos) {
    if (n == 1) {
        finish_1 = pos;
    }
    else if (n == 2) {
        finish_2 = pos;
    }

}


const std::vector<std::string>& Labyrinth::get_labyrinth() const
{
    return labyrinth;
}

bool Labyrinth::is_finish(Point p)
{
    if (p == finish_1 || p == finish_2)
    {
        return true;
    }
    return false;
}

bool Labyrinth::is_fire(Point p)
{
    return labyrinth[p.y][p.x] == FIRE;
}

bool Labyrinth::is_fire_next_turn(Point p)
{
    return labyrinth[p.y + 1][p.x + 1] == FIRE || labyrinth[p.y + 1][p.x] == FIRE || labyrinth[p.y + 1][p.x - 1] == FIRE ||
        labyrinth[p.y][p.x + 1] == FIRE || labyrinth[p.y][p.x - 1] == FIRE || labyrinth[p.y - 1][p.x + 1] == FIRE || labyrinth[p.y - 1][p.x] == FIRE ||
        labyrinth[p.y - 1][p.x - 1] == FIRE;
}
