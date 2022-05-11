/*
** EPITECH PROJECT, 2022
** Plazza.hpp
** File description:
** Plazza
*/

#include "../Shell/Shell.hpp"

#ifndef PLAZZA_H
#define PLAZZA_H

class Plazza {
    public:
        Plazza(int ac, char **av);
        ~Plazza();
        float get_multiplier(void);
        int get_cooks(void);
        int get_pizza_time(void);
        void run();
    protected:
    private:
        float _multiplier = 1;
        int _cooks = 0;
        int _pizzaTime = 0;
        Shell _shell;
};

#endif /* !PLAZZA_H */
