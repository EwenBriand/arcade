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

namespace Game
{
    class GameSnake : public IGameModule
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
            bool processFrame(std::vector<GUI::IDisplayModule::event_t> events) override;
            GUI::IDisplayModule::mapSpecs_t getMapSpecs() override;
            std::vector<GUI::IDisplayModule::pixel_t> getPixels() override;
            std::vector<GUI::IDisplayModule::text_t> getTexts() override;
            std::vector<std::string> getSounds() override;
            bool checkEvent(std::vector<GUI::IDisplayModule::event_t> events);
            bool checkCollision();
            void changeDirection(GUI::IDisplayModule::event_t &event);
            void moveSnake();
            void eatApple();
            void initApple();
        private:
            std::vector<GUI::IDisplayModule::pixel_t> _snake;
            std::vector<GUI::IDisplayModule::pixel_t> _wall;
            std::vector<GUI::IDisplayModule::pixel_t> _apple;
            std::vector<GUI::IDisplayModule::text_t> _texts;
            GUI::IDisplayModule::mapSpecs_t _mapspecs;
            direction _dir;
            int _score = 0;
    };
}

#endif /* DE054797_A52D_4EDB_B7C2_84126F4CB583 */
