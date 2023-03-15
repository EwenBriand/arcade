/*
** EPITECH PROJECT, 2022
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** GameSnake.hpp
*/

#ifndef DE054797_A52D_4EDB_B7C2_84126F4CB583
#define DE054797_A52D_4EDB_B7C2_84126F4CB583

#include "IGameModule.hpp"
#include <iostream>

class GameSnake : public Game::IGameModule
{
    public:
        enum direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        GameSnake();
        ~GameSnake() = default;
        void initWall();
        bool run(GUI::IDisplayModule &gui, bool &stopGame) override;
        bool checkEvent(GUI::IDisplayModule &gui);
        bool checkCollision();
        void changeDirection(GUI::IDisplayModule::event_t &event);
        void moveSnake();
        void eatApple();
        void initApple();
    private:
        std::vector<GUI::IDisplayModule::pixel_t> _snake;
        std::vector<GUI::IDisplayModule::pixel_t> _wall;
        std::vector<GUI::IDisplayModule::pixel_t> _apple;
        direction _dir;
        int _score = 0;
};

#endif /* DE054797_A52D_4EDB_B7C2_84126F4CB583 */
