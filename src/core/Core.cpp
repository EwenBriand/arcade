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

void CORE::Core::setDisplays(std::string &ndisplay)
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

    _displays = entry_point_func();
    std::stringstream ss(ndisplay);
    while (std::getline(ss, _ndisplay, '/')) {}
    dlclose(handle);
}

void CORE::Core::setGame(std::string &ngame)
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
    std::stringstream ss(ngame);
    while (std::getline(ss, _ngame, '/')) {}
    dlclose(handle);
}

std::vector<std::string> CORE::Core::find_so_files(const std::string &path)
{
    std::vector<std::string> result;
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        // Check if the file has the extension ".so"
        if (entry.path().extension() == ".so") {
            result.push_back(entry.path().filename().string());
        }
    }
    return result;
}

void CORE::Core::launchGame()
{
    std::vector<GUI::IDisplayModule::event_t> event;
    std::vector<std::string> lib_game = find_so_files("./lib/game");
    std::vector<std::string> lib_graph = find_so_files("./lib/graph");
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

        event = _displays->pollEvents();
        for (int i = 0; i < event.size(); i++) {
            if (event[i]._name == GUI::IDisplayModule::QUIT)
                status = false;
        }
        std::this_thread::sleep_until(std::chrono::system_clock::now()
            + std::chrono::milliseconds(1000));
    }
    std::cout << "running" << std::endl;

    _displays->closeWindow();
}
