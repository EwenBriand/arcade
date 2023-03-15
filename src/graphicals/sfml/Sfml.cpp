/*
** EPITECH PROJECT, 2022
** oop
** File description:
** sfml.cpp
*/

#include "Sfml.hpp"
#include <filesystem>
#include <iostream>

extern "C" {
    GUI::Sfml::Sfml()
    {
        _start_time = std::time(nullptr);
    }

    void GUI::Sfml::setUnits(const int &pxpu)
    {
        _pxpu = pxpu;
    }

    int GUI::Sfml::getUnits() const
    {
        return _pxpu;
    }

    void GUI::Sfml::openWindow(const int &w, const int &h)
    {
        _windows.create(sf::VideoMode(w, h), "Arcade");
    }

    void GUI::Sfml::closeWindow()
    {
        _windows.close();
    }

    void GUI::Sfml::clearScr()
    {
        _windows.clear();
    }

    void GUI::Sfml::draw()
    {
        _windows.display();
    }

    void GUI::Sfml::setWindowSize(const int &w, const int &h)
    {
        _windows.setSize(sf::Vector2u(w, h));
    }

    void GUI::Sfml::setMapSpecs(mapSpecs_t mapspecs)
    {
        _mapspecs = mapspecs;
    }

    void GUI::Sfml::loadSound(const std::string &label, const std::string &path)
    {
        sf::SoundBuffer buffer;
        sf::Sound sound;

        if (!buffer.loadFromFile(path)) {
            std::cerr << "Error: Can't load sound file" << std::endl;
            return;
        }
        sound.setBuffer(buffer);
        _sounds.push_back(std::make_pair(label, sound));
    }

    void GUI::Sfml::checkKeyEvent(sf::Keyboard::Key key, GUI::Sfml::bindingType_t bindingKey, std::vector<event_t> &events, event_t event)
    {
        if (_event.key.code == key) {
            event._name = bindingKey;
            event.timeStamp = float(std::time(nullptr) - _start_time);
            events.push_back(event);
        }
    }

    void GUI::Sfml::checkMouseEvent(sf::Mouse::Button mouse, bool isPressed, std::vector<event_t> &events, event_t event)
    {
        if (_event.mouseButton.button == mouse) {
            event._name = MOUSE_CLICK;
            event.timeStamp = float(std::time(nullptr) - _start_time);
            event._ivalues.push_back(_event.mouseButton.x);
            event._ivalues.push_back(_event.mouseButton.y);
            switch (mouse) {
                case sf::Mouse::Left:
                    event._ivalues.push_back(MOUSE_LEFT);
                    break;
                case sf::Mouse::Right:
                    event._ivalues.push_back(MOUSE_RIGHT);
                    break;
                case sf::Mouse::Middle:
                    event._ivalues.push_back(MOUSE_MIDDLE);
                    break;
                default:
                    break;
            }
            event._ivalues.push_back(isPressed ? MOUSE_PRESSED : MOUSE_RELEASED);
            events.push_back(event);
        }
    }

    std::vector<GUI::Sfml::event_t> GUI::Sfml::pollEvents()
    {
        std::vector<GUI::Sfml::event_t> events;
        GUI::Sfml::event_t event;

        while (_windows.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                event._name = QUIT;
                event.timeStamp = float(std::time(nullptr) - _start_time);
                events.push_back(event);
                closeWindow();
            }
            if (_event.type == sf::Event::KeyPressed) {
                if (_event.key.code == sf::Keyboard::Escape) {
                    event._name = QUIT;
                    event.timeStamp = float(std::time(nullptr) - _start_time);
                    events.push_back(event);
                    closeWindow();
                }
                checkKeyEvent(sf::Keyboard::Left, LEFT, events, event);
                checkKeyEvent(sf::Keyboard::Right, RIGHT, events, event);
                checkKeyEvent(sf::Keyboard::Up, UP, events, event);
                checkKeyEvent(sf::Keyboard::Down, DOWN, events, event);
            }
            if (_event.type == sf::Event::MouseButtonPressed) {
                checkMouseEvent(sf::Mouse::Left, true, events, event);
                checkMouseEvent(sf::Mouse::Right, true, events, event);
                checkMouseEvent(sf::Mouse::Middle, true, events, event);
            }
            if (_event.type == sf::Event::MouseButtonReleased) {
                checkMouseEvent(sf::Mouse::Left, false, events, event);
                checkMouseEvent(sf::Mouse::Right, false, events, event);
                checkMouseEvent(sf::Mouse::Middle, false, events, event);
            }
        }
        return events;
    }

    void GUI::Sfml::updatePixels(const std::vector<GUI::Sfml::pixel_t> pixels)
    {
        sf::RectangleShape _pixel;

        for (auto &pixel : pixels) {
            _pixel.setSize(sf::Vector2f(_pxpu, _pxpu));
            _pixel.setFillColor(sf::Color(pixel.color));
            _pixel.setPosition(pixel.x * _pxpu, pixel.y * _pxpu);
            draw();
        }
    }

    void GUI::Sfml::setText(std::string label, text_t text)
    {
        sf::Text _text;
        sf::Font _font;

        _font.loadFromFile("./assets/fonts/Montserrat-Regular.ttf");
        _text.setFont(_font);
        _text.setString(text.str);
        _text.setCharacterSize(text.scale);
        _text.setFillColor(sf::Color(text.color));
        _text.setPosition(text.x, text.y);
        _texts.push_back(std::make_pair(label, _text));
    }

    void GUI::Sfml::loadSound(const std::string &label, const std::string &path)
    {
        sf::SoundBuffer buffer;

        if (!buffer.loadFromFile(path))
            throw std::runtime_error("Error while loading sound");
        _sounds.push_back(std::make_pair(label, sf::Sound(buffer)));
    }

    void GUI::Sfml::playSound(const std::string &label, const bool &loop = false)
    {
        for (auto &sound : _sounds) {
            if (sound.first == label) {
                sound.second.play();
                if (loop)
                    sound.second.setLoop(true);
                return;
            }
        }
        throw std::runtime_error("Error while playing sound");
    }

    GUI::IDisplayModule *entrypoint()
    {
        return new GUI::Sfml();
    }
}
