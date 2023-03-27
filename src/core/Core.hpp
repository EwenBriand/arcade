/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** Core
*/

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

typedef GUI::IDisplayModule *(*entry_point_display)();
typedef Game::IGameModule *(*entry_point_game)();

#ifndef FAC672BB_0C81_4D9A_AD70_7FBC9A12F595
    #define FAC672BB_0C81_4D9A_AD70_7FBC9A12F595

namespace CORE
{

    class Core {
      private:
        GUI::IDisplayModule *_displays;
        Game::IGameModule *_game;
        std::string _ndisplay = "";
        std::string _ngame = "";
        std::vector<std::filesystem::path> _so_game;
        std::vector<std::filesystem::path> _so_graph;
        int _act_col = 0;

      public:
        Core(std::string filename);
        ~Core();
        void setDisplays(std::string ndisplay);
        void setGame(std::string ngame);
        void launchGame();
        std::vector<std::filesystem::path> find_so_files(
            const std::string &path);
        void display_menu();
        void event_menu(bool &status);
    };
} // namespace CORE

#endif /* FAC672BB_0C81_4D9A_AD70_7FBC9A12F595 */
