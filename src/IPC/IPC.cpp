/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** IPC
*/

#include "IPC.hpp"

void Plz::IPC::send_reception(mqd_t fd, const std::string msg)
{
    std::cout << "Sending message to reception: " << msg << std::endl;
    if (mq_send(fd, msg.c_str(), msg.length() + 1, 0) == -1)
        throw MsQueues("Error: mq_send failed reception");
}

void Plz::IPC::recv_reception(mqd_t fd, std::string &msg)
{
    char buffer[20];
    std::cout << "IPC recv reception : " << fd << std::endl;
    int ret = mq_receive(fd, buffer, 20, 0);
    if (ret == -1)
        throw MsQueues("Error: mq_receive failed recption");
    if (ret > 0)
        msg.assign(buffer);
}

void Plz::IPC::send_Kitchen(int id, const std::string msg)
{
    int idqueue = this->getQueue(id, 1);

    std::cout << "Sending message to kitchen " << id << ": " << msg << std::endl;
    if (mq_send(_send[idqueue].second, msg.c_str(), msg.length() + 1, 0) == -1)
        throw MsQueues("Error: mq_send failed kitchen");
}

int Plz::IPC::recv_Kitchen(int id, std::string &msg)
{
    int idqueue = this->getQueue(id, 2);
    char buffer[20];
//    std::cout << "IPC recv Kitchen : " << _receive[idqueue].second<< std::endl;
    int r = mq_receive(_receive[idqueue].second, buffer, 20, 0);
    if (r == -1 && errno != EAGAIN) {
        throw MsQueues("Error: mq_receive failed kitchen");
    }
    if (r > 0)
        msg.assign(buffer);
    return (r);
}