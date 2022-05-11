/*
** EPITECH PROJECT, 2022
** Shell.hpp
** File description:
** shell loop display
*/

#ifndef SHELL_H
#define SHELL_H

#include "enum.hpp"

class Shell {
    public:
        Shell();
        ~Shell();
        void run();
        int getType(){return _type;};
        int getSize(){return _size;};
        int getNumber(){return _number;};
    private:
        int _type;
        int _size;
        int _number;
};

#endif /* !SHELL_H */
