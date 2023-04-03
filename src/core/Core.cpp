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
#include <unistd.h>

CORE::Core::Core(std::string filename)
{
    _so_game = find_so_files("./lib/game");
    _so_graph = find_so_files("./lib/graph");

    _handle_d = dlopen(filename.c_str(), RTLD_LAZY);
    if (!_handle_d) {
        std::cerr << dlerror() << std::endl;
        throw Error("Error while opening the library");
        return;
    }

    entry_point_display entry_point_func =
        (entry_point_display) dlsym(_handle_d, "entry_point");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << dlsym_error << std::endl;
        dlclose(_handle_d);
        throw Error("Error while opening the library");
        return;
    }

    _displays = entry_point_func();
    std::stringstream ss(filename);

    while (std::getline(ss, _ndisplay, '/')) {}
    std::cout << "  " << _ndisplay << std::endl;
    _displays->setUnits(10);

    for (auto i = 0; i < (int) _so_graph.size(); ++i)
        if (_so_graph[i].filename().string() == _ndisplay)
            _act_d = i;
}

CORE::Core::~Core()
{
    if (_handle_d != nullptr) {
        delete _displays;
        dlclose(_handle_d);
    }
    if (_handle_g != nullptr) {
        delete _game;
        dlclose(_handle_g);
    }
}

void CORE::Core::setDisplays(std::string ndisplay)
{
    void *handle = dlopen(ndisplay.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        throw Error("Error while opening the library");
        return;
    }

    _displays->closeWindow();
    delete _displays;
    dlclose(_handle_d);
    _handle_d = handle;

    entry_point_display entry_point_func =
        (entry_point_display) dlsym(_handle_d, "entry_point");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << dlsym_error << std::endl;
        dlclose(_handle_d);
        throw Error("Error while opening the library");
        return;
    }

    _displays = entry_point_func();
    _displays->openWindow(400, 400);

    std::stringstream ss(ndisplay);
    while (std::getline(ss, _ndisplay, '/')) {}
    std::cout << "  " << _ndisplay << std::endl;
    _displays->setUnits(10);
}

void CORE::Core::setGame(std::string ngame)
{
    void *handle = dlopen(ngame.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        throw Error("Error while opening the library");
        return;
    }

    if (_handle_g != nullptr) {
        delete _game;
        dlclose(_handle_g);
    }
    _handle_g = handle;

    entry_point_game entry_point_func =
        (entry_point_game) dlsym(_handle_g, "entry_point");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << dlsym_error << std::endl;
        dlclose(_handle_g);
        throw Error("Error while opening the library");
        return;
    }

    _game = entry_point_func();
    std::stringstream ss(ngame);
    while (std::getline(ss, _ngame, '/')) {}
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

void CORE::Core::addIfNotPresent(std::string str)
{
    bool isPresent = false;
    for (std::string s : _texts)
        if (s == str) {
            isPresent = true;
            break;
        }

    if (!isPresent)
        _texts.push_back(str);
}

void CORE::Core::display_menu()
{
    _displays->clearScr();
    GUI::IDisplayModule::text_t text;

    for (auto i = 0; i < (int) _so_game.size(); ++i) {
        addIfNotPresent(_so_game[i].filename().string());
        if (_so_game[i].filename().string() == _ngame)
            text = {_so_game[i].filename(), 120, 25 + 2 * i, 1,
                GUI::IDisplayModule::RED};
        else
            text = {_so_game[i].filename().string(), 120, 25 + 2 * i, 1,
                GUI::IDisplayModule::WHITE};
        _displays->setText(_so_game[i].filename().string(), text);
    }
    for (auto i = 0; i < (int) _so_graph.size(); ++i) {
        addIfNotPresent(_so_graph[i].filename().string());
        if (_so_graph[i].filename().string() == _ndisplay)
            text = {_so_graph[i].filename(), 65, 25 + 2 * i, 1,
                GUI::IDisplayModule::RED};
        else
            text = {_so_graph[i].filename().string(), 65, 25 + 2 * i, 1,
                GUI::IDisplayModule::WHITE};
        _displays->setText(_so_graph[i].filename().string(), text);
    }
    _displays->draw();
}

void CORE::Core::clear_text()
{
    for (auto i : _texts) {
        _displays->setText(i, {"", 0, 0, 1, GUI::IDisplayModule::WHITE});
    }
}

