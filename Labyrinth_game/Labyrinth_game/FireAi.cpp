#include "FireAi.h"


// Do bfs for 1 fire in matrix
void FireAi::fire_matrix_calc_algorithm(Labyrinth& labyrinth) {
    std::queue<Point> fire_queue;
    fire_queue.push(position);
    std::queue<int> fire_path_queue;
    for (int i = 0; i < fire_queue.size(); ++i)
        fire_path_queue.push(0);
    while (!fire_queue.empty()) {
        Point current = fire_queue.front();
        int current_path = fire_path_queue.front();
        if (labyrinth.is_valid_move(current) && labyrinth.fire_matrix[current.y][current.x] > current_path) {
            labyrinth.fire_matrix[current.y][current.x] = current_path;
            queue_pusher_all_positions(fire_path_queue, fire_queue, current, current_path, labyrinth);
        }
        fire_queue.pop();
        fire_path_queue.pop();
    }
}

FireAi::FireAi() {}
FireAi::FireAi(int x, int y, char sym) : Player(x, y, sym) {}
FireAi::FireAi(Point pos, char sym) : Player(pos, sym) {}