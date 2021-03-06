/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#pragma once

#ifndef RECEPTION_HPP_
    #define RECEPTION_HPP_

#include "../IPC/IPC.hpp"
#include "../Kitchen/Kitchen.hpp"
#include "Command.hpp"
#include "fork.hpp"

namespace Plz {

    void saveHistory(const std::string &str);

    class Reception {

        public:
            Reception(int nbCooks, int replaceTime, float multiplier);
            ~Reception() = default;
            void createKitchen(std::shared_ptr<int> idKitchen, std::shared_ptr<IPC>, std::shared_ptr<std::vector<Kitchen_t>>);
            int getLessBusyKitchen(std::shared_ptr<int> idKitchen, std::shared_ptr<IPC>, std::shared_ptr<std::vector<Kitchen_t>>);
            bool setLessBusy(int *less, std::shared_ptr<std::vector<Kitchen_t>> kitchens);
            void notifyReadyCmds(int idCmd, std::vector<std::shared_ptr<Command>>);
            void manageKitchen(std::shared_ptr<std::vector<Kitchen_t>>, std::shared_ptr<IPC>);
            void CloseKitchen(std::shared_ptr<std::vector<Kitchen_t>>);

        protected:
        private:
            int _nbCooks;
            int _replaceTime;
            float _multiplier;
            Fork _fork;

    };
}

#endif /* !RECEPTION_HPP_ */
