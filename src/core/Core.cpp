/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** Core
*/

#include "Core.hpp"
#include <array>
#include <chrono>
#include <dlfcn.h>
#include <iostream>
#include <ncurses.h>
#include <stddef.h>
#include <thread>
#include<unistd.h>


CORE::Core::Core(std::string filename)
{
    void *handle = dlopen(filename.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return;
    }

    entry_point_display entry_point_func =
        (entry_point_display) dlsym(handle, "entry_point");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << dlsym_error << std::endl;
        dlclose(handle);
        return;
    }

    _displays = entry_point_func();
    std::stringstream ss(filename);

    while (std::getline(ss, _ndisplay, '/')) {}
    std::cout << "  " << _ndisplay << std::endl;
    dlclose(handle);
}

CORE::Core::~Core()
{
}

void CORE::Core::setDisplays(std::string ndisplay)
{
    void *handle = dlopen(ndisplay.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return;
    }

    entry_point_display entry_point_func =
        (entry_point_display) dlsym(handle, "entry_point");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << dlsym_error << std::endl;
        dlclose(handle);
        return;
    }

    _displays->closeWindow();
    _displays = entry_point_func();
    _displays->openWindow(100, 100);

    std::stringstream ss(ndisplay);
    while (std::getline(ss, _ndisplay, '/')) {}
    std::cout << "  " << _ndisplay << std::endl;
    dlclose(handle);
    mvprintw(10, 10, "hello world");
    _displays->closeWindow();
    // _displays->clearScr();
    exit(0);
}

void CORE::Core::setGame(std::string ngame)
{
    void *handle = dlopen(ngame.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return;
    }

    entry_point_game entry_point_func =
        (entry_point_game) dlsym(handle, "entry_point");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << dlsym_error << std::endl;
        dlclose(handle);
        return;
    }

    _game = entry_point_func();
    _game->processFrame({});
    std::stringstream ss(ngame);
    while (std::getline(ss, _ngame, '/')) {}
    // dlclose(handle);
}

std::vector<std::filesystem::path> CORE::Core::find_so_files(
    const std::string &path)
{
    std::vector<std::filesystem::path> result;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".so") {
            result.push_back(entry.path());
        }
    }
    return result;
}

void CORE::Core::display_menu()
{
    _so_game = find_so_files("./lib/game");
    _so_graph = find_so_files("./lib/graph");
    std::cout << _ndisplay << std::endl;
    std::cout << lib_graph[0] << std::endl;

    std::cout << "launched" << std::endl;
    _displays->openWindow(100, 100);
    _displays->setMapSpecs({10, 10, 10, 10});
    auto status = true;
    while (status) {
        _displays->clearScr();

        for (auto i = 0; i < lib_game.size(); ++i)
            if (lib_game[i] == _ngame)
                _displays->setText(lib_game[i],
                    {lib_game[i], 120, 25 + 2 * i, 1,
                        GUI::IDisplayModule::RED});
            else
                _displays->setText(lib_game[i],
                    {lib_game[i], 120, 25 + 2 * i, 1,
                        GUI::IDisplayModule::WHITE});

        for (auto i = 0; i < lib_graph.size(); ++i)
            if (lib_graph[i] == _ndisplay)
                _displays->setText(lib_graph[i],
                    {lib_graph[i], 65, 25 + 2 * i, 1,
                        GUI::IDisplayModule::RED});
            else
                _displays->setText(lib_graph[i],
                    {lib_graph[i], 65, 25 + 2 * i, 1,
                        GUI::IDisplayModule::WHITE});

        _displays->draw();

    for (int i = 0; i < (int) event.size(); i++) {
        if (event[i]._name == GUI::IDisplayModule::QUIT)
            status = false;

        if (event[i]._name == GUI::IDisplayModule::DOWN) {
            if (_act_col == 0 && act_d != (int) _so_graph.size() - 1) {
                setDisplays(_so_graph[act_d + 1].string());
                // _ndisplay = _so_graph[act_d + 1].filename().string();
            } else if (act_g != (int) _so_game.size() - 1)
                setGame(_so_game[act_g + 1].string());
            // _ngame = _so_game[act_g + 1].filename().string();
        }

        if (event[i]._name == GUI::IDisplayModule::UP) {
            if (_act_col == 0 && act_d != 0) {
                setDisplays(_so_graph[act_d - 1].string());
                // _ndisplay = _so_graph[act_d - 1].filename().string();
            } else if (act_g != 0) {
                setGame(_so_game[act_g - 1].string());
                // _ngame = _so_game[act_g - 1].filename().string();
            }
        }
        std::this_thread::sleep_until(std::chrono::system_clock::now()
            + std::chrono::milliseconds(1000));
    }
    std::cout << "running" << std::endl;

    _displays->closeWindow();
}
