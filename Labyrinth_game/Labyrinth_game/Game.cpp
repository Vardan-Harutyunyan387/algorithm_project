#include "Game.h"
#include <iostream>
#include <cctype>
#include <windows.h>

Game::Game(Labyrinth& _labyrinth, HumanPlayer _player):labyrinth(_labyrinth), player(_player)
{
}
Game::Game(Labyrinth& _labyrinth) : labyrinth(_labyrinth)
{
}

void Game::difficulty_input() {
    std::cout << "Please choose the difficluty Number:\n"
        << "1. Rookie \n" 
        << "2. Easy\n" 
        << "3. Medium\n"
        << "4. Hard\n";
    std::cin >> difficulty;
    while (difficulty > 4 || difficulty < 0) {
        std::cout << "Wrong number. Please choose difficluty number again from 1 to 4\n";
        std::cin >> difficulty;
    }
}


char Game::getKeyPress()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwMode = 0;
    INPUT_RECORD irInBuf[128];
    DWORD cNumRead = 0;

    // Get the current input mode
    GetConsoleMode(hStdin, &fdwMode);

    // Disable line input and echo input
    SetConsoleMode(hStdin, fdwMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    while (true) {
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            std::cerr << "Error reading input." << std::endl;
            return 0;
        }

        // Process the input events
        for (DWORD i = 0; i < cNumRead; ++i) {
            if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
                // Process the key events
                char key = irInBuf[i].Event.KeyEvent.uChar.AsciiChar;
                return key;
            }
        }
    }
}

// finds finish 1 and finish 2, searching in borders 
void Game::find_exites() {
    for (int i = 0; i < labyrinth.get_cols(); ++i) {
        if (labyrinth.is_valid_move(i, 0) && !labyrinth.is_valid_move(labyrinth.get_finish(1)) && labyrinth.labyrinth[0][i] == labyrinth.SPACE) {
            labyrinth.set_finish(1, Point(i, 0));
        }
        else if (labyrinth.is_valid_move(i, 0) && !labyrinth.is_valid_move(labyrinth.get_finish(2)) && labyrinth.labyrinth[0][i] == labyrinth.SPACE) {
            labyrinth.set_finish(2, Point(i, 0));
        }
    }

    for (int i = 0; i < labyrinth.get_rows(); ++i) {
        if (labyrinth.is_valid_move(0, i) && !labyrinth.is_valid_move(labyrinth.get_finish(1)) && labyrinth.labyrinth[i][0] == labyrinth.SPACE) {
            labyrinth.set_finish(1, Point(0, i));
        }
        else if (labyrinth.is_valid_move(0, i) && !labyrinth.is_valid_move(labyrinth.get_finish(2)) && labyrinth.labyrinth[i][0] == labyrinth.SPACE) {
            labyrinth.set_finish(2, Point(0, i));
        }
    }

    for (int i = 0; i < labyrinth.get_cols(); ++i) {
        if (labyrinth.is_valid_move(i, labyrinth.get_rows() - 1) && !labyrinth.is_valid_move(labyrinth.get_finish(1)) && labyrinth.labyrinth[labyrinth.get_rows() - 1][i] == labyrinth.SPACE) {
            labyrinth.set_finish(1, Point(i, labyrinth.get_rows() - 1));
        }
        else if (labyrinth.is_valid_move(i, labyrinth.get_rows() - 1) && !labyrinth.is_valid_move(labyrinth.get_finish(2)) && labyrinth.labyrinth[labyrinth.get_rows() - 1][i] == labyrinth.SPACE) {
            labyrinth.set_finish(2, Point(i, labyrinth.get_rows() - 1));
        }
    }

    for (int i = 0; i < labyrinth.get_rows(); ++i) {
        if (labyrinth.is_valid_move(labyrinth.get_cols() - 1, i) && !labyrinth.is_valid_move(labyrinth.get_finish(1)) && labyrinth.labyrinth[i][labyrinth.get_cols() - 1] == labyrinth.SPACE) {
            labyrinth.set_finish(1, Point(labyrinth.get_cols() - 1, i));
        }
        else if (labyrinth.is_valid_move(labyrinth.get_cols() - 1, i) && !labyrinth.is_valid_move(labyrinth.get_finish(2)) && labyrinth.labyrinth[i][labyrinth.get_cols() - 1] == labyrinth.SPACE) {
            labyrinth.set_finish(2, Point(labyrinth.get_cols() - 1, i));
        }
    }
}

