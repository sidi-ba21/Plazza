/*
** EPITECH PROJECT, 2022
** Plazza.cpp
** File description:
** Plazza
*/

#include "Plazza.hpp"
#include <thread>
#include <algorithm>
#include <ctime>

Plz::Plazza::Plazza(int ac, char **av)
{
    _multiplier = std::stof(av[1]);
    _cooks = std::stoi(av[2]);
    _pizzaTime = std::stoi(av[3]);
}

Plz::Plazza::~Plazza()
{
}

void Plz::Plazza::run(void)
{
    running = true;
}