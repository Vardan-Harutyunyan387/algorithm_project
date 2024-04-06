//#include "MediumBotPlayer.h"
//
//void MediumBotPlayer::bot_medium_mod_algorithm(Labyrinth& labyrinth) {
//
//    std::queue<Point> shortest_path_1, shortest_path_2, shortest_path_3;
//    std::vector<std::vector<int>> shortest_path_matrix(labyrinth.get_rows(), std::vector<int>(labyrinth.get_cols(), 1001));
//    bot_mod_main_algorithm(shortest_path_matrix, labyrinth, position);
//
//    bool first_path = bot_shortest_path_algorithm(labyrinth.get_finish(1), shortest_path_matrix, shortest_path_1, labyrinth);
//    bool second_path = bot_shortest_path_algorithm(labyrinth.get_finish(2), shortest_path_matrix, shortest_path_2, labyrinth);
//
//    queue_reverse(shortest_path_1);
//    queue_reverse(shortest_path_2);
//
//    //check wich path is shortest for our 2 finishes
//    if (!first_path) {
//        if (add_two_path_all_positions(shortest_path_2, finish_2)) {
//            return;
//        }
//        path = shortest_path_2;
//        return;
//    }
//    else if (!second_path) {
//        if (add_two_path_all_positions(shortest_path_1, finish_1)) {
//            return;
//        }
//        path = shortest_path_1;
//        return;
//    }
//
//    if (shortest_path_2.size() - shortest_path_1.size() == 2) {
//        path = shortest_path_2;
//        return;
//    }
//    else if (shortest_path_1.size() - shortest_path_2.size() == 2) {
//        path = shortest_path_1;
//        return;
//    }
//    if (shortest_path_2.size() > shortest_path_1.size()) {
//        if (add_two_path_all_positions(shortest_path_1, finish_1)) {
//            return;
//        }
//        path = shortest_path_1;
//        return;
//    }
//    else {
//        if (add_two_path_all_positions(shortest_path_2, finish_2)) {
//            return;
//        }
//        bot_path = shortest_path_2;
//        return;
//    }