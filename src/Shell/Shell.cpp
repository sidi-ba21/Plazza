/*
** EPITECH PROJECT, 2022
** Shell.cpp
** File description:
** Shell loop display
*/

#include "../Plazza/Plazza.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "../Error.hpp"

std::vector<std::string> split(const std::string &str, char delim)
{
    std::vector<std::string> res;
    std::stringstream ss(str);
    std::string tmp;

    while (getline(ss, tmp, delim))
        res.push_back(tmp);
    return res;
}

void Plz::Shell::checkCmd(const std::string &cmd)
{
    auto args = split(cmd, ' ');

    if (args.size() !=3 || pizza_types.find(args[0]) == pizza_types.end()
    || pizza_sizes.find(args[1]) == pizza_sizes.end() || args[2][0] != 'x')
        throw InvalidCmd();
    try {
        int n = std::stoi(args[2].substr(1));
        if (n <= 0)
            throw InvalidCmd();
        for (int i = 0; i < n; i++)
            fill_orders(pizza_types[args[0]], pizza_sizes[args[1]]);
    } catch (...) {
        throw InvalidCmd();
    }
}

void Plz::Shell::getCmds(const std::string &line)
{
    auto all_cmds = split(line, ';');

    for (auto &cmd : all_cmds) {
        std::cout << cmd << std::endl;
        checkCmd(cmd);
    }
}

void Plz::Shell::fill_orders(const PizzaType &type, const PizzaSize &size)
{
    if (type == REGINA)
        _orders.push_back(std::make_shared<regina>(size));
    else if (type == MARGARITA)
        _orders.push_back(std::make_shared<margarita>(size));
    else if (type == AMERICANA)
        _orders.push_back(std::make_shared<americana>(size));
    else if (type == FANTASIA)
        _orders.push_back(std::make_shared<fantasia>(size));
}

void *Plz::shell_run(void *plazza)
{
    Plz::Plazza *plz = (Plz::Plazza *)plazza;
    Plz::Shell _shell;

    while (plz->running) {
        std::cout << "> " << std::flush;
        std::string line;
        if (!std::getline(std::cin, line))
            break;
        if (line.compare("status") == 0)
            std::cout << "status ok" << std::endl;
        else if (line.compare("help") == 0)
            std::cout << "help ok" << std::endl;
        else if (line.compare("exit") == 0)
            plz->running = false;
        else {
            try {
                _shell.getCmds(line);
            } catch (InvalidCmd &e) {
                std::cout << "Invalid command" << std::endl;
            }
        }
    }
    return (NULL);
}