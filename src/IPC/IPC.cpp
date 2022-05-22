/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** IPC
*/

#include "IPC.hpp"

void Plz::IPC::send_reception(mqd_t fd, const std::string msg)
{
   // std::cout << "Sending message to reception: " << msg << std::endl;
    if (mq_send(fd, msg.c_str(), msg.length() + 1, 0) == -1)
        throw MsQueues("Error: mq_send failed reception");
}

void Plz::IPC::recv_reception(mqd_t fd, std::string &msg)
{
    char buffer[20];
    int bytes =  0;
    bytes = mq_receive(fd, buffer, 20, 0);

    if (bytes == -1)
        throw MsQueues("Error: mq_receive failed recption");
    if (bytes > 0)
        msg.assign(buffer);
 //   std::cout << "Received message from reception: " << msg << std::endl;
}

void Plz::IPC::send_Kitchen(int id, const std::string msg)
{
    int idqueue = this->getQueue(id, 1);

  //  std::cout << "Sending message to kitchen " << id << ": " << msg << std::endl;
    if (mq_send(_send[idqueue].second, msg.c_str(), msg.length() + 1, 0) == -1)
        throw MsQueues("Error: mq_send failed kitchen");
}

int Plz::IPC::recv_Kitchen(int id, std::string &msg)
{
    int idqueue = this->getQueue(id, 2);
    char buffer[20];
//    std::cout << "IPC recv Kitchen : " << _receive[idqueue].second<< std::endl;
    int bytes = mq_receive(_receive[idqueue].second, buffer, 20, 0);
    if (bytes == -1 && errno != EAGAIN) {
        throw MsQueues("Error: mq_receive failed kitchen");
    }
    if (bytes > 0)
        msg.assign(buffer);
    //std::cout << "Received message from kitchen " << id << ": " << msg << std::endl;
    return (bytes);
}