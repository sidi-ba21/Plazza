/*
** EPITECH PROJECT, 2022
** Plazza.hpp
** File description:
** Plazza
*/


#ifndef PLAZZA_H
    #define PLAZZA_H

    #include "../Shell/Shell.hpp"
    #include <iostream>
    #include <vector>
    #include <mutex>

namespace Plz {

    class Plazza {
        public:
            Plazza(int ac, char **av);
            ~Plazza();
            void run();
            void display();
            void loadOrders();
            void updateOrders();
            bool readyOrder();
            float get_multiplier(void);
            int get_cooks(void);
            int get_pizza_time(void);


        public:
            int _multiplier;
            int _cooks;
            int _pizzaTime;
            bool running;
            pthread_t _thread;
    };

};

#endif /* !PLAZZA_H */
