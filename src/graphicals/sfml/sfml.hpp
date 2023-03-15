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

            void setMapSpecs(mapSpecs_t mapspecs) override;

            std::vector<event_t> pollEvents() override;

            void loadSound(const std::string &label, const std::string &path) override;
            void playSound(const std::string &label, const bool &loop = false) override;

            void setWindowSize(const int &w, const int &h) override;
            void openWindow(const int &w, const int &h) override;
            void closeWindow() override;
            void clearScr() override;

            void draw();
            void updatePixels(std::vector<pixel_t> pixels) override;
            void setText(std::string label, text_t text) override;

        private:
            int _pxpu;
            sf::RenderWindow _windows;
            sf::Event _event;
            mapSpecs_t _mapspecs;
            std::vector<std::pair<std::string, sf::Sound>> _sounds;
            std::vector<std::pair<std::string, sf::Text>> _texts;
    };
}
