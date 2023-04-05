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

#include <ctime>
#include <map>

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
            /**
             * @brief Get the Units object
             *
             * @return int
             */
            int getUnits() const override;
            /**
             * @brief Set the Map Specs object
             *
             * @param mapspecs specs of the map
             */
            void setMapSpecs(mapSpecs_t mapspecs) override;
            /**
             * @brief Check if a key is pressed
             *
             * @param key
             * @param bindingKey
             * @param events
             * @param event
             * @param charCode
             */
            void checkKeyEvent(sf::Keyboard::Key key, GUI::Sfml::bindingType_t bindingKey, std::vector<event_t> &events, event_t event, int charCode = -1);
            /**
             * @brief Check if a mouse button is pressed
             *
             * @param mouse
             * @param isPressed
             * @param events
             * @param event
             */
            void checkMouseEvent(sf::Mouse::Button mouse, bool isPressed, std::vector<event_t> &events, event_t event);
            std::vector<event_t> pollEvents() override;

            void loadSound(const std::string &label, const std::string &path) override;
            void playSound(const std::string &label, const bool &loop = false) override;

            void setWindowSize(const int &w, const int &h) override;
            void openWindow(const int &w, const int &h) override;
            void closeWindow() override;
            void clearScr() override;
            /**
             * @brief Get the Color of a color_t
             *
             * @param color color_t rgb
             * @return sf::Color
             */
            sf::Color getColor(const color_t &color) const;
            /**
             * @brief Convert a text_t to a sf::Text
             *
             * @param text text_t
             * @return sf::Text
             */
            sf::Text textTosfText(const text_t &text);
            /**
             * @brief Convert a pixel_t to a sf::RectangleShape
             *
             * @param pixel pixel_t
             * @return sf::RectangleShape
             */
            sf::RectangleShape pixelTosfRect(const pixel_t &pixel);

            void draw() override;
            void updatePixels(std::vector<pixel_t> pixels) override;
            void setText(std::string label, text_t text) override;
            void setSprite(char label, std::string path) override;

        private:
            int _pxpu;
            sf::RenderWindow _windows;
            sf::Event _event;
            mapSpecs_t _mapspecs;
            std::map<std::string, sf::Sound> _sounds;
            std::map<std::string, text_t> _texts;
            sf::Font _font;
            std::time_t _start_time;
            std::vector<pixel_t> _pixels;
    };
}
