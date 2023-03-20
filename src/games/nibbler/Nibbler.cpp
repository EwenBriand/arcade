/*
** EPITECH PROJECT, 2022
** oop
** File description:
** Nibbler.cpp
*/

#include "Nibbler.hpp"
#include <random>

extern "C" {
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
        for (unsigned int i = 0; i < 50; i++) {
            _wall.push_back(setPixel(GUI::IDisplayModule::color_t::WHITE, {0, 0, 0}, 'M', i, 0));
            _wall.push_back(setPixel(GUI::IDisplayModule::color_t::WHITE, {0, 0, 0}, 'M', i, 50));
            _wall.push_back(setPixel(GUI::IDisplayModule::color_t::WHITE, {0, 0, 0}, 'M', 0, i));
            _wall.push_back(setPixel(GUI::IDisplayModule::color_t::WHITE, {0, 0, 0}, 'M', 50, i));
        }
    }

    void Game::Nibbler::buildSnake()
    {
        _snake.push_back(setPixel(GUI::IDisplayModule::color_t::GREEN, {0, 0, 0}, 'C', 49, 49));
        _snake.push_back(setPixel(GUI::IDisplayModule::color_t::GREEN, {0, 0, 0}, 'C', 48, 49));
        _snake.push_back(setPixel(GUI::IDisplayModule::color_t::GREEN, {0, 0, 0}, 'C', 47, 49));
        _snake.push_back(setPixel(GUI::IDisplayModule::color_t::GREEN, {0, 0, 0}, 'S', 46, 49));
    }

    void Game::Nibbler::generateApple()
    {
        unsigned int random = rand() % 49 + 1;

        for (auto &i : _snake) {
            if (i.x == random && i.y == random) {
                random = rand() % 49 + 1;
                i = _snake[0];
            }
        }
        _apple.push_back(setPixel(GUI::IDisplayModule::color_t::RED, {0, 0, 0}, 'A', random, random));
    }

    void Game::Nibbler::moveSnake()
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

    bool Game::Nibbler::checkCollision()
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

    bool Game::Nibbler::checkEvent(GUI::IDisplayModule::event_t &event)
    {
        if (event._name == GUI::IDisplayModule::bindingType_t::QUIT)
            return false;
        if (event._name == GUI::IDisplayModule::bindingType_t::UP || event._name == GUI::IDisplayModule::bindingType_t::DOWN || event._name == GUI::IDisplayModule::bindingType_t::LEFT || event._name == GUI::IDisplayModule::bindingType_t::RIGHT)
            changeDirection(event);
        return true;
    }

    bool Game::Nibbler::processFrame(std::vector<GUI::IDisplayModule::event_t> events)
    {
        for (auto &event : events) {
            if (!checkEvent(event))
                return false;
        }
        moveSnake();
        if (checkCollision())
            return false;
        generateApple();
        return true;
    }

    GUI::IDisplayModule::mapSpecs_t Game::Nibbler::getMapSpecs()
    {
        return _mapSpecs;
    }

    std::vector<GUI::IDisplayModule::text_t> Game::Nibbler::getTexts()
    {
        return _texts;
    }

    std::vector<std::string> Game::Nibbler::getSounds()
    {
        return _sounds;
    }

    Game::IGameModule *entrypoint()
    {
        return new Game::Nibbler();
    }
}