void Game::initialize() {
    Point bot, human;
    find_exites();
    for (int i = 0; i < labyrinth.get_rows(); ++i) {
        for (int j = 0; j < labyrinth.get_cols(); ++j) {
            if (labyrinth.labyrinth[i][j] == BOT) {
                bot = Point(j, i);
            }
            else if (labyrinth.labyrinth[i][j] == PLAYER) {
                human = Point(j, i);
            }
            else if (labyrinth.labyrinth[i][j] == FIRE) {
                fire_loc.push(FireAi(j, i, FIRE));
            }
        }
    }
    difficulty_input();
    player = HumanPlayer(human, PLAYER);
    if (difficulty == 1) {
        EasyBot = EasyBotPlayer(bot, BOT);
        bot_player = &EasyBot;
        
    }
    else if (difficulty == 2) {
        RookieBot = RookieBotPlayer(bot, BOT);
        bot_player = &RookieBot;
        
    }
    else if (difficulty == 3) {
        fire_matrix_calc();
        MediumBot = MediumBotPlayer(bot, BOT, labyrinth);
        bot_player = &MediumBot;
    }
    else if (difficulty == 4) {
        fire_matrix_calc();
        HardBot = HardBotPlayer(bot, BOT, labyrinth);
        bot_player = &HardBot;
        //HardBot.start(labyrinth);
    }
}

void Game::fire_matrix_calc() {
    std::queue<FireAi> fire_queue = fire_loc;
    while (!fire_queue.empty())
    {
        fire_queue.front().fire_matrix_calc_algorithm(labyrinth);
        fire_queue.pop();
    }
}

//Moving fire if it is posible
void Game::fire_expanding(Point pos, int x, int y) {
    if (labyrinth.is_valid_move(pos.x + x, pos.y + y) && labyrinth.labyrinth[pos.y + y][pos.x + x] != FIRE && labyrinth.labyrinth[pos.y + y][pos.x + x] != DEAD && labyrinth.labyrinth[pos.y + y][pos.x + x] != PLAYER && labyrinth.labyrinth[pos.y + y][pos.x + x] != BOT) {
        labyrinth.labyrinth[pos.y + y][pos.x + x] = FIRE;
        fire_loc.push(FireAi(pos.x + x, pos.y + y, FIRE));
    }
}

bool Game::add_fire(int x, int y)
{
    if (!labyrinth.is_valid_move(x, y))
    {
        return false;
    }
    labyrinth.labyrinth[y][x] = FIRE;
    fire_loc.push(FireAi(x, y, FIRE));
    return true;

}


// Fire expanding function
void Game::fire_expand()
{
    int len = fire_loc.size();
    Point p;
    for (int i = 0; i < len; i++)
    {
        p = fire_loc.front().position;
        fire_loc.pop();
        fire_expanding(p, 1, 0);
        fire_expanding(p, -1, 0);
        fire_expanding(p, 0, 1);
        fire_expanding(p, 0, -1);
    }
}


void Game::play()
{
    initialize();
    bool have_winner = 0;
    char input;
    this->print_frame(labyrinth.get_labyrinth()); // print current labyrinth with player

    while (true && !have_winner) {
        //std::vector<std::string> mod_labyrinth(labyrinth.get_labyrinth()); // get labyrinth

        //if (have_winner)
        //{
        //    std::cout << endgame_message << std::endl;
        //    break;
        //}




        do {
            //std::cin >> input;
            input = std::toupper(getKeyPress());
            if (player.move_player(input, labyrinth))
            {
                if(!check_winner())
                {
                    if (labyrinth.is_fire_next_turn(player.position))
                    {
                        std::cout << "PLAYER STEPPED IN FIRE , BOT WON" << std::endl;
                        labyrinth.labyrinth[player.position.y][player.position.x] = DEAD;
                    }
                    break;
                }
                else
                {
                    have_winner = true;
                    labyrinth.labyrinth[bot_player->position.y][bot_player->position.x] = BOT;
                    break;
                }
            }


        } while (true);
        
    
        if (!have_winner) {
            bot_player->move(labyrinth);
            if (!check_winner())
            {
                if (labyrinth.is_fire_next_turn(bot_player->position))
                {
                    std::cout << "BOT STEPPED IN FIRE , PLAYER WON" << std::endl;
                    labyrinth.labyrinth[bot_player->position.y][bot_player->position.x] = DEAD;
                    have_winner = true;
                }
                fire_expand();
            }
            else {
                have_winner = true;
            }
        }

        if (bot_player->position == player.position)
        {
            labyrinth.labyrinth[player.position.y][player.position.x] = PLAYER_AND_BOT;
        }
        this->print_frame(labyrinth.get_labyrinth()); // print current labyrinth with player
    }

}

void Game::print_frame(const std::vector<std::string>& mod_labyrinth) const
{
    //mod_labyrinth[player.position.x][player.position.y] = player.sym;
    for (const auto& i : mod_labyrinth)
    {
        std::cout << i << std::endl;
    }
}

bool Game::check_winner()
{
    if (labyrinth.is_finish(player.position))
    {
        std::cout << "PLAYER WON" << std::endl;
        return true;
    }
    if (labyrinth.is_finish(bot_player->position))
    {
        std::cout << "BOT WON" << std::endl;
        return true;
    }
    return false;
}

Point Game::move_to_dir(char dir, Point loc)
{
    switch (dir) {
    case 'D':
        return Point(loc.x + 1, loc.y);
    case 'W':
        return Point(loc.x, loc.y - 1);
    case 'A':
        return Point(loc.x - 1, loc.y);
    case 'S':
        return Point(loc.x, loc.y + 1);
    }
}
