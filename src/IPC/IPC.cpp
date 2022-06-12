/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** IPC
*/

#include "IPC.hpp"

static MsgQueues static_queues;

void Plz::IPC::send_reception(mqd_t fd, const std::string msg)
{
   // std::cout << "Sending message to reception: " << msg << std::endl;
    if (static_queues.Send(fd, msg) == -1)
        throw MsQueues("Error: mq_send failed reception");
}

void Plz::IPC::recv_reception(mqd_t fd, std::string &msg)
{
    char buffer[100];
    int bytes =  0;
    bytes = static_queues.Receive(fd, buffer);

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
    if (_queues.Send(_send[idqueue].second, msg) == -1)
        throw MsQueues("Error: mq_send failed kitchen");
}

int Plz::IPC::recv_Kitchen(int id, std::string &msg)
{
    int idqueue = this->getQueue(id, 2);
    char buffer[100];
//    std::cout << "IPC recv Kitchen : " << _receive[idqueue].second<< std::endl;
    int bytes = _queues.Receive(_receive[idqueue].second, buffer);
    if (bytes == -1 && errno != EAGAIN) {
        throw MsQueues("Error: mq_receive failed kitchen");
    }
    if (bytes > 0)
        msg.assign(buffer);
    //std::cout << "Received message from kitchen " << id << ": " << msg << std::endl;
    return (bytes);
}

void Plz::IPC::send_Status(mqd_t fd, const std::string msg)
{
    if (static_queues.Send(fd, msg) == -1)
        throw MsQueues("Error: mq_send failed stock");
}

void Plz::IPC::recv_Status(mqd_t fd, std::string &msg)
{
    char buffer[100];
    int bytes =  0;
    bytes = static_queues.Receive(fd, buffer);

    if (bytes == -1)
        throw MsQueues("Error: mq_receive failed stock");
    if (bytes > 0)
        msg.assign(buffer);
}

int Plz::IPC::recv_Stock(int id, std::string &msg)
{
    int idqueue = this->getQueue(id, 4);
    char buffer[100];

    int bytes = _queues.Receive(_status[idqueue].second, buffer);
    if (bytes == -1 && errno != EAGAIN) {
        throw MsQueues("Error: mq_receive failed kitchen");
    }
    if (bytes > 0)
        msg.assign(buffer);
    return (bytes);
}

void Plz::IPC::send_Stock(int id, const std::string msg)
{
    int idqueue = this->getQueue(id, 3);

    if (_queues.Send(_status[idqueue].second, msg) == -1)
        throw MsQueues("Error: mq_send failed status");
}