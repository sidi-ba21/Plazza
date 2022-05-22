/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

#include "../Pizza/IPizza.hpp"
#include "thread_pool.hpp"
#include "../IPC/IPC.hpp"
#include "Fridge.hpp"
#include <memory>
#include <vector>
#include <mutex>
#include <mqueue.h>
#include <atomic>

namespace Plz {

    typedef struct Kitchen_s {
        int nb;
        int busy;
        std::time_t time;
        int freeCook;
        bool isFree;
    } Kitchen_t;

    class Cook {
        public:
            static void cook(mqd_t send, mqd_t receive, int replaceTime, float multiplier);
            static std::thread createCook(mqd_t send, mqd_t receive, int replace, float multiplier);
            static Plz::PizzaType getCmd(const std::string &cmd);
            static bool pickIngredients(Plz::PizzaType);
            static void cookPizza(Plz::PizzaType, float multiplier);
            static void Communication(std::string command, mqd_t receive);
    };

    class Kitchen {
        public:
            void initMsgQueue() {
                std::string file("/plz" + std::to_string(this->_id) + "SEND");
                struct mq_attr attr;
               // std::cout << "IPC open3 : " << file << std::endl;
                attr.mq_maxmsg = 10;
                attr.mq_msgsize = 20;
                _send = mq_open(file.c_str(), O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), &attr);
                if (_send == -1) {
                    throw MsQueues("Error: mq_open failed");
                }
                file.assign("/plz" + std::to_string(this->_id) + "RECEIVE");
               // std::cout << "IPC open4 : " << file << std::endl;
                _receive = mq_open(file.c_str(), O_RDWR | O_CREAT | O_NONBLOCK, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), &attr);
                if (_receive == -1) {
                    throw MsQueues("Error: mq_open failed");
                }
            }
            Kitchen(int id, int nbCooks, float multiplier, int replaceTime) {
                _id = id;
                _nbCooks = nbCooks;
                _multiplier = multiplier;
                nbPizza = 0;
                initMsgQueue();
                for (int i = 0; i < _nbCooks; i++)
                    _pool.push_back(Plz::Cook::createCook(_send, _receive, replaceTime, _multiplier));
                threadPool();
            }
            void threadPool() {
                for (int i = 0; i < _nbCooks; i++)
                    _pool[i].join();
                std::_Exit(0);
            }
            ~Kitchen() = default;
        private:
            int _id;
            int _nbCooks;
            float _multiplier;
            int nbPizza;
            std::vector<std::unique_ptr<IPizza>> _pizza {};
            std::vector<std::thread> _pool;
            mqd_t _send;
            mqd_t _receive;
    };
}

#endif /* !KITCHEN_HPP_ */
