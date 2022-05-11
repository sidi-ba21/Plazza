/*
** EPITECH PROJECT, 2022
** Plazza.cpp
** File description:
** Plazza
*/

#include <string>

#include "Plazza.hpp"

Plazza::Plazza(int ac, char **av)
{
    _multiplier = std::stof(av[1]);
    _cooks = std::stoi(av[2]);
    _pizzaTime = std::stoi(av[3]);
}

Plazza::~Plazza()
{
}

void Plazza::run(void)
{
    _shell.run();
}