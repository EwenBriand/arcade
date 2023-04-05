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
            /**
             * @brief Enum for the direction of the snake
             *
             */
            enum direction {
                UP,
                DOWN,
                LEFT,
                RIGHT
            };
            GameSnake();
            ~GameSnake() = default;
            /**
             * @brief Init the wall of the game
             *
             */
            void initWall();
            bool processFrame(std::vector<GUI::IDisplayModule::event_t> events) override;
            GUI::IDisplayModule::mapSpecs_t getMapSpecs() override;
            std::vector<GUI::IDisplayModule::pixel_t> getPixels() override;
            std::vector<GUI::IDisplayModule::text_t> getTexts() override;
            std::vector<std::string> getSounds() override;
            /**
             * @brief Check in what direction the snake is going
             *
             * @param events events from the display module
             * @return false if the user wants to quit the game, true otherwise
             */
            bool checkEvent(std::vector<GUI::IDisplayModule::event_t> events);
            /**
             * @brief Check if the snake is colliding with itself or the wall
             *
             * @return true if the snake is colliding, false otherwise
             */
            bool checkCollision();
            /**
             * @brief Change the direction of the snake
             *
             * @param event event from the display module
             */
            void changeDirection(GUI::IDisplayModule::event_t &event);
            /**
             * @brief Move the snake
             *
             */
            void moveSnake();
            /**
             * @brief Check if the snake is eating an apple
             *
             */
            void eatApple();
            /**
             * @brief Init the apple
             *
             */
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
