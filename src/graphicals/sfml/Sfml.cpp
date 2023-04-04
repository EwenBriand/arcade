/*
** EPITECH PROJECT, 2022
** oop
** File description:
** sfml.cpp
*/

#include "Sfml.hpp"
#include <filesystem>
#include <iostream>

extern "C"
{
    GUI::IDisplayModule *entry_point()
    {
        return new GUI::Sfml();
    };
}

GUI::Sfml::Sfml()
{
    _start_time = std::time(nullptr);
    _font.loadFromFile("assets/fonts/Montserrat-Regular.ttf");
    _mapspecs = {0, 0, 0, 0};
    _pxpu = 5;
}

GUI::Sfml::~Sfml()
{
    _font.~Font();
    _windows.~RenderWindow();
    std::cout << "Destroying openWindow..." << std::endl;
}

void GUI::Sfml::setUnits(const int &pxpu)
{
    _pxpu = pxpu;
}

int GUI::Sfml::getUnits() const
{
    return _pxpu;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void GUI::Sfml::openWindow(const int &w, const int &h)
{
    _windows.create(sf::VideoMode(1920, 1080), "Arcade");
    _windows.setFramerateLimit(60);
}

void GUI::Sfml::closeWindow()
{
    _windows.close();
}

void GUI::Sfml::clearScr()
{
    _windows.clear();
    _pixels.clear();
}

sf::Color GUI::Sfml::getColor(const color_t &color) const
{
    switch (color) {
        case GUI::IDisplayModule::BLACK: return sf::Color::Black;
        case GUI::IDisplayModule::WHITE: return sf::Color::White;
        case GUI::IDisplayModule::RED: return sf::Color::Red;
        case GUI::IDisplayModule::GREEN: return sf::Color::Green;
        case GUI::IDisplayModule::BLUE: return sf::Color::Blue;
        case GUI::IDisplayModule::YELLOW: return sf::Color::Yellow;
        case GUI::IDisplayModule::MAGENTA: return sf::Color::Magenta;
        case GUI::IDisplayModule::CYAN: return sf::Color::Cyan;
        default: return sf::Color::Black;
    }
}

sf::Text GUI::Sfml::textTosfText(const text_t &text)
{
    sf::Text sfText;

    sfText.setFont(_font);
    sfText.setString(text.str);
    sfText.setCharacterSize(text.scale + 20);
    sfText.setFillColor(getColor(text.color));
    sfText.setPosition((float) text.x * 10, (float) text.y * 10);
    return sfText;
}

sf::RectangleShape GUI::Sfml::pixelTosfRect(const pixel_t &pixel)
{
    sf::RectangleShape sfRect(sf::Vector2f(_pxpu, _pxpu));

    sfRect.setFillColor(sf::Color(pixel.deltaRGB.r, pixel.deltaRGB.g, pixel.deltaRGB.b, 255));
    sfRect.setPosition(pixel.x * _pxpu, pixel.y * _pxpu);
    return sfRect;
}

void GUI::Sfml::draw()
{
    for (auto &text : _texts) {
        if (text.second.str.empty())
            continue;
        _windows.draw(textTosfText(text.second));
    }
    for (auto &pixel : _pixels)
        _windows.draw(pixelTosfRect(pixel));
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

void GUI::Sfml::checkKeyEvent(sf::Keyboard::Key key,
    GUI::Sfml::bindingType_t bindingKey, std::vector<event_t> &events,
    event_t event, int charCode)
{
    if (_event.key.code == key) {
        event._name = bindingKey;
        event.timeStamp = float(std::time(nullptr) - _start_time);
        event._ivalues.push_back(charCode);
        events.push_back(event);
    }
}

void GUI::Sfml::checkMouseEvent(sf::Mouse::Button mouse, bool isPressed,
    std::vector<event_t> &events, event_t event)
{
    if (_event.mouseButton.button == mouse) {
        event._name = MOUSE_CLICK;
        event.timeStamp = float(std::time(nullptr) - _start_time);
        event._ivalues.push_back(-1);
        event._ivalues.push_back(_event.mouseButton.x);
        event._ivalues.push_back(_event.mouseButton.y);
        switch (mouse) {
            case sf::Mouse::Left: event._ivalues.push_back(MOUSE_LEFT); break;
            case sf::Mouse::Right:
                event._ivalues.push_back(MOUSE_RIGHT);
                break;
            case sf::Mouse::Middle:
                event._ivalues.push_back(MOUSE_MIDDLE);
                break;
            default: break;
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
            checkKeyEvent(sf::Keyboard::Escape, QUIT, events, event);
            checkKeyEvent(sf::Keyboard::Left, LEFT, events, event);
            checkKeyEvent(sf::Keyboard::Right, RIGHT, events, event);
            checkKeyEvent(sf::Keyboard::Up, UP, events, event);
            checkKeyEvent(sf::Keyboard::Down, DOWN, events, event);
            checkKeyEvent(sf::Keyboard::Backspace, BACKSPACE, events, event);
            checkKeyEvent(sf::Keyboard::Enter, ENTER, events, event);
            checkKeyEvent(sf::Keyboard::Space, KEYCODE, events, event, ' ');
            for (sf::Keyboard::Key i; i < 26; i = sf::Keyboard::Key(i + 1)) {
                checkKeyEvent(i, KEYCODE, events, event, 'a' + i);
            }
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
    _pixels = pixels;
}

void GUI::Sfml::setText(std::string label, text_t text)
{
    _texts[label] = text;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void GUI::Sfml::loadSound(const std::string &label, const std::string &path)
{
    // sf::SoundBuffer buffer;

    // if (!buffer.loadFromFile(path))
    //     throw std::runtime_error("Error while loading sound");
    // _sounds.push_back(std::make_pair(label, sf::Sound(buffer)));
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void GUI::Sfml::playSound(const std::string &label, const bool &loop)
{
    // for (auto &sound : _sounds) {
    //     if (sound.first == label) {
    //         sound.second.play();
    //         if (loop)
    //             sound.second.setLoop(true);
    //         return;
    //     }
    // }
    // throw std::runtime_error("Error while playing sound");
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void GUI::Sfml::setSprite(char label, std::string path)
{
}
