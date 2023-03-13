/*
** EPITECH PROJECT, 2022
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** main.cpp
*/

#include <dlfcn.h>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: ./test [library]" << std::endl;
        return 84;
    }
    std::cout << "Loading library..." << std::endl;
    void *handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return 84;
    }
    std::cout << "Library loaded" << std::endl;
    dlclose(handle);
    return 0;
}