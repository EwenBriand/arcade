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

extern "C"
{
    GUI::IDisplayModule *entry_point()
    {
        return new GUI::Ncurse();
    };
}

GUI::Ncurse::Ncurse()
{
    std::cout << "Creating openWindow..." << std::endl;
    _mapspecs = {0, 0, 0, 0};
}

GUI::Ncurse::~Ncurse()
{
}

void GUI::Ncurse::setUnits(const int &pxpu)
{
    _units = pxpu;
}

int GUI::Ncurse::getUnits() const
{
    return _units;
}

void GUI::Ncurse::setMapSpecs(mapSpecs_t mapspecs)
{
    _mapspecs.pixh = mapspecs.pixh;
    _mapspecs.pixw = mapspecs.pixw;
    _mapspecs.posx = mapspecs.posx;
    _mapspecs.posy = mapspecs.posy;
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
        case KEY_ENTER: event._name = GUI::IDisplayModule::ENTER; break;
        case 27: event._name = GUI::IDisplayModule::QUIT; break;
        default:
            event._name = GUI::IDisplayModule::KEYCODE;
            event._ivalues = std::vector<int>(1, touch);
            break;
    }

    events.push_back(event);
    return events;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void GUI::Ncurse::loadSound(const std::string &label, const std::string &path)
{
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void GUI::Ncurse::playSound(const std::string &label, const bool &loop)
{
}

void GUI::Ncurse::setWindowSize(const int &x, const int &y)
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            _map[i + _mapspecs.posx][j + _mapspecs.posy] = {
                GUI::IDisplayModule::WHITE, {}, ' ', i, j, "", 0};

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++)
            std::cout << _map[i][j].repr;
        std::cout << std::endl;
    }
    std::cout << _map[0].size() << std::endl;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void GUI::Ncurse::openWindow(const int &w, const int &h)
{
    setWindowSize(w, h);
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

void GUI::Ncurse::draw()
{
    for (auto outer_it = _map.begin(); outer_it != _map.end(); ++outer_it) {
        for (auto inner_it = outer_it->second.begin();
             inner_it != outer_it->second.end(); ++inner_it) {
            attron(COLOR_PAIR(inner_it->second.color));
            mvprintw(
                outer_it->first, inner_it->first, "%c", inner_it->second.repr);
        }
    }
    for (auto i = _texts.begin(); i != _texts.end(); ++i) {
        if (i->second.str.empty())
            continue;
        attron(COLOR_PAIR(i->second.color));
        mvprintw(i->second.y, i->second.x, "%s", i->second.str.c_str());
    }
}

void GUI::Ncurse::updatePixels(std::vector<pixel_t> pixels)
{
    for (int i = 0; i < (int) pixels.size(); i++) {
        _map[pixels[i].x + _mapspecs.posx][pixels[i].y + _mapspecs.posy]
            .color = pixels[i].color;
        _map[pixels[i].x + _mapspecs.posx][pixels[i].y + _mapspecs.posy]
            .deltaRGB = pixels[i].deltaRGB;
        _map[pixels[i].x + _mapspecs.posx][pixels[i].y + _mapspecs.posy].repr =
            pixels[i].repr;
        _map[pixels[i].x + _mapspecs.posx][pixels[i].y + _mapspecs.posy]
            .spritePath = pixels[i].spritePath;
        _map[pixels[i].x + _mapspecs.posx][pixels[i].y + _mapspecs.posy]
            .rotation = pixels[i].rotation;
    }

    for (int i = 0; i < _mapspecs.pixw; i++) {
        for (int j = 0; j < _mapspecs.pixh; j++)
            std::cout << _map[i][j].repr;
        std::cout << std::endl;
    }
    std::cout << _map[0].size() << std::endl;
}

void GUI::Ncurse::setText(std::string label, text_t text)
{
    _texts[label] = text;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void GUI::Ncurse::setSprite(char label, std::string path)
{
}
