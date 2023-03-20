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
                RIGHT
            };
            Nibbler();
            ~Nibbler() override = default;
            GUI::IDisplayModule::pixel_t setPixel(GUI::IDisplayModule::color_t color, GUI::IDisplayModule::deltaRGB_t deltaRGB, unsigned char repr, int x, int y);
            void buildMap();
            void buildSnake();
            void generateApple();
            void moveSnake();
            bool checkCollision();
            bool Game::Nibbler::checkEvent(GUI::IDisplayModule::event_t &event);
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
            GUI::IDisplayModule::mapSpecs_t _mapSpecs;
            std::vector<GUI::IDisplayModule::text_t> _texts;
            std::vector<std::string> _sounds;
            direction _dir;
    };
}
