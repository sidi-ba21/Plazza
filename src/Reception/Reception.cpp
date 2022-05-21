/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

Plz::Reception::Reception(int nbCooks, int replaceTime, float multiplier)
{
    _nbCooks = nbCooks;
    _replaceTime = replaceTime;
    _multiplier = multiplier;
}

void Plz::Reception::createKitchen(int idKitchen, std::shared_ptr<IPC> msg, std::shared_ptr<std::vector<Kitchen_t>> kitchens)
{
    pid_t pid;
    Kitchen_t tmp {idKitchen, 0, std::time(nullptr), 0, false};
    kitchens->push_back(tmp);
    msg->createQueue(idKitchen);
    pid = fork();
    if (pid == 0) {
        try {
            Kitchen kitchen(idKitchen, _nbCooks, _replaceTime, _multiplier);
            std::_Exit(0);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            std::_Exit(0);
        }
    }
}

int Plz::Reception::getLessBusyKitchen(int idKitchen, std::shared_ptr<IPC> msg, std::shared_ptr<std::vector<Kitchen_t>> kitchens)
{
    int max = _nbCooks * 2 - 1;
    int less = 0;
    bool newKitchen = true;

    for (int i = 0; i < kitchens->size(); i++) {
        if (!kitchens->at(i).isFree && kitchens->at(i).busy < max)
            less = kitchens->at(i).busy;
    }
    for (int i = 0; i < kitchens->size(); i++) {
        if (kitchens->at(i).busy == less) {
            less = i;
            newKitchen = false;
            break;
        }
    }
    if (newKitchen) {
        createKitchen(idKitchen, msg, kitchens);
        less = kitchens->size() - 1;
    }
    return (less);
}
/*
void Plz::Reception::notifyReadyCmds(int idCmd, std::vector<std::shared_ptr<Command>> commands)
{
    if ()
}
*/