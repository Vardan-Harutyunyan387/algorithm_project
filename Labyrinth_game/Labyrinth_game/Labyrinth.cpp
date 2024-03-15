#include <iostream>
#include "Labyrinth.h"


Labyrinth::Labyrinth()
{
	labyrinth = {
        "########.#",
        "..##...#.#",
        "#.##.#.#.#",
        "#.##.#.#.#",
        "#....#.#.#",
        "######.#.#",
        "#........#",
        "#.########",
        "#........#",
        "##########"
    };
    finish_1 = Point(0, 8);
    finish_2 = Point(1, 0);
    rows = 10;
    cols = 10;
}

bool Labyrinth::is_valid_move(int x, int y) const
{
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        return false;  // Out of bounds
    return labyrinth[x][y] != '#';  // Not a wall
}

bool Labyrinth::is_valid_move(Point p) const
{
    if (p.x < 0 || p.x >= rows || p.y < 0 || p.y >= cols)
        return false;  // Out of bounds
    return labyrinth[p.x][p.y] != '#';  // Not a wall
}

bool Labyrinth::add_fire(int x, int y)
{
    if (is_valid_move(x, y))
    {
        labyrinth[x][y] = 'f';
        fire_loc.push(Point(x, y));
        return true;
    }
    return false;
}

void Labyrinth::fire_expand()
{
    int len = fire_loc.size();
    Point p;
    for (int i = 0; i < len; i++)
    {
        p = fire_loc.front();
        fire_loc.pop();

        if (is_valid_move(p.x + 1, p.y))
        {
            labyrinth[p.x + 1][p.y] = 'f';
            fire_loc.push(Point(p.x + 1, p.y));
        }
        if (is_valid_move(p.x - 1, p.y))
        {
            labyrinth[p.x - 1][p.y] = 'f';
            fire_loc.push(Point(p.x - 1, p.y));
        }
        if (is_valid_move(p.x, p.y + 1))
        {
            labyrinth[p.x][p.y + 1] = 'f';
            fire_loc.push(Point(p.x, p.y + 1));
        }
        if (is_valid_move(p.x, p.y - 1))
        {
            labyrinth[p.x][p.y - 1] = 'f';
            fire_loc.push(Point(p.x, p.y - 1));
        }
    }
}

const std::vector<std::string>& Labyrinth::get_labyrinth() const
{
    return labyrinth;
}
