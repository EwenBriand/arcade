/*
** EPITECH PROJECT, 2022
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** GameSnake.cpp
*/

#include "GameSnake.hpp"

GameSnake::GameSnake()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 128, 0};
    _dir = direction::LEFT;
    _snake.push_back({GUI::IDisplayModule::color_t::GREEN, green, 's', 25, 25});
    _snake.push_back({GUI::IDisplayModule::color_t::GREEN, green, 'c', 26, 25});
    _snake.push_back({GUI::IDisplayModule::color_t::GREEN, green, 'c', 27, 25});
    _snake.push_back({GUI::IDisplayModule::color_t::GREEN, green, 'c', 28, 25});
    initWall();
    initApple();
}

void GameSnake::initWall()
{
    GUI::IDisplayModule::deltaRGB_t white = {0, 0, 0};
    for (int i = 0; i < 50; i++) {
        _wall.push_back({GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 0});
        _wall.push_back({GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 50});
        _wall.push_back({GUI::IDisplayModule::color_t::WHITE, white, 'M', 0, i});
        _wall.push_back({GUI::IDisplayModule::color_t::WHITE, white, 'M', 50, i});
    }
}

void GameSnake::initApple()
{
    GUI::IDisplayModule::deltaRGB_t red = {256, 0, 0};
    int random = rand() % 49 + 1;
    for (auto &i : _snake) {
        if (i.x == random && i.y == random) {
            random = rand() % 49 + 1;
            i = _snake[0];
        }
    }
    _apple.push_back({GUI::IDisplayModule::color_t::RED, red, 'a', random, random});
}

std::vector<GUI::IDisplayModule::pixel_t> GameSnake::getPixels()
{
    std::vector<GUI::IDisplayModule::pixel_t> pixels;
    pixels.insert(pixels.end(), _snake.begin(), _snake.end());
    pixels.insert(pixels.end(), _wall.begin(), _wall.end());
    pixels.insert(pixels.end(), _apple.begin(), _apple.end());
    return pixels;
}

std::vector<GUI::IDisplayModule::text_t> GameSnake::getTexts()
{
    std::vector<GUI::IDisplayModule::text_t> texts;
    // GUI::IDisplayModule::text_t text;
    // text._text = "Score: " + std::to_string(_score);
    // text._x = 0;
    // text._y = 0;
    // texts.push_back(text);
    return texts;
}

std::vector<std::string> GameSnake::getSounds()
{
    std::vector<std::string> sounds;
    return sounds;
}

GUI::IDisplayModule::mapSpecs_t GameSnake::getMapSpecs()
{
    GUI::IDisplayModule::mapSpecs_t specs;
    return specs;
}

bool GameSnake::processFrame(std::vector<GUI::IDisplayModule::event_t> events)
{
    if (!checkEvent(events))
        return false;
    moveSnake();
    if (checkCollision())
        return false;
    eatApple();
    return true;
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

bool GameSnake::checkEvent(std::vector<GUI::IDisplayModule::event_t> events)
{
    for (auto &event : events) {
        if (event._name == GUI::IDisplayModule::bindingType_t::QUIT)
            return false;
        changeDirection(event);
    }
    return true;
}

void GameSnake::moveSnake()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 128, 0};
    _snake[0].repr = 'c';
    if (_dir == direction::UP)
        _snake.insert(_snake.begin(), {GUI::IDisplayModule::color_t::GREEN, green, 's', _snake[0].x, _snake[0].y + 1});
    if (_dir == direction::DOWN)
        _snake.insert(_snake.begin(), {GUI::IDisplayModule::color_t::GREEN, green, 's', _snake[0].x, _snake[0].y - 1});
    if (_dir == direction::LEFT)
        _snake.insert(_snake.begin(), {GUI::IDisplayModule::color_t::GREEN, green, 's', _snake[0].x - 1, _snake[0].y});
    if (_dir == direction::RIGHT)
        _snake.insert(_snake.begin(), {GUI::IDisplayModule::color_t::GREEN, green, 's', _snake[0].x + 1, _snake[0].y});
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
    GUI::IDisplayModule::deltaRGB_t green = {0, 128, 0};
    if (_snake[0].x == _apple[0].x && _snake[0].y == _apple[0].y) {
        _snake.push_back({GUI::IDisplayModule::color_t::GREEN, green, 'c', _snake[_snake.size() - 1].x, _snake[_snake.size() - 1].y});
        _apple.clear();
        initApple();
        _score += 100;
    }
}