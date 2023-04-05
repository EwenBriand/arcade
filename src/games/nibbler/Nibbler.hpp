/*
** EPITECH PROJECT, 2022
** oop
** File description:
** Nibbler.hpp
*/

#pragma once

#include "IGameModule.hpp"

namespace Game
{
    class Nibbler : public IGameModule {
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
            Nibbler();
            ~Nibbler() override = default;
            /**
             * @brief Init the map of the game
             *
             */
            void buildMap();
            /**
             * @brief Init the snake of the game
             *
             */
            void buildSnake();
            /**
             * @brief Init the apple of the game
             *
             */
            void generateApple();
            /**
             * @brief Move the snake
             *
             */
            void moveSnake();
            /**
             * @brief Check if the snake is colliding with itself or the wall
             *
             * @return true if the snake is colliding, false otherwise
             */
            bool checkCollision();
            /**
             * @brief Check if the snake is eating an apple
             *
             */
            void eatApple();
            /**
             * @brief Check in what direction the snake is going
             *
             * @param events events from the display module
             * @return false if the user wants to quit the game, true otherwise
             */
            bool checkEvent(std::vector<GUI::IDisplayModule::event_t> events);
            /**
             * @brief Change the direction of the snake
             *
             * @param event event from the display module
             */
            void changeDirection(GUI::IDisplayModule::event_t &event);
            /**
             * @brief Update the score
             *
             */
            void updateScore();
            bool processFrame(std::vector<GUI::IDisplayModule::event_t>) override;
            GUI::IDisplayModule::mapSpecs_t getMapSpecs() override;
            std::vector<GUI::IDisplayModule::pixel_t> getPixels() override;
            std::vector<GUI::IDisplayModule::text_t> getTexts() override;
            std::vector<std::string> getSounds() override;
            /**
             * @brief Get the Map Wall Pos From File object
             *
             * @param path path to the file
             * @return the map in a 2D array of int
             */
            int **getMapWallPosFromFile(std::string path);
        private:
            std::vector<GUI::IDisplayModule::pixel_t> _pixels;
            std::vector<GUI::IDisplayModule::pixel_t> _snake;
            std::vector<GUI::IDisplayModule::pixel_t> _wall;
            std::vector<GUI::IDisplayModule::pixel_t> _apple;
            std::vector<GUI::IDisplayModule::text_t> _texts;
            GUI::IDisplayModule::mapSpecs_t _mapspecs;
            direction _dir;
            int _score;
            bool _shouldMove;
    };
}
