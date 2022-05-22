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

std::vector<std::string> split(const std::string &str, char delim);

namespace Plz {

    class Plazza {
        public:
            Plazza(char **av);
            ~Plazza() = default;
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
            void displayStatus(void);
        public:
            float _multiplier;
            int _cooks;
            int _regenerationTime;
            int nbOrders;
            int nbKitchens;
            std::shared_ptr<IPC> _msg;
            std::vector<std::shared_ptr<Command>> commands;
            std::unique_ptr<Reception> _reception;
            std::shared_ptr<std::vector<Kitchen_t>> _kitchens;
            int getIdCmd(int idCmd) {
                for (size_t i = 0; i < commands.size(); i++) {
                    if (commands[i]->getId() == idCmd)
                        return i;
                }
                throw std::runtime_error("No command found");
            }
            std::pair<PizzaType, PizzaSize> decryptMsg(std::vector<std::string> arg) {
                return std::make_pair(pizza_types[arg[0]], pizza_sizes[arg[1]]);
            }
    };

};

#endif /* !PLAZZA_H */
