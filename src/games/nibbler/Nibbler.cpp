/*
** EPITECH PROJECT, 2022
** oop
** File description:
** Nibbler.cpp
*/

#include "Nibbler.hpp"
#include <random>
#include <iostream>
#include <fstream>

extern "C" {
    Game::IGameModule *entry_point()
    {
        return new Game::Nibbler();
    };
}

Game::Nibbler::Nibbler()
{
    srand(time(NULL));
    std::cout << "Creating Nibbler..." << std::endl;
    _dir = direction::LEFT;
    buildSnake();
    buildMap();
    _shouldMove = true;
    _score = 0;
    _mapspecs = {60, 60, 10, 10};
    _texts.push_back({"Score: " + std::to_string(_score), 71, 0, 18,
        GUI::IDisplayModule::color_t::WHITE});
}

int **Game::Nibbler::getMapElemPosFromFile(std::string path, char elem)
{
    std::string map_str;
    std::ifstream map_file(path);
    int rows = 0, cols = 0, num_elem = 0, index = 0;
    int **pos = nullptr;

    if (map_file.is_open()) {
        map_str = std::string((std::istreambuf_iterator<char>(map_file)), std::istreambuf_iterator<char>());
        map_file.close();
    } else {
        std::cout << "Error: could not open map file." << std::endl;
        return pos;
    }

    for (int i = 0; i < map_str.length(); i++) {
        if (map_str[i] == '\n') {
            rows++;
            cols = 0;
        } else {
            cols++;
            if (map_str[i] == elem) {
                num_elem++;
            }
        }
    }

    pos = new int*[num_elem + 1];
    for (int i = 0; i < num_elem + 1; i++) {
        pos[i] = new int[2];
    }

    for (int i = 0; i < map_str.length(); i++) {
        if (map_str[i] == elem) {
            pos[index][0] = rows - 1;
            pos[index][1] = cols - 1;
            index++;
        }
        if (map_str[i] == '\n') {
            rows--;
            cols = 0;
        } else {
            cols++;
        }
    }
    pos[index] = nullptr;
    return pos;
}

void Game::Nibbler::buildMap()
{
    GUI::IDisplayModule::deltaRGB_t white = {255, 255, 255};
    GUI::IDisplayModule::deltaRGB_t red = {255, 0, 0};

    for (int i = 5; i < 24; i++) {
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 5, "", 0});
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', i, 23, "", 0});
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', 5, i, "", 0});
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', 23, i, "", 0});
    }
    _wallpos = getMapElemPosFromFile("assets/map/nibbler_basic.txt", '#');
    if (_wallpos == nullptr) {
        return;
    }
    for (int i = 0; _wallpos[i] != nullptr; i++) {
        _wall.push_back(
            {GUI::IDisplayModule::color_t::WHITE, white, 'M', _wallpos[i][0] + 7, _wallpos[i][1] + 7, "", 0});
    }
    _applepos = getMapElemPosFromFile("assets/map/nibbler_basic.txt", 'A');
    if (_applepos == nullptr) {
        return;
    }
    for (int i = 0; _applepos[i] != nullptr; i++) {
        _apple.push_back(
            {GUI::IDisplayModule::color_t::RED, red, 'A', _applepos[i][0] + 7, _applepos[i][1] + 7, "", 0});
    }
}

void Game::Nibbler::buildSnake()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};
    _dir = direction::LEFT;
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'S', 8, 22, "", 0});
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'C', 9, 22, "", 0});
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'C', 10, 22, "", 0});
    _snake.push_back(
        {GUI::IDisplayModule::color_t::GREEN, green, 'C', 11, 22, "", 0});
}

void Game::Nibbler::moveSnake()
{
    GUI::IDisplayModule::deltaRGB_t green = {0, 255, 0};

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

bool Game::Nibbler::checkCollision()
{
    int x = (_dir == direction::LEFT) ? -1 : _dir == direction::RIGHT ? 1 : 0;
    int y = (_dir == direction::UP) ? -1 : _dir == direction::DOWN ? 1 : 0;

    for (auto &i : _pixels) {
        if (i.x == _snake[0].x + x && i.y == _snake[0].y + y && i.repr == 'M') {
            if (_dir == direction::UP || _dir == direction::DOWN) {
                for (auto &j : _pixels) {
                    if (j.x == _snake[0].x - 1 && j.y == _snake[0].y && j.repr == 'M') {
                        _dir = direction::RIGHT;
                        _shouldMove = true;
                        return false;
                    }
                    else if (j.x == _snake[0].x + 1 && j.y == _snake[0].y && j.repr == 'M') {
                        _dir = direction::LEFT;
                        _shouldMove = true;
                        return false;
                    }
                }
                _shouldMove = false;
            } else if (_dir == direction::LEFT || _dir == direction::RIGHT) {
                for (auto &j : _pixels) {
                    if (j.x == _snake[0].x && j.y == _snake[0].y - 1 && j.repr == 'M') {
                        _dir = direction::DOWN;
                        _shouldMove = true;
                        return false;
                    }
                    else if (j.x == _snake[0].x && j.y == _snake[0].y + 1 && j.repr == 'M') {
                        _dir = direction::UP;
                        _shouldMove = true;
                        return false;
                    }
                }
                _shouldMove = false;
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

    for (auto &i : _pixels) {
        if (i.x == _snake[0].x && i.y == _snake[0].y && i.repr == 'A') {
            _snake.push_back({GUI::IDisplayModule::color_t::GREEN, green, 'c',
                _snake[_snake.size() - 1].x, _snake[_snake.size() - 1].y, "", 0});
            _score += 100;
            for (auto it = _apple.begin(); it != _apple.end(); ++it) {
                if (it->x == _snake[0].x && it->y == _snake[0].y) {
                    _apple.erase(it);
                    break;
                }
            }
        }
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
    if (!checkEvent(events))
        return false;
    if (checkCollision())
        return false;
    if (_apple.empty())
        return false;
    if (_shouldMove)
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
    return {0, 20, 10, 10};
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
