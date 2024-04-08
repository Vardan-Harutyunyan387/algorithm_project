#include "MediumBotPlayer.h"
#include "iostream"
MediumBotPlayer::MediumBotPlayer() {}
MediumBotPlayer::MediumBotPlayer(int x, int y, char sym) : Player(x, y, sym) {}
MediumBotPlayer::MediumBotPlayer(Point pos, char sym, Labyrinth& labyrinth) : Player(pos, sym)
{
    this->start(labyrinth);
}


bool MediumBotPlayer::make_path_longer(std::queue<Point> shortest_path, std::queue<Point>& longer_path, std::vector<std::vector<int>> shortest_path_matrix, Labyrinth& labyrinth) {
    int n = shortest_path.size();
    if (n == 1) {
        return false;
    }
    Point last = shortest_path.front(), pre_last;
    shortest_path.pop();
    pre_last = shortest_path.front();
    shortest_path.pop();
    if (labyrinth.fire_matrix[last.y][last.x] >= n + 2 && (((n > 1) && labyrinth.fire_matrix[pre_last.y][pre_last.x] > n + 1)) || n == 1) {
        shortest_path_matrix[last.y][last.x] = n + 2;
        shortest_path_matrix[pre_last.y][pre_last.x] = n + 1;
        /*for (int i = 0; i < shortest_path_matrix.size(); ++i) {
            for (int j = 0; j < shortest_path_matrix.size(); ++j) {
                std::cout << shortest_path_matrix[i][j] << ' ';
            }
            std::cout << '\n';
        }*/
        bool longer_path_exist = bot_shortest_path_algorithm(last, shortest_path_matrix, longer_path, labyrinth);
        return longer_path_exist;
    }
    
    return false;
}


bool MediumBotPlayer::two_step_cycle_allowed(std::queue<Point> path, std::vector<std::vector<int>> const shortest_path_matrix, Labyrinth& const labyrinth) {
    //Check if fire is far to 1 turn from finish posion
    //Only for finish it can be 1 not 2, becouse if the bot reach finish game ends
    if (labyrinth.fire_matrix[path.front().y][path.front().x] - shortest_path_matrix[path.front().y][path.front().x] < 2)
        return false;
    path.pop();
    path.push(position);
    while (!path.empty()) {
        if (labyrinth.fire_matrix[path.front().y][path.front().x] - shortest_path_matrix[path.front().y][path.front().x] <= 2)
            return false;
        path.pop();
    }
    return true;
}

bool MediumBotPlayer::one_member_two_step_cycle(std::queue<Point>& path,int x, int y, std::vector<std::vector<int>> const shortest_path_matrix, Labyrinth& const labyrinth) {
    std::queue<Point> longer_path = path;
    if (labyrinth.is_valid_move(position.x + x, position.y + y) && Point(position.x + x, position.y + y) != path.front()) {
        longer_path.push(position);
        longer_path.push(Point(position.x + x, position.y + y));
        if (two_step_cycle_allowed(longer_path, shortest_path_matrix, labyrinth)) {
            path.push(position);
            path.push(Point(position.x + x, position.y + y));
            return true;
        }
    }
    return false;
}

bool MediumBotPlayer::two_step_cycle(std::queue<Point>& path, std::vector<std::vector<int>> const shortest_path_matrix, Labyrinth& const labyrinth) {
    int n = path.size();
    std::queue<Point> longer_path = path;
    if (n == 1) {
        if (one_member_two_step_cycle(path, 1, 0, shortest_path_matrix, labyrinth))
            return true;
        if (one_member_two_step_cycle(path, -1, 0, shortest_path_matrix, labyrinth))
            return true;
        if (one_member_two_step_cycle(path, 0, 1, shortest_path_matrix, labyrinth))
            return true;
        if (one_member_two_step_cycle(path, 0, -1, shortest_path_matrix, labyrinth))
            return true;
        return false;
    }
    if (!two_step_cycle_allowed(longer_path, shortest_path_matrix, labyrinth)) {
        return false;
    }
    queue_reverse(path);
    Point step_1;
    step_1 = path.front();
    queue_reverse(path);
    path.push(position);
    path.push(step_1);
    return true;
}

void MediumBotPlayer::bot_medium_algorithm_calc(std::queue<Point>& shortest_path, std::vector<std::vector<int>> const shortest_path_matrix, Labyrinth& const labyrinth) {
    std::queue<Point> longer_path;
    bool longer_path_exist = make_path_longer(shortest_path, longer_path, shortest_path_matrix, labyrinth);
    if (longer_path_exist) {
        queue_reverse(longer_path);
        shortest_path = longer_path;
        return;
    }
    else {
        bool two_step_cycle_exist = two_step_cycle(shortest_path, shortest_path_matrix, labyrinth);
        queue_reverse(shortest_path);
        return;
    }
}



void MediumBotPlayer::bot_medium_mod_algorithm(Labyrinth& labyrinth) {

    std::queue<Point> shortest_path_1, shortest_path_2;
    std::vector<std::vector<int>> shortest_path_matrix(labyrinth.get_rows(), std::vector<int>(labyrinth.get_cols(), 1001));
    bot_mod_main_algorithm(shortest_path_matrix, labyrinth, position);

    bool first_path = bot_shortest_path_algorithm(labyrinth.get_finish(1), shortest_path_matrix, shortest_path_1, labyrinth);
    bool second_path = bot_shortest_path_algorithm(labyrinth.get_finish(2), shortest_path_matrix, shortest_path_2, labyrinth);


    if (first_path && shortest_path_2.size() - shortest_path_1.size() == 2) {
        queue_reverse(shortest_path_2);
        path = shortest_path_2;
        return;
    }
    else if (second_path && shortest_path_1.size() - shortest_path_2.size() == 2) {
        queue_reverse(shortest_path_1);
        path = shortest_path_1;
        return;
    }


    // if 1 path doesn't exist make 2 path longer or 1 path is longer than 2 path
    if (!first_path || second_path && shortest_path_2.size() < shortest_path_1.size()) {
        std::cout << shortest_path_2.size();
        bot_medium_algorithm_calc(shortest_path_2, shortest_path_matrix, labyrinth);
        path = shortest_path_2;
        return;
    }
    else {
        bot_medium_algorithm_calc(shortest_path_1, shortest_path_matrix, labyrinth);
        path = shortest_path_1;
        return;
    }
}


void MediumBotPlayer::start(Labyrinth& labyrinth) {
    bot_medium_mod_algorithm(labyrinth);
}

void MediumBotPlayer::move(Labyrinth& labyrinth) {
    if (path.empty())
        return;
    change_position(path.front(), labyrinth);
    path.pop();
}