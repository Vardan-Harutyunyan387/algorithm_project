#include "BotAlgorithms.h"


// This function add to the our fire queue a position if it exsist
void BotAlgorithms::queue_pusher(std::queue<int>& value_queue, std::queue<Point>& path_queue, Point pos, int x, int y, int val, Labyrinth& labyrinth) {
    if (labyrinth.is_valid_move(pos.x + x, pos.y + y)) {
        value_queue.push(val + 1);
        path_queue.push({ pos.x + x, pos.y + y });
    }
}


void BotAlgorithms::queue_pusher(std::queue<Point>& path_queue, Point pos, int x, int y, Labyrinth& labyrinth) {
    if (labyrinth.is_valid_move(pos.x + x, pos.y + y)) {
        path_queue.push({ pos.x + x, pos.y + y });
    }
}


// do queue_pusher function to all positions
void BotAlgorithms::queue_pusher_all_positions(std::queue<int>& value_queue, std::queue<Point>& path_queue, Point pos, int val, Labyrinth& labyrinth) {
    queue_pusher(value_queue, path_queue, pos, 1, 0, val, labyrinth);// (x + 1, y)
    queue_pusher(value_queue, path_queue, pos, -1, 0, val, labyrinth);// (x - 1, y)
    queue_pusher(value_queue, path_queue, pos, 0, -1, val, labyrinth);// (x, y - 1)
    queue_pusher(value_queue, path_queue, pos, 0, 1, val, labyrinth);// (x, y + 1)
}

void BotAlgorithms::queue_pusher_all_positions(std::queue<Point>& path_queue, Point pos, Labyrinth& labyrinth) {
    queue_pusher(path_queue, pos, 1, 0, labyrinth); // (x + 1, y)
    queue_pusher(path_queue, pos, -1, 0, labyrinth);// (x - 1, y)
    queue_pusher(path_queue, pos, 0, -1, labyrinth);// (x, y - 1)
    queue_pusher(path_queue, pos, 0, 1, labyrinth);// (x, y + 1)
}


void BotAlgorithms::queue_reverse(std::queue<Point>& q) {
    int len = q.size();
    std::vector<Point> v;
    while (len--) {
        v.push_back(q.front());
        q.pop();
    }
    for (int i = v.size() - 1; i > -1; --i)
        q.push(v[i]);
}


// fill shortest_path_matrix with shortest path to the positions
void BotAlgorithms::bot_mod_main_algorithm(std::vector<std::vector<int>>& shortest_path_matrix, Labyrinth& labyrinth, Point& position) {
    std::queue<Point> path_queue;
    std::queue<Point> new_path_queue;
    int value = 0;
    path_queue.push(position);
    while (!path_queue.empty()) {
        while (!path_queue.empty()) {
            Point current = path_queue.front();
            if (labyrinth.is_valid_move(current) && (labyrinth.fire_matrix[current.y][current.x] > value || labyrinth.fire_matrix[current.y][current.x] == value && (current == labyrinth.get_finish(1) || current == labyrinth.get_finish(2))) && shortest_path_matrix[current.y][current.x] > value) {
                shortest_path_matrix[current.y][current.x] = value;
                queue_pusher_all_positions(new_path_queue, current, labyrinth);
            }
            path_queue.pop();
        }
        path_queue = new_path_queue;
        new_path_queue = std::queue<Point>();
        ++value;
    }
}


//This function finds shortest path by moving from our position to it's smaller neigbour
//In main algorithm we give to our shortest_path_matrix the values of path and this algorithm is coming back to our start position from finish position
bool BotAlgorithms::bot_shortest_path_algorithm(Point current, std::vector<std::vector<int>> shortest_path_matrix, std::queue<Point>& shortest_path, Labyrinth& labyrinth) {
    if (!labyrinth.is_valid_move(current) || shortest_path_matrix[current.y][current.x] == 1001)
        return false;
    if (shortest_path_matrix[current.y][current.x] == 0)
        return true;
    shortest_path.push(current);
    Point change_checker = current;
    if (bot_shorter_path_checker(current, 1, 0, shortest_path_matrix, labyrinth)) {
        current.x++;
    }
    else if (bot_shorter_path_checker(current, -1, 0, shortest_path_matrix, labyrinth)) {
        current.x--;
    }
    else if (bot_shorter_path_checker(current, 0, 1, shortest_path_matrix, labyrinth)) {
        current.y++;
    }
    else if (bot_shorter_path_checker(current, 0, -1, shortest_path_matrix, labyrinth)) {
        current.y--;
    }
    if (change_checker == current)
        return false;
    return bot_shortest_path_algorithm(current, shortest_path_matrix, shortest_path, labyrinth);

}


bool BotAlgorithms::bot_shorter_path_checker(Point current, int x, int y, std::vector<std::vector<int>> shortest_path_matrix, Labyrinth& labyrinth) {
    return (labyrinth.is_valid_move(current.x + x, current.y + y) && shortest_path_matrix[current.y][current.x] - shortest_path_matrix[current.y + y][current.x + x] == 1);
}
