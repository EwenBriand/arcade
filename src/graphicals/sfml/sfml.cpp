/*
** EPITECH PROJECT, 2022
** oop
** File description:
** sfml.cpp
*/

#include "sfml.hpp"

extern "C" {
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

    GUI::IDisplayModule *entrypoint()
    {
        return new GUI::Sfml();
    }
}
