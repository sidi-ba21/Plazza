/*
** EPITECH PROJECT, 2022
** Plazza.hpp
** File description:
** Plazza
*/

#pragma once

#ifndef PLAZZA_H
    #define PLAZZA_H

    #include "../Pizza/IPizza.hpp"
    #include "../IPC/IPC.hpp"
    #include "../Reception/Reception.hpp"
    #include <iostream>
    #include <vector>
    #include <mutex>

namespace Plz {

    class Plazza {
        public:
            Plazza(int ac, char **av);
            ~Plazza();
            void display();
            void loadOrders(std::shared_ptr<Command>);
            void updateOrders();
            int getNewIdOrders() {
                nbOrders++;
                return nbOrders;
            };
            void eraseNewCommandId(){ this->nbOrders--; };
            float get_multiplier(void);
            int get_cooks(void);
            int get_pizza_time(void);

        public:
            float _multiplier;
            int _cooks;
            int _regenerationTime;
            int nbOrders;
            int nbKitchens;
            std::unique_ptr<IPC> _msg;
            std::vector<std::shared_ptr<Command>> commands;
            void createKitchens();
    };

};

#endif /* !PLAZZA_H */
