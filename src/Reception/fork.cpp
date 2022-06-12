/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** fork
*/

#include "fork.hpp"

pid_t Fork::doFork()
{
    return (fork());
}

pid_t Fork::waitFork()
{
    return (wait(NULL));
}