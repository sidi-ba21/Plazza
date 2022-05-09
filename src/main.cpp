/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** main
*/

#include "Error.hpp"
#include "Usage.hpp"
#include <iostream>

static bool check_arguments(int ac, char **av)
{
    try {
        if (ac != 4)
            throw ErrorUsage();
        if (std::stoi(av[1]) <= 0)
            throw ErrorMultiplier();
        if (std::stoi(av[2]) <= 0)
            throw ErrorCooks();
        if (std::stoi(av[3]) <= 0)
            throw ErrorTime();
    } catch (Error &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

int main(int ac, char **av)
{
    if (ac == 2 && av[1] == std::string("-h")) {
        std::cout << HELP_USAGE << std::endl;
        return 0;
    }
    if (!check_arguments(ac, av))
        return 84;
    return 0;
}