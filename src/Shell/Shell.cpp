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
    if (args.size() !=3)
        throw InvalidCmd();
    if (args[0] != )
}

void Plz::Shell::getCmds(const std::string &line)
{
    auto all_cmds = split(line, ';');

    for (auto &cmd : all_cmds) {
        std::cout << cmd << std::endl;
        check_cmd(cmd);
    }
}

/*
void *shell_run(void *plazza)
{
    Plazza *plz = (Plazza *)plazza;

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
            std::cout << "Invalid command. try 'help'" << std::endl;
        }
    }
    return (NULL);
}*/