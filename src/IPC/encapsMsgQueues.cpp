/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** encapsMsgQueues
*/

#include "encapsMsgQueues.hpp"

MsgQueues::MsgQueues()
{
    _attr.mq_maxmsg = 10;
    _attr.mq_msgsize = 100;
}

mqd_t MsgQueues::Open(std::string file, int opt)
{
    if (opt == 1)
        return (mq_open(file.c_str(), O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), &_attr));
    return (mq_open(file.c_str(), O_RDWR | O_CREAT | O_NONBLOCK, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), &_attr));
}

int MsgQueues::Close(mqd_t fd)
{
    return (mq_close(fd));
}

int MsgQueues::Unlink(std::string file)
{
    return (mq_unlink(file.c_str()));
}

int MsgQueues::Send(mqd_t fd, std::string msg)
{
    return (mq_send(fd, msg.c_str(), msg.length() + 1, 0));
}

int MsgQueues::Receive(mqd_t fd, char *buffer)
{
    return (mq_receive(fd, buffer, 100, 0));
}