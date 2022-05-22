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

bool Plz::Reception::setLessBusy(int *less, std::shared_ptr<std::vector<Kitchen_t>> kitchens)
{
    for (std::size_t i = 0; i < kitchens->size(); i++) {
        if (kitchens->at(i).busy == *less) {
            *less = i;
            return (false);
        }
    }
    return (true);
}

int Plz::Reception::getLessBusyKitchen(int idKitchen, std::shared_ptr<IPC> msg, std::shared_ptr<std::vector<Kitchen_t>> kitchens)
{
    int max = _nbCooks * 2 - 1;
    int less = max;
    bool newKitchen = true;

    for (std::size_t i = 0; i < kitchens->size(); i++) {
        if (!kitchens->at(i).isFree && kitchens->at(i).busy < max)
            less = kitchens->at(i).busy;
    }
    if (setLessBusy(&less, kitchens)) {
        createKitchen(idKitchen, msg, kitchens);
        less = kitchens->size() - 1;
    }
    return (less);
}

void Plz::Reception::notifyReadyCmds(int idCmd, std::vector<std::shared_ptr<Command>> commands)
{
    if (commands[idCmd]->isDone()) {
        std::cout << "Command N°" << commands[idCmd]->getId() << ": " << commands[idCmd]->getOrder()
        << " is done" << std::endl;
        commands.erase(commands.begin() + idCmd);
    }
}

void Plz::Reception::CloseKitchen(std::shared_ptr<std::vector<Kitchen_t>> kitchens)
{
    int size = kitchens->size() - 1;

    if (size == -1)
        return;
    for (; size >= 0; size--)
        if (kitchens->at(size).freeCook == _nbCooks)
            kitchens->erase(kitchens->begin() + size);
}

void Plz::Reception::manageKitchen(std::shared_ptr<std::vector<Kitchen_t>> kitchens, std::shared_ptr<IPC> msg)
{
    std::string buf;

    for (std::size_t i = 0; i < kitchens->size(); i++) {
        std::time_t now = std::time(nullptr);
        if (now - kitchens->at(i).time > 5 && !kitchens->at(i).isFree && kitchens->at(i).busy == 0) {
            // do it nbCooks times
            for (int j = 0; j < _nbCooks; j++) {
                msg->send_Kitchen(kitchens->at(i).nb, "close");
                kitchens->at(i).isFree = true;
            }
        }
    }

    for (std::size_t i = 0; i < kitchens->size(); i++) {
        if (kitchens->at(i).busy == 0) {
            if (msg->recv_Kitchen(kitchens->at(i).nb, buf) > 0 && buf.compare("close OK") == 0) {
                kitchens->at(i).freeCook++;
                continue;
            }
        }
    }
    CloseKitchen(kitchens);
}