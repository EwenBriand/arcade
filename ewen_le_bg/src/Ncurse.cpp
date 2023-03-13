/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** Ncurs
*/

#include "Ncurse.hpp"
#include <iostream>
#include <ncurses.h>
#include <ostream>

GUI::Ncurse::Ncurse(unsigned int x, unsigned int y)
{
    for (unsigned int i = 0; i < x; i++)
        for (unsigned int j = 0; j < y; j++)
            if (i == 0 || i == 9 || j == 0 || j == 9)
                _map[i][j] = {GUI::IDisplayModule::WHITE, 'X', i, j};
            else
                _map[i][j] = {GUI::IDisplayModule::WHITE, ' ', i, j};

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++)
            std::cout << _map[i][j].repr;
        std::cout << std::endl;
    }
    std::cout << _map[0].size() << std::endl;
}

GUI::Ncurse::~Ncurse()
{
}

void GUI::Ncurse::openWindow(const int &w, const int &h)
{
    initscr();
    curs_set(0);
    raw();
    start_color();
    // init_pair(id, color back, color char);
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
}

void GUI::Ncurse::closeWindow()
{
    endwin();
}

void GUI::Ncurse::clearScr()
{
    clear();
}

void GUI::Ncurse::draw(const int x, const int y)
{
    int w, h;
    getmaxyx(stdscr, h, w);
    if (w < _map.size() + x || h < _map[0].size() + x) {
        mvprintw(0, 0, "Window too small");
        return;
    }

    for (int i = 0; i < _map.size(); i++)
        for (int j = 0; j < _map[i].size(); j++) {
            attron(COLOR_PAIR(_map[i][j].color));
            mvprintw(i + x, j + y, "%c", _map[i][j].repr);
        }
}

void GUI::Ncurse::updatePixels(std::vector<pixel_t> pixels)
{
    for (int i = 0; i < pixels.size(); i++) {
        _map[pixels[i].x][pixels[i].y].color = pixels[i].color;
        _map[pixels[i].x][pixels[i].y].repr = pixels[i].repr;
    }
}

void GUI::Ncurse::setUnits(const int &pxpu)
{
    _units = pxpu;
}

int GUI::Ncurse::getUnits() const
{
    return _units;
}

std::vector<GUI::IDisplayModule::event_t> GUI::Ncurse::pollEvents()
{
    auto touch = getch();
    std::vector<GUI::IDisplayModule::event_t> events;
    event_t event;
    event.timeStamp = 0;

    switch (touch) {
        case KEY_UP: event._name = GUI::IDisplayModule::UP; break;
        case KEY_DOWN: event._name = GUI::IDisplayModule::DOWN; break;
        case KEY_LEFT: event._name = GUI::IDisplayModule::LEFT; break;
        case KEY_RIGHT: event._name = GUI::IDisplayModule::RIGHT; break;
        case ' ': event._name = GUI::IDisplayModule::SPACE; break;
        case 27: event._name = GUI::IDisplayModule::QUIT; break;
        default:
            event._name = GUI::IDisplayModule::KEYCODE;
            event._ivalues = std::vector<int>(1, touch);
            break;
    }

    events.push_back(event);
    return events;
}

void GUI::Ncurse::playSound(const std::string &id, bool loop)
{
}

void GUI::Ncurse::stopSound(const std::string &id)
{
}

void GUI::Ncurse::setVolume(const int &between_zero_and_100)
{
}

void GUI::Ncurse::setPitch(const float &multiplyer)
{
}

void GUI::Ncurse::setWindowSize(const int &w, const int &h)
{
}

void GUI::Ncurse::drawText(
    const std::string &text, int x, int y, const color_t &color)
{
    attron(COLOR_PAIR(color));
    mvprintw(y, x, "%s", text.c_str());
}
