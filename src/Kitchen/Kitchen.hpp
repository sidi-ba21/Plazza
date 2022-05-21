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

    class Cook {
        public:
            static void createCook(mqd_t send, mqd_t receive, int replace, float multiplier);
            static Plz::PizzaType getCmd(const std::string &cmd);
            static bool pickIngredients(Plz::PizzaType);
            static void cookPizza(Plz::PizzaType, float multiplier);
            static void Communication(std::string command, mqd_t receive);
    };

    class Kitchen {
        public:
            void initMsgQueue() {
                struct mq_attr attr;
                std::string file("/tmp/plz_send" + std::to_string(this->_id));

                attr.mq_maxmsg = 10;
                attr.mq_msgsize = 20;
                _send = mq_open(file.c_str(), O_RDWR | O_CREAT, 0666, &attr);
                if (_send == -1)
                    throw std::runtime_error("Error: mq_open failed");
                file.assign("/tmp/plz_receive" + std::to_string(this->_id));
                _receive = mq_open(file.c_str(), O_RDWR | O_CREAT | O_NONBLOCK, 0666, &attr);
                if (_receive == -1)
                    throw std::runtime_error("Error: mq_open failed");
            }
            Kitchen(int id, int nbCooks, float multiplier, int replaceTime) {
                _id = id;
                _nbCooks = nbCooks;
                _multiplier = multiplier;
                nbPizza = 0;
                initMsgQueue();
                for (int i = 0; i < _nbCooks; i++)
                    _pool.pushPool(Plz::Cook::createCook, _send, _receive, replaceTime, _multiplier);
                _pool.joinAll();
            }
            ~Kitchen() = default;
        private:
            int _id;
            int _nbCooks;
            float _multiplier;
            int nbPizza;
            std::vector<std::unique_ptr<IPizza>> _pizza {};
            ThreadPool _pool;
            mqd_t _send;
            mqd_t _receive;
    };
}

#endif /* !KITCHEN_HPP_ */
