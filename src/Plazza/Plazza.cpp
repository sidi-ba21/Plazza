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

Plz::Plazza::Plazza(char **av)
{
    _multiplier = std::stof(av[1]);
    _cooks = std::stoi(av[2]);
    _regenerationTime = std::stof(av[3]);
    _msg = std::make_unique<IPC>(IPC());
    _kitchens = std::make_shared<std::vector<Kitchen_t>>();
    nbKitchens = std::make_shared<int>(0);
    nbOrders = 0;
    _reception = std::make_unique<Reception>(Reception(_cooks, _regenerationTime, _multiplier));
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
    int idKitchen = 0;

    this->commands.push_back(orders);
    for (int i = 0; i < orders->getSize(); i++) {
        idKitchen = _reception->getLessBusyKitchen(nbKitchens, _msg, _kitchens);
        _kitchens->at(idKitchen).busy++;
        this->_msg->send_Kitchen(_kitchens->at(idKitchen).nb, orders->unpack(i));
    }
}
void Plz::Plazza::updateOrders()
{
    std::string buf;
    int idCmd = 0;
    int CookToFree = 0;

    _reception->manageKitchen(_kitchens, _msg);
    for (std::size_t i = 0; i < _kitchens->size(); i++) {
        for (int j = 0; j < _kitchens->at(i).busy; j++) {
            if (_msg->recv_Kitchen(_kitchens->at(i).nb, buf) > 0) {
                buf = buf.substr(0, buf.length() - 3);
                auto arg = split(buf, ' ');
                auto pizza = decryptMsg(arg);
                idCmd = this->getIdCmd(stoi(arg[2]));
                CookToFree++;
                commands[idCmd]->release(pizza.first, pizza.second);
                _reception->notifyReadyCmds(idCmd, commands);
            }
        }
        if (_kitchens->at(i).busy - CookToFree == 0 && CookToFree != 0)
            _kitchens->at(i).time = std::time(nullptr);
        _kitchens->at(i).busy -= CookToFree;
        CookToFree = 0;
    }
}

void Plz::Plazza::displayStatus(void)
{
    if (_kitchens->size() == 0)
        std::cout << "There are currently no working kitchen" << std::endl;
    for (std::size_t i = 0; i < _kitchens->size(); i++) {
        std::cout << "Kitchen N°" << i << ":" << std::endl
        << "    " << "There are " << _cooks << " cooks in the kitchen" << std::endl
        << "    " << _kitchens->at(i).busy << " of them are busy" << std::endl
        << "    " << _cooks - _kitchens->at(i).busy << " of them are free" << std::endl;
    }
}
