/*
** EPITECH PROJECT, 2022
** my project
** File description:
** main
*/

#include <array>
#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <stddef.h>
#include <thread>
#include "IDisplayModule.hpp"
#include "my.h"
#include "src/Ncurse.hpp"

void game_loop(GUI::IDisplayModule *display,
    std::array<std::array<char, 10>, 10> map,
    GUI::IDisplayModule::pixel_t *player)
{
    bool a = true;
    std::vector<GUI::IDisplayModule::event_t> event;
    GUI::IDisplayModule::pixel_t old = {
        player->color, player->repr, player->x, player->y};
    std::vector<GUI::IDisplayModule::pixel_t> updated_pix;
    int time = 0;

    while (a) {
        display->clearScr();
        updated_pix.clear();
        updated_pix.push_back(old);
        updated_pix.push_back(*player);
        display->updatePixels(updated_pix);
        display->draw(1, 1);
        display->drawText(std::string("Hello World!" + std::to_string(time)),
            10, 10, GUI::IDisplayModule::WHITE);
        display->drawText(
            std::string("Hello World!"), 10, 11, GUI::IDisplayModule::YELLOW);
        display->drawText(
            std::string("Hello World!"), 10, 12, GUI::IDisplayModule::RED);
        display->drawText(
            std::string("Hello World!"), 10, 13, GUI::IDisplayModule::GREEN);
        display->drawText(
            std::string("Hello World!"), 10, 14, GUI::IDisplayModule::BLUE);
        display->drawText(
            std::string("Hello World!"), 10, 15, GUI::IDisplayModule::MAGENTA);
        display->drawText(
            std::string("Hello World!"), 10, 16, GUI::IDisplayModule::BLACK);
        display->drawText(
            std::string("Hello World!"), 10, 17, GUI::IDisplayModule::CYAN);

        event = display->pollEvents();
        for (int i = 0; i < event.size(); i++) {
            if (event[i]._name == GUI::IDisplayModule::LEFT
                && map[player->x][player->y - 1] != 'X') {
                old.x = player->x;
                old.y = player->y;
                player->y -= 1;
                old.repr = ' ';
            }
            if (event[i]._name == GUI::IDisplayModule::RIGHT
                && map[player->x][player->y + 1] != 'X') {
                old.x = player->x;
                old.y = player->y;
                player->y += 1;
                old.repr = ' ';
            }
            if (event[i]._name == GUI::IDisplayModule::UP
                && map[player->x - 1][player->y] != 'X') {
                old.x = player->x;
                old.y = player->y;
                player->x -= 1;
                old.repr = ' ';
            }
            if (event[i]._name == GUI::IDisplayModule::DOWN
                && map[player->x + 1][player->y] != 'X') {
                old.x = player->x;
                old.y = player->y;
                player->x += 1;
                old.repr = ' ';
            }
            if (event[i]._name == GUI::IDisplayModule::QUIT)
                a = false;
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::this_thread::sleep_until(std::chrono::system_clock::now()
            + std::chrono::milliseconds(1000));
        time++;
    }
}

void the_game(void)
{
    GUI::IDisplayModule *display = new GUI::Ncurse(10, 10);
    std::array<std::array<char, 10>, 10> map;
    GUI::IDisplayModule::pixel_t player = {0, 'O', 1, 1};

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (i == 0 || i == 9 || j == 0 || j == 9)
                map[i][j] = 'X';
            else
                map[i][j] = ' ';

    display->openWindow(0, 0);
    game_loop(display, map, &player);
    display->closeWindow();
}

int main(int argc, char **argv, char **env)
{
    if (env[0] == NULL)
        return ERROR_VALUE;

    the_game();

    return END_VALUE;
}
