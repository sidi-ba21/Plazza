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

    std::thread Cook::createCook(mqd_t send, mqd_t receive, mqd_t status, int replaceTime, float multiplier)
    {
        // init cook thread
        std::thread pool(&Cook::cook, send, receive, status, replaceTime, multiplier);

        return pool;
    }

    void Cook::cook(mqd_t send, mqd_t receive, mqd_t status, int replaceTime, float multiplier)
    {
     //   std::cout << "Creating cook" << std::endl;
        std::string cmd, buf, str;
        stock.setReplaceTime(replaceTime);
        while (1) {
            _mutex_msg_send.lock();
            IPC::recv_reception(send, buf);
            cmd = buf;
            _mutex_msg_send.unlock();
            if (cmd.compare("close") == 0) {
                Cook::Communication(cmd, receive);
                break;
            }
            if (cmd.find("status") != std::string::npos) {
                std::string buf("Ingredients Status Kitchens N° " + cmd.substr(6, cmd.length()) + " :");
                auto i = 0;
                for (auto &it : stock.getStock()) {
                    i == 0 ? buf.append("\n\t\tDoe: ") : i == 1 ? buf.append("\n\t\tTomato: ") :
                    i == 2 ? buf.append("\n\t\tGruyere: ") : i == 3 ? buf.append("\n\t\tHam: ") :
                    i == 4 ? buf.append("\n\t\tMushrooms: ") : i == 5 ? buf.append("\n\t\tSteak: ") :
                    i == 6 ? buf.append("\n\t\tEggplant: ") : i == 7 ? buf.append("\n\t\tGoatCheese: ") :
                    i == 8 ? buf.append("\n\t\tChiefLove: ") : 0;
                    buf.append(std::to_string(it));
                    i++;
                }
                std::cout << buf << std::endl;
                continue;
            }
            while (!Cook::pickIngredients(Cook::getCmd(buf)));
            Cook::cookPizza(Cook::getCmd(buf), multiplier);
            Cook::Communication(cmd, receive);
        }
    }

    void Cook::cookPizza(Plz::PizzaType type, float multiplier)
    {
    //    printf("__________cooked %0.f\n", multiplier);
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
//        std::cout << "Sending command: " << msg << std::endl;
        _mutex_msg_receive.lock();
        IPC::send_reception(receive, msg);
        _mutex_msg_receive.unlock();
    }

    void Cook::sendStock(std::string stock, mqd_t status)
    {
        _mutex_msg_receive.lock();
        IPC::send_reception(status, stock);
        _mutex_msg_receive.unlock();
    }
}