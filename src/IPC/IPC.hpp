/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** IPC
*/

#ifndef IPC_HPP_
    #define IPC_HPP_

#include <vector>
#include <mqueue.h>
#include <time.h>
#include <iostream>

    #define PMODE 0666

namespace Plz {

class IPC {
    public:
        IPC() { _nbQueues = 0; };
        ~IPC() { 
            for (int i = 0; i < _nbQueues; i++) {
                mq_close(_send[i].second);
                }
            for (int i = 0; i < _nbQueues; i++) {
                mq_close(_receive[i].second);
                }
        };
        void createQueue(int idKitchen) {
            mqd_t queue;
            struct mq_attr attr;
            std::string file("/tmp/plz_send" + std::to_string(this->_nbQueues + 1));
            
            attr.mq_maxmsg = 10;
            attr.mq_msgsize = 20;
            mq_unlink(file.c_str());
            queue = mq_open(file.c_str(), O_RDWR | O_CREAT, PMODE, &attr);
            if (queue == -1)
                throw std::runtime_error("Error: mq_open failed");
            _send.push_back(std::make_pair(idKitchen, queue));
            file.assign("/tmp/plz_receive" + std::to_string(this->_nbQueues + 1));
            mq_unlink(file.c_str());
            queue = mq_open(file.c_str(), O_RDWR | O_CREAT | O_NONBLOCK, PMODE, &attr);
            if (queue == -1)
                throw std::runtime_error("Error: mq_open failed");
            _receive.push_back(std::make_pair(idKitchen, queue));
            this->_nbQueues++;
        };

    protected:
    private:
        int _nbQueues;
        std::vector<std::pair<int, mqd_t>> _send;
        std::vector<std::pair<int, mqd_t>> _receive;
        int getQueue(int id);
};

}
#endif /* !IPC_HPP_ */
