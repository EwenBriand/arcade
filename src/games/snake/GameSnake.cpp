/*
** EPITECH PROJECT, 2022
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** GameSnake.cpp
*/

#include "GameSnake.hpp"

extern "C"
{
    Game::IGameModule *entry_point()
    {
        return new Game::GameSnake();
    };
}

Game::GameSnake::GameSnake()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};
    _dir = direction::LEFT;
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 's', 25, 25});
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'c', 26, 25});
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'c', 27, 25});
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'c', 28, 25});
    initWall();
    initApple();
}

void Game::GameSnake::initWall()
{
    GUI::IDisplayModule::deltaRGB_t white = {255, 255, 255};
    for (int i = 5; i < 51; i++) {
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 5});
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 50});
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', 5, i});
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', 50, i});
    }
}

void Game::GameSnake::initApple()
{
    GUI::IDisplayModule::deltaRGB_t red = {255, 0, 0};
    int random = rand() % 49 + 1;
    for (auto &i : _snake) {
        if (i.x == random && i.y == random) {
            random = rand() % 49 + 1;
            i = _snake[0];
        }
    }
    _apple.push_back(
        {GUI::IDisplayModule::color_t::RED, red, 'a', random, random});
}

std::vector<GUI::IDisplayModule::pixel_t> Game::GameSnake::getPixels()
{
    std::vector<GUI::IDisplayModule::pixel_t> pixels;
    pixels.insert(pixels.end(), _snake.begin(), _snake.end());
    pixels.insert(pixels.end(), _wall.begin(), _wall.end());
    pixels.insert(pixels.end(), _apple.begin(), _apple.end());
    return pixels;
}

std::vector<GUI::IDisplayModule::text_t> Game::GameSnake::getTexts()
{
    _texts.push_back({"Score: " + std::to_string(_score), 71, 0, 18,
        GUI::IDisplayModule::color_t::WHITE});
    return _texts;
}

std::vector<std::string> Game::GameSnake::getSounds()
{
    std::vector<std::string> sounds;
    return sounds;
}

GUI::IDisplayModule::mapSpecs_t Game::GameSnake::getMapSpecs()
{
    return _mapspecs;
}

bool Game::GameSnake::processFrame(
    std::vector<GUI::IDisplayModule::event_t> events)
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

void Game::GameSnake::changeDirection(GUI::IDisplayModule::event_t &event)
{
    if (event._name == GUI::IDisplayModule::bindingType_t::UP) {
        if (_dir == direction::DOWN || _dir == direction::UP)
            return;
        _texts.push_back(
            {"UP", 71, 5, 18, GUI::IDisplayModule::color_t::WHITE});
        _dir = direction::UP;
    }
    if (event._name == GUI::IDisplayModule::bindingType_t::DOWN) {
        if (_dir == direction::UP || _dir == direction::DOWN)
            return;
        _texts.push_back(
            {"DOWN", 71, 5, 18, GUI::IDisplayModule::color_t::WHITE});
        _dir = direction::DOWN;
    }
    if (event._name == GUI::IDisplayModule::bindingType_t::LEFT) {
        if (_dir == direction::RIGHT || _dir == direction::LEFT)
            return;
        _texts.push_back(
            {"LEFT", 71, 5, 18, GUI::IDisplayModule::color_t::WHITE});
        _dir = direction::LEFT;
    }
    if (event._name == GUI::IDisplayModule::bindingType_t::RIGHT) {
        if (_dir == direction::LEFT || _dir == direction::RIGHT)
            return;
        _texts.push_back(
            {"RIGHT", 71, 5, 18, GUI::IDisplayModule::color_t::WHITE});
        _dir = direction::RIGHT;
    }
}

bool Game::GameSnake::checkEvent(
    std::vector<GUI::IDisplayModule::event_t> events)
{
    for (auto &event : events) {
        if (event._name == GUI::IDisplayModule::bindingType_t::QUIT)
            return false;
        changeDirection(event);
    }
    return true;
}

void Game::GameSnake::moveSnake()
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

bool Game::GameSnake::checkCollision()
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

void Game::GameSnake::eatApple()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};
    if (_snake[0].x == _apple[0].x && _snake[0].y == _apple[0].y) {
        _snake.push_back({GUI::IDisplayModule::color_t::GREEN, green, 'c',
            _snake[_snake.size() - 1].x, _snake[_snake.size() - 1].y});
        _apple.clear();
        initApple();
        _score += 100;
    }
}
