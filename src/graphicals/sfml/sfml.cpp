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

    void GUI::Sfml::drawText(const std::string &text, int x, int y, const GUI::Sfml::color_t &color)
    {
        sf::Text _text;
        sf::Font _font;

        _font.loadFromFile("./assets/fonts/Montserrat-Regular.ttf");
        _text.setFont(_font);
        _text.setString(text);
        _text.setCharacterSize(10);
        _text.setFillColor(sf::Color::White);
        _text.setPosition(x, y);
        _windows.draw(_text);
    }

    void GUI::Sfml::playSound(const std::string &id, bool loop = false)
    {
        sf::SoundBuffer _buffer;

        _buffer.loadFromFile("./assets/sounds/" + id + ".wav");
        _sound.setBuffer(_buffer);
        _sound.setLoop(loop);
        _sound.play();
    }

    void GUI::Sfml::stopSound(const std::string &id)
    {
        _sound.stop();
    }

    void GUI::Sfml::setVolume(const int &between_zero_and_100)
    {
        _sound.setVolume(between_zero_and_100);
    }

    void GUI::Sfml::setPitch(const float &multiplyer)
    {
        _sound.setPitch(multiplyer);
    }

    void GUI::Sfml::setLoop(const bool &loop)
    {
        _sound.setLoop(loop);
    }

    std::vector<GUI::Sfml::sound_t> GUI::Sfml::loadSounds(const std::string &dir)
    {
        for (const auto &file : std::filesystem::directory_iterator(dir)) {
            GUI::Sfml::sound_t sound;

            sound.path = file.path();
            sound.id = file.path().filename().string();
            _sounds.push_back(sound);
        }
        return _sounds;
    }

    GUI::IDisplayModule *entrypoint()
    {
        return new GUI::Sfml();
    }
}
