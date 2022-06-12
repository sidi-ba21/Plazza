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
#include "../Error.hpp"
#include "encapsMsgQueues.hpp"

    #define PMODE 0666

namespace Plz {

class IPC {
    public:
        static void send_reception(mqd_t fd, const std::string msg);
        static void recv_reception(mqd_t fd, std::string &msg);
        void send_Kitchen(int id, const std::string msg);
        int recv_Kitchen(int id, std::string &msg);
        static void send_Status(mqd_t fd, const std::string msg);
        static void recv_Status(mqd_t fd, std::string &msg);
        void send_Stock(int id, const std::string msg);
        int recv_Stock(int id, std::string &msg);

        IPC() { _nbQueues = 0; };
        ~IPC() { 
            for (int i = 0; i < _nbQueues; i++) {
                _queues.Close(_send[i].second);
                }
            for (int i = 0; i < _nbQueues; i++) {
                _queues.Close(_receive[i].second);
                }
        };
        void createQueue(int idKitchen) {
            std::string file("/plz" + std::to_string(this->_nbQueues + 1) + "SEND");
            mqd_t queue;
            _queues.Unlink(file);
            queue = _queues.Open(file, 1);
            if (queue == -1)
                throw MsQueues("Error: mq_open failed");
            _send.push_back(std::make_pair(idKitchen, queue));
            file.assign("/plz" + std::to_string(this->_nbQueues + 1) + "RECEIVE");
           // std::cout << "IPC open2 : " << file << std::endl;
            _queues.Unlink(file);
            queue = _queues.Open(file, 0);
            if (queue == -1)
                throw MsQueues("Error: mq_open failed");
            _receive.push_back(std::make_pair(idKitchen, queue));
            file.assign("/plz" + std::to_string(this->_nbQueues + 1) + "STATUS");
            _queues.Unlink(file);
            queue = _queues.Open(file, 1);
            if (queue == -1)
                throw MsQueues("Error: mq_open failed");
            _status.push_back(std::make_pair(idKitchen, queue));
            file.assign("/plz" + std::to_string(this->_nbQueues + 1) + "STOCK");
            _queues.Unlink(file);
            queue = _queues.Open(file, 0);
            if (queue == -1)
                throw MsQueues("Error: mq_open failed");
            _stock.push_back(std::make_pair(idKitchen, queue));
            this->_nbQueues++;
        };
    protected:
    private:
        int _nbQueues;
        MsgQueues _queues;
        std::vector<std::pair<int, mqd_t>> _send;
        std::vector<std::pair<int, mqd_t>> _receive;
        std::vector<std::pair<int, mqd_t>> _status;
        std::vector<std::pair<int, mqd_t>> _stock;
        int getQueue(int id, int mode) {
            if (mode == 1) {
                for (std::size_t i = 0; i < _send.size(); i++) {
                    if (_send[i].first == id)
                        return i;
                }
            } else if (mode == 2) {
                for (std::size_t i = 0; i < _receive.size(); i++) {
                    if (_receive[i].first == id)
                        return i;
                }
            } else if (mode == 3) {
                for (std::size_t i = 0; i < _status.size(); i++) {
                    if (_status[i].first == id)
                        return i;
                }
            } else if (mode == 4) {
                for (std::size_t i = 0; i < _stock.size(); i++) {
                    if (_stock[i].first == id)
                        return i;
                }
            }
            throw MsQueues("Error: getQueue failed");
        };
};

}
#endif /* !IPC_HPP_ */
