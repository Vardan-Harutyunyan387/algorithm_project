#include "MediumBotPlayer.h"
#include "iostream"
MediumBotPlayer::MediumBotPlayer() {}
MediumBotPlayer::MediumBotPlayer(int x, int y, char sym) : Player(x, y, sym) {}
MediumBotPlayer::MediumBotPlayer(Point pos, char sym, Labyrinth& labyrinth) : Player(pos, sym)
{
    this->start(labyrinth);
}
void MediumBotPlayer::bot_medium_mod_algorithm(Labyrinth& labyrinth) {

    std::queue<Point> shortest_path_1, shortest_path_2, longer_path;
    std::vector<std::vector<int>> shortest_path_matrix(labyrinth.get_rows(), std::vector<int>(labyrinth.get_cols(), 1001));
    bot_mod_main_algorithm(shortest_path_matrix, labyrinth, position);

    bool first_path = bot_shortest_path_algorithm(labyrinth.get_finish(1), shortest_path_matrix, shortest_path_1, labyrinth);
    bool second_path = bot_shortest_path_algorithm(labyrinth.get_finish(2), shortest_path_matrix, shortest_path_2, labyrinth);

    //queue_reverse(shortest_path_1);
    //queue_reverse(shortest_path_2);
    //check wich path is shortest for our 2 finishes
    if (!first_path) {
        int n = shortest_path_2.size();
        Point last = shortest_path_2.front();
        shortest_path_2.pop();
        Point pre_last = shortest_path_2.front();
        shortest_path_2.pop();
        if (labyrinth.fire_matrix[last.y][last.x] >= n + 2 && labyrinth.fire_matrix[pre_last.y][pre_last.x] > n + 1) {
            shortest_path_matrix[last.y][last.x] = n + 2;
            shortest_path_matrix[pre_last.y][pre_last.x] = n + 1;
            bool longer_path_exist = bot_shortest_path_algorithm(labyrinth.get_finish(2), shortest_path_matrix, longer_path, labyrinth);
            if (longer_path_exist) {
                queue_reverse(longer_path);
                path = longer_path;
                while (!longer_path.empty()) {
                    std::cout << longer_path.front().x << " " << longer_path.front().y;
                    longer_path.pop();
                }
                return;
            }
            else {
                //go AND COME Back
            }
        }
        else {
            //go AND COME Back
        }
    }
    else if (!second_path) {
        int n = shortest_path_1.size();
        Point last = shortest_path_1.front();
        shortest_path_1.pop();
        Point pre_last = shortest_path_1.front();
        shortest_path_1.pop();
        if (labyrinth.fire_matrix[last.y][last.x] >= n + 2 && labyrinth.fire_matrix[pre_last.y][pre_last.x] > n + 1) {
            shortest_path_matrix[last.y][last.x] = n + 2;
            shortest_path_matrix[pre_last.y][pre_last.x] = n + 1;
            bool longer_path_exist = bot_shortest_path_algorithm(labyrinth.get_finish(1), shortest_path_matrix, longer_path, labyrinth);
            if (longer_path_exist) {
                queue_reverse(longer_path);
                path = longer_path;
                while (!longer_path.empty()) {
                    std::cout << longer_path.front().x << " " << longer_path.front().y;
                    longer_path.pop();
                }
                return;
            }
            else {
                //go AND COME Back
            }
        }
        else {
            //go AND COME Back
        }
    }

    if (shortest_path_2.size() - shortest_path_1.size() == 2) {
        path = shortest_path_2;
        return;
    }
    else if (shortest_path_1.size() - shortest_path_2.size() == 2) {
        path = shortest_path_1;
        return;
    }
    if (shortest_path_2.size() > shortest_path_1.size()) {

        path = shortest_path_1;
        return;
    }
    else {

        path = shortest_path_2;
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