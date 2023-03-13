/*
** EPITECH PROJECT, 2022
** oop
** File description:
** sfml.hpp
*/

#pragma once

#include "IDisplayModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2

#define MOUSE_PRESSED 0
#define MOUSE_RELEASED 1

namespace GUI
{
    class Sfml : public IDisplayModule {
        public:
            Sfml();
            ~Sfml();
            void setUnits(const int &pxpu) override;
            int getUnits() const override;

            std::vector<event_t> pollEvents() override;

            void playSound(const std::string &id, bool loop = false) override;
            void stopSound(const std::string &id) override;
            void setVolume(const int &between_zero_and_100) override;
            void setPitch(const float &multiplier) override;
            void setLoop(const bool &loop) override;
            std::vector<sound_t> loadSounds(const std::string &dir) override;

            void setWindowSize(const int &w, const int &h) override;
            void openWindow(const int &w, const int &h) override;
            void closeWindow() override;
            void clearScr() override;

            void draw();
            void updatePixels(std::vector<pixel_t> pixels) override;
            void drawText(const std::string &text, int x, int y, const color_t &color) override;

        private:
            int _pxpu;
            sf::RenderWindow _windows;
            sf::Event _event;
            sf::Sound _sound;
            sf::vector<sound_t> _sounds;
    };
}
