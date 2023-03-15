/*
** EPITECH PROJECT, 2022
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** GameSnake.cpp
*/

#include "GameSnake.hpp"

GameSnake::GameSnake()
{
    _dir = direction::LEFT;
    _snake.push_back({GUI::IDisplayModule::color_t::GREEN, 's', 25, 25});
    _snake.push_back({GUI::IDisplayModule::color_t::GREEN, 'c', 26, 25});
    _snake.push_back({GUI::IDisplayModule::color_t::GREEN, 'c', 27, 25});
    _snake.push_back({GUI::IDisplayModule::color_t::GREEN, 'c', 28, 25});
    initWall();
    initApple();
}

void GameSnake::initWall()
{
    for (unsigned int i = 0; i < 50; i++) {
        _wall.push_back({GUI::IDisplayModule::color_t::WHITE, 'M', i, 0});
        _wall.push_back({GUI::IDisplayModule::color_t::WHITE, 'M', i, 50});
        _wall.push_back({GUI::IDisplayModule::color_t::WHITE, 'M', 0, i});
        _wall.push_back({GUI::IDisplayModule::color_t::WHITE, 'M', 50, i});
    }
}

void GameSnake::initApple()
{
    unsigned int random = rand() % 49 + 1;
    for (auto &i : _snake) {
        if (i.x == random && i.y == random) {
            random = rand() % 49 + 1;
            i = _snake[0];
        }
    }
    _apple.push_back({GUI::IDisplayModule::color_t::RED, 'a', random, random});
}

bool GameSnake::run(GUI::IDisplayModule &gui, bool &stopGame)
{
    if (!checkEvent(gui))
        return false;
    moveSnake();
    if (checkCollision())
        return false;
    eatApple();
    gui.updatePixels(_apple);
    gui.updatePixels(_snake);
    gui.updatePixels(_wall);
}

void GameSnake::changeDirection(GUI::IDisplayModule::event_t &event)
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

bool GameSnake::checkEvent(GUI::IDisplayModule &gui)
{
    for (auto &event : gui.pollEvents()) {
        if (event._name == GUI::IDisplayModule::bindingType_t::QUIT)
            return false;
        changeDirection(event);
    }
    return true;
}

void GameSnake::moveSnake()
{
    _snake[0].repr = 'c';
    if (_dir == direction::UP)
        _snake.insert(_snake.begin(), {GUI::IDisplayModule::color_t::GREEN, 's', _snake[0].x, _snake[0].y + 1});
    if (_dir == direction::DOWN)
        _snake.insert(_snake.begin(), {GUI::IDisplayModule::color_t::GREEN, 's', _snake[0].x, _snake[0].y - 1});
    if (_dir == direction::LEFT)
        _snake.insert(_snake.begin(), {GUI::IDisplayModule::color_t::GREEN, 's', _snake[0].x - 1, _snake[0].y});
    if (_dir == direction::RIGHT)
        _snake.insert(_snake.begin(), {GUI::IDisplayModule::color_t::GREEN, 's', _snake[0].x + 1, _snake[0].y});
    _snake.pop_back();
}

bool GameSnake::checkCollision()
{
    for (auto &wall : _wall) {
        if (wall.x == _snake[0].x && wall.y == _snake[0].y)
            return true;
    }
    for (unsigned int i = 1; i < _snake.size(); i++) {
        if (_snake[0].x == _snake[i].x && _snake[0].y == _snake[i].y)
            return true;
    }
    return false;
}

void GameSnake::eatApple()
{
    if (_snake[0].x == _apple[0].x && _snake[0].y == _apple[0].y) {
        _snake.push_back({GUI::IDisplayModule::color_t::GREEN, 'c', _snake[_snake.size() - 1].x, _snake[_snake.size() - 1].y});
        _apple.clear();
        initApple();
        _score += 100;
    }
}