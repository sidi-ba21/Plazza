/*
** EPITECH PROJECT, 2022
** Shell.hpp
** File description:
** shell loop display
*/

#pragma once

#ifndef SHELL_H
    #define SHELL_H

    #include <memory>
    #include <utility>
    #include <vector>
    #include "../Plazza/Plazza.hpp"
    #include "../Reception/Reception.hpp"

namespace Plz {

    class Shell {
        public:
            Shell(int ac, char **av) {
                _plazza = std::make_unique<Plz::Plazza>(ac, av);
                 shell_run(); 
            };
            ~Shell() = default;
            void getCmds(const std::string &line);
            void checkCmd(const std::string &cmd, std::shared_ptr<Plz::Command> order);
            void shell_run();

        private:
            std::unique_ptr<Plz::Plazza> _plazza;
    };
};

#endif /* !SHELL_H */
