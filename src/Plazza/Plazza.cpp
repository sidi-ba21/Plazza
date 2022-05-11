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

float Plazza::get_multiplier(void)
{
    return (_multiplier);
}

int Plazza::get_cooks(void)
{
    return (_cooks);
}

int Plazza::get_pizza_time(void)
{
    return (_pizzaTime);
}

void Plazza::run(void)
{
    _shell.run();
}