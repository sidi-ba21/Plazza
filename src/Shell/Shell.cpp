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
#include <sys/select.h>
#include <unistd.h>


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

int Plz::Shell::userActivity()
{
    fd_set readfds;
    struct timeval _wait{0, 100};
    std::string line;
    int activity = 0;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    if ((activity = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &_wait)) == -1) {
        std::perror("select");
        exit(84);
    } else if (activity) {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            if (!std::getline(std::cin, line))
                return (-1);
            _line.assign(line);
            return (1);
        }
    } else
        _plazza->updateOrders();
    return (0);
}

void Plz::Shell::shell_run()
{
    int r = 0;

    while (1) {
        r = userActivity();
        if (r == -1)
            break;
        if (r) {
            if (_line.compare("status") == 0)
                std::cout << "status ok" << std::endl;
            else if (_line.compare("help") == 0)
                std::cout << "help ok" << std::endl;
            else if (_line.compare("exit") == 0)
                break;
            else {
                try {
                    getCmds(_line);
                } catch (InvalidCmd &e) {
                    std::cout << "Invalid command" << std::endl;
                    _plazza->eraseNewCommandId();
                }
            }
        }
    }
}