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
/*
//This function add to the our fire queue a position if it exsist
void Labyrinth::queue_pusher(std::queue<int>& value_queue, std::queue<Point>& path_queue, Point pos, int x, int y, int val) {
    if (is_valid_move(pos.x + x, pos.y + y)) {
        value_queue.push(val + 1);
        path_queue.push({ pos.x + x, pos.y + y });
    }
}


void Labyrinth::queue_pusher(std::queue<Point>& path_queue, Point pos, int x, int y) {
    if (is_valid_move(pos.x + x, pos.y + y)) {
        path_queue.push({ pos.x + x, pos.y + y });
    }
}


// do queue_pusher function to all positions
void Labyrinth::queue_pusher_all_positions(std::queue<int>& value_queue, std::queue<Point>& path_queue, Point pos, int val) {
    queue_pusher(value_queue, path_queue, pos, 1, 0, val);// (x + 1, y)
    queue_pusher(value_queue, path_queue, pos, -1, 0, val);// (x - 1, y)
    queue_pusher(value_queue, path_queue, pos, 0, -1, val);// (x, y - 1)
    queue_pusher(value_queue, path_queue, pos, 0, 1, val);// (x, y + 1)
}

void Labyrinth::queue_pusher_all_positions(std::queue<Point>& path_queue, Point pos) {
    queue_pusher(path_queue, pos, 1, 0); // (x + 1, y)
    queue_pusher(path_queue, pos, -1, 0);// (x - 1, y)
    queue_pusher(path_queue, pos, 0, -1);// (x, y - 1)
    queue_pusher(path_queue, pos, 0, 1);// (x, y + 1)
}
*/
//Calculates the shortest path of fire and put it in fire_matrix 


//Checks if the neigbour position is smaller than current
//bool Labyrinth::bot_shorter_path_checker(Point current, int x, int y, std::vector<std::vector<int>> shortest_path_matrix) {
//    return (is_valid_move(current.x + x, current.y + y) && shortest_path_matrix[current.y + y][current.x + x] < shortest_path_matrix[current.y][current.x]);
//}

//This function finds shortest path by moving from our position to it's smaller neigbour
//In main algorithm we give to our shortest_path_matrix the values of path and this algorithm is coming back to our start position from finish position
//bool Labyrinth::bot_shortest_path_algorithm(Point current,std::vector<std::vector<int>> shortest_path_matrix, std::queue<Point>& shortest_path) {
//    if (!is_valid_move(current) || shortest_path_matrix[current.y][current.x] == 1001)
//        return false;
//    if (shortest_path_matrix[current.y][current.x] == 0)
//        return true;
//    shortest_path.push(current);
//    if (bot_shorter_path_checker(current, 1 , 0, shortest_path_matrix)) {
//        current.x++;
//    }
//    else if (bot_shorter_path_checker(current, -1, 0, shortest_path_matrix)) {
//        current.x--;
//    } 
//    else if (bot_shorter_path_checker(current, 0, 1, shortest_path_matrix)) {
//        current.y++;
//    }
//    else if (bot_shorter_path_checker(current, 0, -1, shortest_path_matrix)) {
//        current.y--;
//    }
//    return bot_shortest_path_algorithm(current, shortest_path_matrix, shortest_path);
//
//}


