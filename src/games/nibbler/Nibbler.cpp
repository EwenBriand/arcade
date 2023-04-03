/*
** EPITECH PROJECT, 2022
** oop
** File description:
** Nibbler.cpp
*/

#include "Nibbler.hpp"
#include <random>
#include <iostream>

extern "C" {
    Game::IGameModule *entry_point()
    {
        return new Game::Nibbler();
    };
}

Game::Nibbler::Nibbler()
{
    _dir = direction::LEFT;
    buildSnake();
    buildMap();
    generateApple();
    _shouldMove = true;
}

void Game::Nibbler::buildMap()
{
    GUI::IDisplayModule::deltaRGB_t white = {255, 255, 255};

    for (int i = 5; i < 51; i++) {
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 5, "", 0});
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 50, "", 0});
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', 5, i, "", 0});
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', 50, i, "", 0});
    }
}

void Game::Nibbler::buildSnake()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};
    _dir = direction::LEFT;
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'S', 25, 48, "", 0});
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'C', 26, 48, "", 0});
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'C', 27, 48, "", 0});
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'C', 28, 48, "", 0});
}

void Game::Nibbler::generateApple()
{
    GUI::IDisplayModule::deltaRGB_t red = {255, 0, 0};
    int randomx = 6 + (rand() % 43);
    int randomy = 6 + (rand() % 43);

    for (auto &i : _snake) {
        if (i.x == randomx && i.y == randomy) {
            randomx = 6 + (rand() % 43);
            randomy = 6 + (rand() % 43);
            i = _snake[0];
        }
    }
    _apple.push_back({GUI::IDisplayModule::color_t::RED, red, 'A', randomx,
        randomy, "", 0});
}

void Game::Nibbler::moveSnake()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};

    if (_shouldMove) {
        _snake[0].repr = 'C';
        if (_dir == direction::UP)
            _snake.insert(_snake.begin(),
                {GUI::IDisplayModule::color_t::GREEN, green, 'S', _snake[0].x,
                    _snake[0].y - 1, "", 0});
        if (_dir == direction::DOWN)
            _snake.insert(_snake.begin(),
                {GUI::IDisplayModule::color_t::GREEN, green, 'S', _snake[0].x,
                    _snake[0].y + 1, "", 0});
        if (_dir == direction::LEFT)
            _snake.insert(_snake.begin(),
                {GUI::IDisplayModule::color_t::GREEN, green, 'S', _snake[0].x - 1,
                    _snake[0].y, "", 0});
        if (_dir == direction::RIGHT)
            _snake.insert(_snake.begin(),
                {GUI::IDisplayModule::color_t::GREEN, green, 'S', _snake[0].x + 1,
                    _snake[0].y, "", 0});
        _snake.pop_back();
    }
}

bool Game::Nibbler::checkCollision()
{
    int x = (_dir == direction::LEFT) ? -1 : _dir == direction::RIGHT ? 1 : 0;
    int y = (_dir == direction::UP) ? -1 : _dir == direction::DOWN ? 1 : 0;

    // The snake can turn right or left automatically when colliding with a wall, or stop at T-junction
    for (auto &i : _pixels) {
        if (i.x == _snake[0].x + x && i.y == _snake[0].y + y) {
            if (i.repr == 'M') {
                if (_dir == direction::UP || _dir == direction::DOWN) {
                    // if (i.x == _snake[0].x + 1) {
                    //     std::cout << "RIGHT" << std::endl;
                    //     _dir = direction::RIGHT;
                    // }
                    // else if (i.x == _snake[0].x - 1) {
                    //     std::cout << "LEFT" << std::endl;
                    //     _dir = direction::LEFT;
                    // }
                    // else
                        _shouldMove = false;
                } else if (_dir == direction::LEFT || _dir == direction::RIGHT) {
                    // if (i.y == _snake[0].y + 1) {
                    //     std::cout << "DOWN" << std::endl;
                    //     _dir = direction::DOWN;
                    // }
                    // else if (i.y == _snake[0].y - 1) {
                    //     std::cout << "UP" << std::endl;
                    //     _dir = direction::UP;
                    // }
                    // else
                        _shouldMove = false;
                }
            }
        }
        if (i.x == _snake[0].x && i.y == _snake[0].y && i.repr == 'C')
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
        _shouldMove = true;
    }
    if (event._name == GUI::IDisplayModule::bindingType_t::DOWN) {
        if (_dir == direction::UP || _dir == direction::DOWN)
            return;
        _dir = direction::DOWN;
        _shouldMove = true;
    }
    if (event._name == GUI::IDisplayModule::bindingType_t::LEFT) {
        if (_dir == direction::RIGHT || _dir == direction::LEFT)
            return;
        _dir = direction::LEFT;
        _shouldMove = true;
    }
    if (event._name == GUI::IDisplayModule::bindingType_t::RIGHT) {
        if (_dir == direction::LEFT || _dir == direction::RIGHT)
            return;
        _dir = direction::RIGHT;
        _shouldMove = true;
    }
}

void Game::Nibbler::eatApple()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};

    if (_snake[0].x == _apple[0].x && _snake[0].y == _apple[0].y) {
        _snake.push_back({GUI::IDisplayModule::color_t::GREEN, green, 'c',
            _snake[_snake.size() - 1].x, _snake[_snake.size() - 1].y, "", 0});
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
    _pixels = getPixels();
    if (!checkEvent(events)) {
        return false;
    }
    if (checkCollision()) {
        return false;
    }
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

std::vector<GUI::IDisplayModule::pixel_t> Game::Nibbler::getPixels()
{
    std::vector<GUI::IDisplayModule::pixel_t> pixels;
    pixels.insert(pixels.end(), _snake.begin(), _snake.end());
    pixels.insert(pixels.end(), _wall.begin(), _wall.end());
    pixels.insert(pixels.end(), _apple.begin(), _apple.end());
    return pixels;
}

std::vector<std::string> Game::Nibbler::getSounds()
{
    std::vector<std::string> sounds;
    return sounds;
}
