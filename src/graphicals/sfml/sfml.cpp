/*
** EPITECH PROJECT, 2022
** oop
** File description:
** sfml.cpp
*/

#include "sfml.hpp"
#include <filesystem>

extern "C" {
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

    std::vector<GUI::Sfml::event_t> GUI::Sfml::pollEvents()
    {
        std::vector<GUI::Sfml::event_t> events;
        GUI::Sfml::event_t event;

        while (_windows.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                event._name = QUIT;
                events.push_back(event);
                GUI::Sfml::closeWindow();
            }
            if (_event.type == sf::Event::KeyPressed) {
                if (_event.key.code == sf::Keyboard::Escape) {
                    event._name = QUIT;
                    events.push_back(event);
                    GUI::Sfml::closeWindow();
                }
                if (_event.key.code == sf::Keyboard::Left) {
                    event._name = LEFT;
                    events.push_back(event);
                }
                if (_event.key.code == sf::Keyboard::Right) {
                    event._name = RIGHT;
                    events.push_back(event);
                }
                if (_event.key.code == sf::Keyboard::Up) {
                    event._name = UP;
                    events.push_back(event);
                }
                if (_event.key.code == sf::Keyboard::Down) {
                    event._name = DOWN;
                    events.push_back(event);
                }
            }
            if (_event.type == sf::Event::MouseButtonPressed) {
                if (_event.mouseButton.button == sf::Mouse::Left) {
                    event._name = MOUSE_CLICK;
                    event._ivalues.push_back(_event.mouseButton.x);
                    event._ivalues.push_back(_event.mouseButton.y);
                    event._ivalues.push_back(MOUSE_LEFT);
                    event._ivalues.push_back(MOUSE_PRESSED);
                    events.push_back(event);
                }
                if (_event.mouseButton.button == sf::Mouse::Right) {
                    event._name = MOUSE_CLICK;
                    event._ivalues.push_back(_event.mouseButton.x);
                    event._ivalues.push_back(_event.mouseButton.y);
                    event._ivalues.push_back(MOUSE_RIGHT);
                    event._ivalues.push_back(MOUSE_PRESSED);
                    events.push_back(event);
                }
                if (_event.mouseButton.button == sf::Mouse::Middle) {
                    event._name = MOUSE_CLICK;
                    event._ivalues.push_back(_event.mouseButton.x);
                    event._ivalues.push_back(_event.mouseButton.y);
                    event._ivalues.push_back(MOUSE_MIDDLE);
                    event._ivalues.push_back(MOUSE_PRESSED);
                    events.push_back(event);
                }
            }
            if (_event.type == sf::Event::MouseButtonReleased) {
                if (_event.mouseButton.button == sf::Mouse::Left) {
                    event._name = MOUSE_CLICK;
                    event._ivalues.push_back(_event.mouseButton.x);
                    event._ivalues.push_back(_event.mouseButton.y);
                    event._ivalues.push_back(MOUSE_LEFT);
                    event._ivalues.push_back(MOUSE_RELEASED);
                    events.push_back(event);
                }
                if (_event.mouseButton.button == sf::Mouse::Right) {
                    event._name = MOUSE_CLICK;
                    event._ivalues.push_back(_event.mouseButton.x);
                    event._ivalues.push_back(_event.mouseButton.y);
                    event._ivalues.push_back(MOUSE_RIGHT);
                    event._ivalues.push_back(MOUSE_RELEASED);
                    events.push_back(event);
                }
                if (_event.mouseButton.button == sf::Mouse::Middle) {
                    event._name = MOUSE_CLICK;
                    event._ivalues.push_back(_event.mouseButton.x);
                    event._ivalues.push_back(_event.mouseButton.y);
                    event._ivalues.push_back(MOUSE_MIDDLE);
                    event._ivalues.push_back(MOUSE_RELEASED);
                    events.push_back(event);
                }
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
            _windows.draw(_pixel);
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
