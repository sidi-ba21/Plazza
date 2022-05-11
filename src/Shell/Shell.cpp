/*
** EPITECH PROJECT, 2022
** Shell.cpp
** File description:
** Shell loop display
*/

#include "Shell.hpp"

#include <string>
#include <iostream>

Shell::Shell()
{
}

Shell::~Shell()
{
}

void Shell::run()
{
    std::string input;

    std::cout << ">";
    std::cin >> input;
}