/*
//Returns the shortest path for bot in vector using bfs(wave algorithm )
void Labyrinth::bot_mod_main_algorithm(std::vector<std::vector<int>>& shortest_path_matrix) {
    std::queue<Point> path_queue;
    std::queue<Point> new_path_queue;
    int value = 0;
    path_queue.push(bot_position);
    while (!path_queue.empty()) {
        while (!path_queue.empty()) {
            Point current = path_queue.front();
            if (is_valid_move(current) && fire_matrix[current.y][current.x] > value && shortest_path_matrix[current.y][current.x] > value) {
                shortest_path_matrix[current.y][current.x] = value;
                queue_pusher_all_positions(new_path_queue, current);
            }
            path_queue.pop();
        }
        path_queue = new_path_queue;
        new_path_queue = std::queue<Point>();
        ++value;
    }
}

void Labyrinth::bot_hard_mod_algorithm() {
    std::queue<Point> shortest_path_1, shortest_path_2;
    std::vector<std::vector<int>> shortest_path_matrix(rows, std::vector<int>(cols, 1001));
    bot_mod_main_algorithm(shortest_path_matrix);

    bool first_path = bot_shortest_path_algorithm(finish_1, shortest_path_matrix, shortest_path_1);
    bool second_path = bot_shortest_path_algorithm(finish_2, shortest_path_matrix, shortest_path_2);
    queue_reverse(shortest_path_2);
    queue_reverse(shortest_path_1);

    //check wich path is shortest for our 2 finishes
    if (!second_path || shortest_path_2.size() > shortest_path_1.size()) {
        bot_path = shortest_path_1;
        return;
    }
    bot_path = shortest_path_2;
}


bool Labyrinth::add_two_path(std::queue<Point> path, int x, int y, Point finish) {
    std::queue<Point> shortest_path;
    Point original_pos = bot_position;
    if (is_valid_move(bot_position.x + x, bot_position.y + y) && fire_matrix[bot_position.y + y][bot_position.x + x] != 1 && (path.front() != Point(bot_position.x + x, bot_position.y + y) || (path.front() == Point(bot_position.x + x, bot_position.y + y) && fire_matrix[bot_position.y][bot_position.x] == 1))) {
        bot_position.x += x;
        bot_position.y += y;
        std::vector<std::vector<int>> path_matrix(rows, std::vector<int>(cols, 1001));
        bot_mod_main_algorithm(path_matrix);
        bool third_path = bot_shortest_path_algorithm(finish, path_matrix, shortest_path);
        shortest_path.push(Point(bot_position.x, bot_position.y));
        if (third_path && path.size() - shortest_path.size() == 2) {
            queue_reverse(path);
            bot_path = shortest_path;
            bot_position = original_pos;
            return true;
        }
    }
    bot_position = original_pos;
    return false;
}
bool Labyrinth::add_two_path_all_positions(std::queue<Point> path, Point finish) {
    if (add_two_path(path, 1, 0, finish) || add_two_path(path, -1, 0, finish) || add_two_path(path, 0, 1, finish) || add_two_path(path, 0, 1, finish))
        return true;
    return false;
}
void Labyrinth::bot_medium_mod_algorithm() {

    std::queue<Point> shortest_path_1, shortest_path_2, shortest_path_3;
    std::vector<std::vector<int>> shortest_path_matrix(rows, std::vector<int>(cols, 1001));
    bot_mod_main_algorithm(shortest_path_matrix);

    bool first_path = bot_shortest_path_algorithm(finish_1, shortest_path_matrix, shortest_path_1);
    bool second_path = bot_shortest_path_algorithm(finish_2, shortest_path_matrix, shortest_path_2);

    queue_reverse(shortest_path_1);
    queue_reverse(shortest_path_2);

    //check wich path is shortest for our 2 finishes
    if (!first_path) {
        if (add_two_path_all_positions(shortest_path_2, finish_2)) {
            return;
        }
        bot_path = shortest_path_2;
        return;
    }
    else if (!second_path) {
        if (add_two_path_all_positions(shortest_path_1, finish_1)) {
            return;
        }
        bot_path = shortest_path_1;
        return;
    }

    if (shortest_path_2.size() - shortest_path_1.size() == 2) {
        bot_path = shortest_path_2;
        return;
    }
    else if (shortest_path_1.size() - shortest_path_2.size() == 2) {
        bot_path = shortest_path_1;
        return;
    }
    if (shortest_path_2.size() > shortest_path_1.size()) {
        if (add_two_path_all_positions(shortest_path_1, finish_1)) {
            return;
        }
        bot_path = shortest_path_1;
        return;
    }
    else {
        if (add_two_path_all_positions(shortest_path_2, finish_2)) {
            return;
        }
        bot_path = shortest_path_2;
        return;
    }
}*/




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
