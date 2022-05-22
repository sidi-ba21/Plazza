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

//    std::cout << "size orders : " << orders->getSize() << std::endl;
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
//        _msg->send_Kitchen(_kitchens->at(i).nb, "status");
        for (int j = 0; j < _kitchens->at(i).busy; j++) {
            if (_msg->recv_Kitchen(_kitchens->at(i).nb, buf) > 0) {
//                buf = buf.substr(0, buf.length() - 3);
//                std::cout << "buf : " << buf << std::endl;
                auto arg = split(buf, ' ');
                auto pizza = decryptMsg(arg);
                idCmd = this->getIdCmd(stoi(arg[2]));
                CookToFree++;
                // print command[idCmd] size
//                std::cout << "Command " << idCmd << " size : " << commands[idCmd]->getSize() << std::endl;
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
    std::string buf;
    std:: string str;

    if (_kitchens->size() == 0) {
        std::cout << "There are currently no working kitchen" << std::endl;
        return;
    }
    for (std::size_t i = 0; i < _kitchens->size(); i++) {
       // if (_msg->recv_Stock(_kitchens->at(i).nb, buf) > 0) {
       //     std::cout << buf << std::endl;
//               auto arg = split(buf, ';');
//               str = "Doe: " + arg[0] + ", Tomato: " + arg[1] +
//               ", Gruyere: " + arg[2] + ", Ham: " + arg[3] + ", Mushrooms: " + arg[4] +
//               ", Steak: " + arg[5] + ", Eggplant: " + arg[6] + ", GoatCheese: " + arg[7] +
//               ", ChiefLove: " + arg[8];
       //     break;
       // }
        auto busy = _kitchens->at(i).busy >= _cooks ? _cooks : _kitchens->at(i).busy;
        auto free = _cooks - _kitchens->at(i).busy > 0 ? _cooks - _kitchens->at(i).busy : 0;
        auto pizza = _kitchens->at(i).busy > _cooks ? _kitchens->at(i).busy - _cooks : 0;
        std::cout << "Kitchen N°" << i << ":" << std::endl
        << "    " << "Pizza waiting to be cooked :" <<  pizza << std::endl
        << "    " << "There are " << _cooks << " cooks in the kitchen" << std::endl
        << "    " << busy << " of them are busy" << std::endl
        << "    " << free << " of them are free" << std::endl;
       // << "    " << "Fridge status: " << str << std::endl;
    }
}