int CORE::Core::start_game(bool &status)
{
    auto event = _displays->pollEvents();
    auto text = _game->getTexts();

    clear_text();
    _displays->clearScr();
    _displays->setMapSpecs(_game->getMapSpecs());

    while (_game->processFrame(event)) {
        _displays->clearScr();

        _displays->updatePixels(_game->getPixels());
        text = _game->getTexts();
        for (auto i = 0; i < (int) text.size(); ++i) {
            _displays->setText("label" + ('0' + i), text[i]);
            addIfNotPresent("label" + ('0' + i));
        }

        _displays->draw();
        event = _displays->pollEvents();
        for (int i = 0; i < (int) event.size(); i++) {
            if (event[i]._ivalues.size() > 0 && event[i]._ivalues[0] == 'm') {
                _displays->clearScr();
                clear_text();
                return 1;
            }
            if (event[i]._ivalues.size() > 0 && event[i]._ivalues[0] == 'z') {
                if (_act_d + 1 == (int) _so_graph.size())
                    _act_d = 0;
                else
                    _act_d++;
                setDisplays(_so_graph[_act_d].string());
            }
            if (event[i]._ivalues.size() > 0 && event[i]._ivalues[0] == 't') {
                if (_act_g + 1 == (int) _so_game.size())
                    _act_g = 0;
                else
                    _act_g++;
                return 2;
            }
            if (event[i]._ivalues.size() > 0 && event[i]._ivalues[0] == 'r') {
                return 2;
            }
            if (event[i]._ivalues.size() > 0 && event[i]._ivalues[0] == 'q') {
                status = false;
                return 0;
            }
        }
        std::this_thread::sleep_until(
            std::chrono::system_clock::now() + std::chrono::milliseconds(200));
    }
    _displays->clearScr();
    clear_text();
    return 0;
}

void CORE::Core::event_menu(bool &status)
{
    auto res = 0;
    auto event = _displays->pollEvents();

    for (int i = 0; i < (int) event.size(); i++) {
        if (event[i]._name == GUI::IDisplayModule::QUIT)
            status = false;

        if (event[i]._name == GUI::IDisplayModule::ENTER) {
            while ((res = start_game(status)) == 2) {
                setGame(_so_game[_act_g].string());
            }
            if ((res = start_game(status)) == 0)
                setGame("lib/game/" + _ngame);
            event = _displays->pollEvents();
            break;
        }

        if (event[i]._name == GUI::IDisplayModule::DOWN) {
            if (_act_col == 0 && _act_d != (int) _so_graph.size() - 1)
                setDisplays(_so_graph[(_act_d++) + 1].string());
            else if (_act_g != (int) _so_game.size() - 1)
                setGame(_so_game[(_act_g++) + 1].string());
        }

        if (event[i]._name == GUI::IDisplayModule::UP) {
            if (_act_col == 0 && _act_d != 0) {
                setDisplays(_so_graph[(_act_d--) - 1].string());

            } else if (_act_g != 0) {
                setGame(_so_game[(_act_g--) - 1].string());
            }
        }
        if (event[i]._name == GUI::IDisplayModule::LEFT && _act_col == 1)
            _act_col = 0;

        if (event[i]._name == GUI::IDisplayModule::RIGHT && _act_col == 0)
            _act_col = 1;
    }
}

void CORE::Core::launchGame()
{
    _so_game = find_so_files("./lib/game");
    _so_graph = find_so_files("./lib/graph");
    if (_so_game.size() == 0 || _so_graph.size() == 0) {
        std::cerr << "No lib found" << std::endl;
        throw Error("No lib found");
        return;
    }
    _ngame = _so_game[0].filename().string();
    setGame(_so_game[0].string());
    std::cout << _ndisplay << std::endl;
    std::cout << _so_graph[0].string() << std::endl;
    std::cout << _ndisplay << std::endl;

    std::cout << "launched" << std::endl;
    _displays->openWindow(400, 400);
    _displays->setMapSpecs({10, 10, 10, 10});
    auto status = true;
    while (status) {
        display_menu();
        event_menu(status);
        std::this_thread::sleep_until(
            std::chrono::system_clock::now() + std::chrono::milliseconds(200));
    }
    std::cout << "running" << std::endl;

    _displays->closeWindow();
}

// sdl input PT
// finir + relancer le jeux PT
// tout les texts ne sont pas refresh
