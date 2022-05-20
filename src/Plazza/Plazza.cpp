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
    _regenerationTime = std::stof(av[3]);
}

Plz::Plazza::~Plazza()
{
}

float Plz::Plazza::get_multiplier(void)
{
    return (_multiplier);
}

int Plz::Plazza::get_cooks(void)
{
    return (_cooks);
}

int Plz::Plazza::get_pizza_time(void)
{
    return (_regenerationTime);
}

void Plz::Plazza::loadOrders(std::shared_ptr<Command> orders)
{

}
void Plz::Plazza::updateOrders()
{
}