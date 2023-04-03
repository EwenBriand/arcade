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
            enum direction {
                UP,
                DOWN,
                LEFT,
                RIGHT,
                NONE
            };
            Nibbler();
            ~Nibbler() override = default;
            void buildMap();
            void buildSnake();
            void generateApple();
            void moveSnake();
            bool checkCollision();
            void eatApple();
            bool checkEvent(std::vector<GUI::IDisplayModule::event_t> events);
            void changeDirection(GUI::IDisplayModule::event_t &event);
            void updateScore();
            bool processFrame(std::vector<GUI::IDisplayModule::event_t>) override;
            GUI::IDisplayModule::mapSpecs_t getMapSpecs() override;
            std::vector<GUI::IDisplayModule::pixel_t> getPixels() override;
            std::vector<GUI::IDisplayModule::text_t> getTexts() override;
            std::vector<std::string> getSounds() override;
        private:
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
