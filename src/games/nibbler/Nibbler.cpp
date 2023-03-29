/*
** EPITECH PROJECT, 2022
** oop
** File description:
** Nibbler.cpp
*/

#include "Nibbler.hpp"
#include <random>

extern "C" {
    Game::IGameModule *entry_point()
    {
        return new Game::Nibbler();
    }
}

Game::Nibbler::Nibbler()
{
    _dir = direction::LEFT;
    buildSnake();
    buildMap();
    generateApple();
}

GUI::IDisplayModule::pixel_t setPixel(GUI::IDisplayModule::color_t color, GUI::IDisplayModule::deltaRGB_t deltaRGB, unsigned char repr, int x, int y)
{
    GUI::IDisplayModule::pixel_t pixel;

    pixel.color = color;
    pixel.deltaRGB = deltaRGB;
    pixel.repr = repr;
    pixel.x = x;
    pixel.y = y;
    return pixel;
}

void Game::Nibbler::buildMap()
{
    GUI::IDisplayModule::deltaRGB_t white = {255, 255, 255};

    for (unsigned int i = 5; i < 51; i++) {
        _wall.push_back(setPixel(GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 5));
        _wall.push_back(setPixel(GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 50));
        _wall.push_back(setPixel(GUI::IDisplayModule::color_t::WHITE, white, 'M', 5, i));
        _wall.push_back(setPixel(GUI::IDisplayModule::color_t::WHITE, white, 'M', 50, i));
    }
}

void Game::Nibbler::buildSnake()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};

    _snake.push_back(setPixel(GUI::IDisplayModule::color_t::GREEN, green, 'C', 49, 49));
    _snake.push_back(setPixel(GUI::IDisplayModule::color_t::GREEN, green, 'C', 48, 49));
    _snake.push_back(setPixel(GUI::IDisplayModule::color_t::GREEN, green, 'C', 47, 49));
    _snake.push_back(setPixel(GUI::IDisplayModule::color_t::GREEN, green, 'S', 46, 49));
}

void Game::Nibbler::generateApple()
{
    GUI::IDisplayModule::deltaRGB_t red = {255, 0, 0};
    int random = rand() % 49 + 1;

    for (auto &i : _snake) {
        if (i.x == random && i.y == random) {
            random = rand() % 49 + 1;
            i = _snake[0];
        }
    }
    _apple.push_back(setPixel(GUI::IDisplayModule::color_t::RED, red, 'A', random, random));
}

void Game::Nibbler::moveSnake()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};

    _snake[0].repr = 'c';
    if (_dir == direction::UP)
        _snake.insert(_snake.begin(),
            {GUI::IDisplayModule::color_t::GREEN, green, 's', _snake[0].x,
                _snake[0].y - 1});
    if (_dir == direction::DOWN)
        _snake.insert(_snake.begin(),
            {GUI::IDisplayModule::color_t::GREEN, green, 's', _snake[0].x,
                _snake[0].y + 1});
    if (_dir == direction::LEFT)
        _snake.insert(_snake.begin(),
            {GUI::IDisplayModule::color_t::GREEN, green, 's', _snake[0].x - 1,
                _snake[0].y});
    if (_dir == direction::RIGHT)
        _snake.insert(_snake.begin(),
            {GUI::IDisplayModule::color_t::GREEN, green, 's', _snake[0].x + 1,
                _snake[0].y});
    _snake.pop_back();
}

bool Game::Nibbler::checkCollision()
{
    int x = _dir == direction::LEFT ? -1 : _dir == direction::RIGHT ? 1 : 0;
    int y = _dir == direction::UP ? -1 : _dir == direction::DOWN ? 1 : 0;

    for (auto &wall : _wall) {
        if (wall.x == (_snake[0].x + x) && wall.y == (_snake[0].y + y))
            return true;
    }
    for (unsigned int i = 1; i < _snake.size(); i++) {
        if ((_snake[0].x + x) == _snake[i].x
            && (_snake[0].y + y) == _snake[i].y)
            return true;
    }
    return false;
}

void Game::Nibbler::changeDirection(GUI::IDisplayModule::event_t &event)
{
    if (event._name == GUI::IDisplayModule::bindingType_t::UP) {
        if (_dir == direction::DOWN || _dir == direction::UP)
            return;
        _dir = direction::UP;
    }
    if (event._name == GUI::IDisplayModule::bindingType_t::DOWN) {
        if (_dir == direction::UP || _dir == direction::DOWN)
            return;
        _dir = direction::DOWN;
    }
    if (event._name == GUI::IDisplayModule::bindingType_t::LEFT) {
        if (_dir == direction::RIGHT || _dir == direction::LEFT)
            return;
        _dir = direction::LEFT;
    }
    if (event._name == GUI::IDisplayModule::bindingType_t::RIGHT) {
        if (_dir == direction::LEFT || _dir == direction::RIGHT)
            return;
        _dir = direction::RIGHT;
    }
}

void Game::Nibbler::eatApple()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};

    if (_snake[0].x == _apple[0].x && _snake[0].y == _apple[0].y) {
        _snake.push_back({GUI::IDisplayModule::color_t::GREEN, green, 'c',
            _snake[_snake.size() - 1].x, _snake[_snake.size() - 1].y});
        _apple.clear();
        generateApple();
        _score += 100;
    }
}

bool Game::Nibbler::checkEvent(
    std::vector<GUI::IDisplayModule::event_t> events)
{
    for (auto &event : events) {
        if (event._name == GUI::IDisplayModule::bindingType_t::QUIT)
            return false;
        changeDirection(event);
    }
    return true;
}

bool Game::Nibbler::processFrame(std::vector<GUI::IDisplayModule::event_t> events)
{
    _texts.clear();
    if (!checkEvent(events))
        return false;
    if (checkCollision())
        return false;
    moveSnake();
    eatApple();
    return true;
}

std::vector<GUI::IDisplayModule::text_t> Game::Nibbler::getTexts()
{
    _texts.push_back({"Score: " + std::to_string(_score), 71, 0, 18,
        GUI::IDisplayModule::color_t::WHITE});
    return _texts;
}

GUI::IDisplayModule::mapSpecs_t Game::Nibbler::getMapSpecs()
{
    return _mapspecs;
}
