/*
** EPITECH PROJECT, 2022
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** main.cpp
*/

#include <dlfcn.h>
#include <iostream>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "src/core/Core.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: ./arcade [library]" << std::endl;
        return 84;
    }
    std::cout << "Loading library..." << std::endl;

    auto core = new CORE::Core(argv[1]);
    core->launchGame();
    delete (core);

    return 0;
}
