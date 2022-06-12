/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** encapsMsgQueues
*/

#ifndef ENCAPSMSGQUEUES_HPP_
    #define ENCAPSMSGQUEUES_HPP_

    #include <mqueue.h>
    #include <iostream>

class MsgQueues {
    public:
        MsgQueues();
        ~MsgQueues() = default;
        mqd_t Open(std::string, int);
        int Close(mqd_t);
        int Unlink(std::string);
        int Send(mqd_t, std::string);
        int Receive(mqd_t, char *);
    private:
        struct mq_attr _attr;
};

#endif /* !ENCAPSMSGQUEUES_HPP_ */
