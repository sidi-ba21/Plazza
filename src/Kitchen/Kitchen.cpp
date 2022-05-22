/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

namespace Plz {
    Fridge stock;
    static std::mutex _mutex_msg_send;
    static std::mutex _mutex_msg_receive;
    static std::mutex _mutex_ing;

    void Cook::createCook(mqd_t send, mqd_t receive, int replaceTime, float multiplier)
    {
        std::string command, buffer;
        stock.setReplaceTime(replaceTime);
        printf("_______________Cook created\n");
        while (1) {
            _mutex_msg_send.lock();
            IPC::recv_reception(send, buffer);
            command = buffer;
            _mutex_msg_receive.unlock();
            if (command.compare("close") == 0) {
                Cook::Communication(command, receive);
                break;
            }
            while (!Cook::pickIngredients(Cook::getCmd(buffer)));
            Cook::cookPizza(Cook::getCmd(buffer), multiplier);
            Cook::Communication(command, receive);
        }
    }

    void Cook::cookPizza(Plz::PizzaType type, float multiplier)
    {
        int time = Plz::pizza_time[type] * multiplier;
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }

    bool Cook::pickIngredients(Plz::PizzaType type)
    {
        bool pick = false;

        _mutex_ing.lock();
        stock.checkReplace();
        pick = stock.getIngredient(type);
        _mutex_ing.unlock();
        return (pick);
    }

    Plz::PizzaType Cook::getCmd(const std::string &cmd)
    {
        std::string type = cmd.substr(0, cmd.find(' '));
        return Plz::pizza_types[type];
    }

    void Cook::Communication(std::string command, mqd_t receive)
    {
        std::string msg(command + " OK");
        _mutex_msg_receive.lock();
        IPC::send_reception(receive, msg);
        _mutex_msg_receive.unlock();
    }
}