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
        void *_handle_d = nullptr;
        void *_handle_g = nullptr;
        std::vector<std::string> _texts;
        int _act_g = 0;
        int _act_d = 0;

      public:
        class Error : public std::exception {
          private:
            std::string _msg;

          public:
            /**
             * @brief Construct a new Error object
             *
             * @param msg message of the error
             */
            Error(std::string msg) : _msg(msg)
            {
            }
            /**
             * @brief Get the message of the error
             *
             * @return const char*
             */
            const char *what() const noexcept override
            {
                return _msg.c_str();
            }
        };
        /**
         * @brief Construct a new Core object
         *
         * @param filename name of the library graphical
         */
        Core(std::string filename);
        ~Core();
        /**
        * @brief Set the graphical library to use
        * @param ndisplay name of the library
        */
        void setDisplays(std::string ndisplay);
        /**
         * @brief Set the game to use
         *
         * @param ngame name of the game
         */
        void setGame(std::string ngame);
        /**
         * @brief Launch the game
         *
         */
        void launchGame();
        /**
         * @brief Get the graphical library
         * @param path path to the library
         * @return std::vector<std::filesystem::path> list of the
         * graphical and game libraries
         */
        std::vector<std::filesystem::path> find_so_files(
            const std::string &path);
        /**
         * @brief display the menu
         *
         */
        void display_menu();
        /**
         * @brief get all the events of the menu
         *
         * @param status change to false if the user want to quit
         */
        void event_menu(bool &status);
        /**
         * @brief launch the game
         * @param status change to false if the user want to quit
         * @return int 1 if the user want to quit, 0 if all is ok, 2 if the
         * user want to change the game
         */
        int start_game(bool &status);
        /**
         * @brief clear the text
         */
        void clear_text();
        /**
         * @brief add a lib to the list of the lib
         * @param str name of the lib
         */
        void addIfNotPresent(std::string str);
    };
} // namespace CORE

#endif /* FAC672BB_0C81_4D9A_AD70_7FBC9A12F595 */
