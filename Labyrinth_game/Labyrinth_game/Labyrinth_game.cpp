#include <iostream>
#include "Labyrinth.h"
#include "HumanPlayer.h"
#include "Game.h"
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

bool isNumeric(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> getDirectoryFiles(const fs::path& directory, const std::vector<std::string> extensions)
{
    // List of file names.
    std::vector<std::string> files{};

    for (const auto& file : fs::recursive_directory_iterator(directory))
    {
        if (fs::is_regular_file(file))
        {
            if (extensions.empty() ||
                std::find(extensions.begin(), extensions.end(), file.path().extension().string()) != (extensions.end()))
            {
                files.push_back(file.path().filename().string());
            }
        }
    }
    return files;
}


int main()
{
    std::cout << "LABYRINTH GAME: RACE" << std::endl;
    auto fileList = getDirectoryFiles(fs::current_path(), { ".txt" });
    while (true)
    {
        std::cout << '\n' << "Avilable labyrinths" << std::endl;
        for (int i = 0; i < fileList.size(); i++)
        {
            std::cout << i + 1 << '.' << fileList[i] << std::endl;
        }
        std::cout << "Enter labyrinth number to play game or E to exit" << std::endl;
        std::string input;
        bool exit = 0;
        std::string labyrinth_string;
        do {
            std::cin >> input;
            if (input == std::string(1, 'E') or input == std::string(1, 'e'))
            {
                exit = true;
                break;
            }


            if(isNumeric(input))
            {
                if (std::stoi(input) >= 1 && std::stoi(input) <= fileList.size())
                {
                    labyrinth_string = fileList[std::stoi(input) - 1];
                    break;
                }
            }
            std::cout << "Invalid input: Try again: ";

        } while (true);

        if (exit)
        {
            break;
        }
        Labyrinth lab_1(labyrinth_string);
        Game game(lab_1);
        game.play();
    }

}

