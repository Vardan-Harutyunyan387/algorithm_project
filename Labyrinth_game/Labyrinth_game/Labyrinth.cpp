#include <iostream>
#include <cstdlib> 
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
    finish_1 = Point(8, 0);
    finish_2 = Point(0, 1);
    rows = 10;
    cols = 10;
    bot_position = Point(4, 6);
    fire_matrix = std::vector<std::vector<int>>(rows, std::vector<int> (cols, 1001));
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

bool Labyrinth::add_fire(int x, int y)
{
    if (!is_valid_move(x, y))
    {
        return false;
    }
    labyrinth[y][x] = FIRE;
    fire_loc.push(Point(x, y));
    return true;
    
}

void Labyrinth::change_bot_position(Point pos) {
    if (!is_valid_move(pos)) {
        return;
    }
    labyrinth[bot_position.y][bot_position.x] = SPACE;
    labyrinth[pos.y][pos.x] = BOT;
    bot_position = pos;
}

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

//Calculates the shortest path of fire and put it in fire_matrix 
void Labyrinth::fire_matrix_calc() {
    std::queue<Point> fire_queue = fire_loc;
    std::queue<int> fire_path_queue;
    for (int i = 0; i < fire_queue.size(); ++i)
        fire_path_queue.push(0);
    while (!fire_queue.empty()) {
        Point current = fire_queue.front();
        int current_path = fire_path_queue.front();
        if (is_valid_move(current) && fire_matrix[current.y][current.x] > current_path) {
            fire_matrix[current.y][current.x] = current_path;
            queue_pusher_all_positions(fire_path_queue, fire_queue, current, current_path);
        }
        fire_queue.pop();
        fire_path_queue.pop();
    }
    
}

//Checks if the neigbour position is smaller than current
bool Labyrinth::bot_shorter_path_checker(Point current, int x, int y, std::vector<std::vector<int>> shortest_path_matrix) {
    return (is_valid_move(current.x + x, current.y + y) && shortest_path_matrix[current.y + y][current.x + x] < shortest_path_matrix[current.y][current.x]);
}

//This function finds shortest path by moving from our position to it's smaller neigbour
//In main algorithm we give to our shortest_path_matrix the values of path and this algorithm is coming back to our start position from finish position
bool Labyrinth::bot_shortest_path_algorithm(Point current,std::vector<std::vector<int>> shortest_path_matrix, std::queue<Point>& shortest_path) {
    if (!is_valid_move(current) || shortest_path_matrix[current.y][current.x] == 1001)
        return false;
    if (shortest_path_matrix[current.y][current.x] == 0)
        return true;
    shortest_path.push(current);
    if (bot_shorter_path_checker(current, 1 , 0, shortest_path_matrix)) {
        current.x++;
    }
    else if (bot_shorter_path_checker(current, -1, 0, shortest_path_matrix)) {
        current.x--;
    } 
    else if (bot_shorter_path_checker(current, 0, 1, shortest_path_matrix)) {
        current.y++;
    }
    else if (bot_shorter_path_checker(current, 0, -1, shortest_path_matrix)) {
        current.y--;
    }
    return bot_shortest_path_algorithm(current, shortest_path_matrix, shortest_path);

}



/*

Qnnarkel Vardani het

*/


void Labyrinth::queue_reverse(std::queue<Point>& q) {
    int len = q.size();
    std::vector<Point> v;
    while (len--) {
        v.push_back(q.front());
        q.pop();
    }
    for (int i = v.size() - 1; i > -1; --i)
        q.push(v[i]);
}

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
}

//Moving fire if posible
void Labyrinth::fire_expanding(Point pos, int x, int y) {
    if (is_valid_move(pos.x + x, pos.y + y)) {
        labyrinth[pos.y + y][pos.x + x] = FIRE;
        fire_loc.push(Point(pos.x + x, pos.y + y));
    }
}

void Labyrinth::difficulty_algorithm(int difficulty) {
    fire_matrix_calc();
    if (difficulty == 4) {
        bot_hard_mod_algorithm();
        return;
    }
    else if (difficulty == 3) {
        
    }
}


// Fire expanding function
void Labyrinth::fire_expand()
{
    int len = fire_loc.size();
    Point p;
    for (int i = 0; i < len; i++)
    {
        p = fire_loc.front();
        fire_loc.pop();
        fire_expanding(p, 1, 0);
        fire_expanding(p, -1, 0);
        fire_expanding(p, 0, 1);
        fire_expanding(p, 0, -1);
    }
}

void Labyrinth::bot_moving() {
    if (bot_path.empty())
        return;
    change_bot_position(bot_path.front());
    bot_path.pop();
}


//Doing random move 
//Is used in easy and rookie difficulties
void Labyrinth::bot_rand_moving(bool avoid_fire) {
    srand((unsigned)time(NULL));
    int x, y;
    while (true) {
        x = (rand() % 3) - 1;
        y = (rand() % 3) - 1;
        if (!is_valid_move(bot_position.x + x, bot_position.y + y) || (avoid_fire && labyrinth[bot_position.y + y][x + bot_position.x + x] == FIRE)) {
            continue;
        }
        break;
    }
    change_bot_position(Point(bot_position.x + x, bot_position.y + y));
}


const std::vector<std::string>& Labyrinth::get_labyrinth() const
{
    return labyrinth;
}
