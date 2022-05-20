/*
** EPITECH PROJECT, 2022
** Shell.cpp
** File description:
** Shell loop display
*/

#include <iostream>
#include <sstream>
#include <algorithm>
#include "../Error.hpp"
#include "Shell.hpp"


std::vector<std::string> split(const std::string &str, char delim)
{
    std::vector<std::string> res;
    std::stringstream ss(str);
    std::string tmp;

    while (getline(ss, tmp, delim))
        res.push_back(tmp);
    return res;
}

void Plz::Shell::checkCmd(const std::string &cmd, std::shared_ptr<Command> order)
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
            order->fill_orders(pizza_types[args[0]], pizza_sizes[args[1]]);
    } catch (...) {
        throw InvalidCmd();
    }
}

void Plz::Shell::getCmds(const std::string &line)
{
    std::shared_ptr<Command> order (new Command(line, _plazza->getNewIdOrders()));
    auto all_cmds = split(line, ';');

    for (auto &cmd : all_cmds) {
        checkCmd(cmd, order);
    }
    std::cout << "\nOrder N°" << order->getId() << " is in preparation" << std::endl;
    _plazza->loadOrders(order);
}

void Plz::Shell::shell_run()
{
    while (1) {
        std::cout << "> " << std::flush;
        std::string line;
        if (!std::getline(std::cin, line))
            break;
        if (line.compare("status") == 0)
            std::cout << "status ok" << std::endl;
        else if (line.compare("help") == 0)
            std::cout << "help ok" << std::endl;
        else if (line.compare("exit") == 0)
            break;
        else {
            try {
                getCmds(line);
            } catch (InvalidCmd &e) {
                std::cout << "Invalid command" << std::endl;
                _plazza->eraseNewCommandId();
            }
        }
    }
}