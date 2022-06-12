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
#include <fstream>

#define RESET_COLOR "\e[m"
#define MAKE_GREEN "\e[32m"

void Plz::saveHistory(const std::string &str);

Plz::Reception::Reception(int nbCooks, int replaceTime, float multiplier)
{
    _nbCooks = nbCooks;
    _replaceTime = replaceTime;
    _multiplier = multiplier;
}

void Plz::Reception::createKitchen(std::shared_ptr<int> idKitchen, std::shared_ptr<IPC> msg, std::shared_ptr<std::vector<Kitchen_t>> kitchens)
{
    pid_t pid;
    // increase by one the number of kitchens
    *idKitchen = *idKitchen + 1;
 //   printf("idKitchen: %d\n", *idKitchen);
//    Kitchen_t newKitchen {*idKitchen, 0, std::time(nullptr), 0, false};
    kitchens->push_back({*idKitchen, 0, std::time(nullptr), 0, false});
    msg->createQueue(*idKitchen);
    pid = _fork.doFork();
    if (pid == 0) {
        try {
            Kitchen kitchen(*idKitchen, _nbCooks, _multiplier, _replaceTime);
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

int Plz::Reception::getLessBusyKitchen(std::shared_ptr<int> idKitchen, std::shared_ptr<IPC> msg, std::shared_ptr<std::vector<Kitchen_t>> kitchens)
{
    int max = _nbCooks * 2 - 1;
    int less = max;

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

void Plz::saveHistory(const std::string &str)
{
    std::ofstream file("history.log", std::ios::app);
    std::time_t time = std::time(0);
    std::tm *now = std::localtime(&time);
    file << now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "  ->\t"
    << str << std::endl;
}

void Plz::Reception::notifyReadyCmds(int idCmd, std::vector<std::shared_ptr<Command>> commands)
{
    if (commands[idCmd]->isDone()) {
        std::cout << MAKE_GREEN << "Command N°" << commands[idCmd]->getId() << ": " << commands[idCmd]->getOrder()
        << " is ready" << RESET_COLOR << std::endl;
        commands.erase(commands.begin() + idCmd);
        saveHistory("Command N°" + std::to_string(commands[idCmd]->getId()) + ": " + commands[idCmd]->getOrder() + " is ready");
    }
}

void Plz::Reception::CloseKitchen(std::shared_ptr<std::vector<Kitchen_t>> kitchens)
{
    int size = kitchens->size() - 1;

    if (size == -1)
        return;
//    printf("Size kitchen: %d\n", size);
    for (; size >= 0; size--)
        if (kitchens->at(size).freeCook == _nbCooks) {
            kitchens->erase(kitchens->begin() + size);
            _fork.waitFork();
        //  std::cout << "closeKitchen" << std::endl;
        }
//    wait(NULL);
}

void Plz::Reception::manageKitchen(std::shared_ptr<std::vector<Kitchen_t>> kitchens, std::shared_ptr<IPC> msg)
{
    std::string buf;

    for (std::size_t i = 0; i < kitchens->size(); i++) {
        std::time_t now = std::time(nullptr);
 //       std::cout << "now " << now << "--------- elapsed " << now - kitchens->at(i).time << " busy " << kitchens->at(i).busy <<
 //       " bool " << kitchens->at(i).isFree << std::endl;
        if (now - kitchens->at(i).time > 5 && !kitchens->at(i).isFree && kitchens->at(i).busy == 0) {
            // do it nbCooks times
         //   std::cout << "it " << i << (" Kitchen N°" + std::to_string(kitchens->at(i).nb) + " send") << std::endl;
            for (int j = 0; j < _nbCooks; j++) {
                msg->send_Kitchen(kitchens->at(i).nb, "close");
                kitchens->at(i).isFree = true;
            }
        }
    }

    for (std::size_t i = 0; i < kitchens->size(); i++) {
        if (kitchens->at(i).busy == 0) {
            if (msg->recv_Kitchen(kitchens->at(i).nb, buf) > 0 && buf.compare("close OK") == 0) {
          //      printf("received kitchen\n");
                kitchens->at(i).freeCook++;
                continue;
            }
        }
    }
    CloseKitchen(kitchens);
}