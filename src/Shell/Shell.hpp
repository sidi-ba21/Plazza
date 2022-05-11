/*
** EPITECH PROJECT, 2022
** Shell.hpp
** File description:
** shell loop display
*/

#ifndef SHELL_H
#define SHELL_H

class Shell {
    public:
        Shell();
        ~Shell();
        void run();
    private:
        int _type;
        int _size;
        int _number;
};

#endif /* !SHELL_H */
