/*
** EPITECH PROJECT, 2022
** Shell.hpp
** File description:
** shell loop display
*/

#ifndef SHELL_H
    #define SHELL_H

    #include <memory>
    #include <vector>
    #include "../Pizza/IPizza.hpp"
namespace Plz {

    class Shell {
        public:
            Shell() = default;
            ~Shell() = default;
            void getCmds(const std::string &line);
            void checkCmd(const std::string &cmd);
            void fill_orders(const PizzaType &type, const PizzaSize &size);
            void *shell_run(void *plazza);

        private:
            std::vector<std::shared_ptr<IPizza>> _orders {};
    };

};

#endif /* !SHELL_H */
