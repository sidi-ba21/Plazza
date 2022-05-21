/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** IPC
*/

#include "IPC.hpp"

void Plz::IPC::send_reception(mqd_t fd, const std::string msg)
{
    if (mq_send(fd, msg.c_str(), msg.length() + 1, 0) == -1)
        throw std::runtime_error("Error: mq_send failed");
}

void Plz::IPC::recv_reception(mqd_t fd, std::string &msg)
{
    char buffer[20];

    if (mq_receive(fd, buffer, 20, 0) == -1)
        throw std::runtime_error("Error: mq_receive failed");
    msg.assign(buffer);
}

void Plz::IPC::send_Kitchen(int id, const std::string msg)
{
    int idqueue = this->getQueue(id, 1);

    if (mq_send(_send[idqueue].second, msg.c_str(), msg.length() + 1, 0) == -1)
        throw std::runtime_error("Error: mq_send failed");
}

int Plz::IPC::recv_Kitchen(int id, std::string &msg)
{
    int idqueue = this->getQueue(id, 2);
    char buffer[20];
    int r = mq_receive(_receive[idqueue].second, buffer, 20, 0);

    if (r == -1) {
        throw std::runtime_error("Error: mq_receive failed");
        return (-1);
    }
    r > 0 ? msg.assign(buffer) : 0;
    return (r);
}