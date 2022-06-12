/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** fork
*/

#ifndef FORK_HPP_
    #define FORK_HPP_

    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>

class Fork {

    public:
        Fork() = default;
        pid_t doFork();
        pid_t waitFork();
        ~Fork() = default;
};




#endif /* !FORK_HPP_ */
