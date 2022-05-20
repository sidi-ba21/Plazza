/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <memory>
#include <vector>
#include <utility>
#include "../Pizza/Pizza.hpp"

namespace Plz {

    class Command {
        public:
            Command(const std::string &order, int id){
                this->_cmd = order;
                this->_id = id;
            };
            ~Command() = default;
            bool isDone() const {
                if (_orders.empty())
                    return true;
                return false;
            };
            void fill_orders(const PizzaType &type, const PizzaSize &size) {
                if (type == REGINA)
                    _orders.push_back(std::make_unique<regina>(size));
                else if (type == MARGARITA)
                    _orders.push_back(std::make_unique<margarita>(size));
                else if (type == AMERICANA)
                    _orders.push_back(std::make_unique<americana>(size));
                else if (type == FANTASIA)
                    _orders.push_back(std::make_unique<fantasia>(size));
            }
            int getId() const { return _id; };
            int getSize() const { return _orders.size(); };
            std::string getOrder() const { return _cmd; };
            std::string unpack(int i) const {
                if ((std::size_t)i >= _orders.size())
                    return nullptr;
                return pizza_names[_orders[i]->getType()] + " " +
                pizza_str_size[_orders[i]->getSize()] + " " + std::to_string(_id);
            };
            void release(const PizzaType &type, const PizzaSize &size) {
                for (auto it = _orders.begin(); it != _orders.end();) {
                    if ((*it)->getType() == type && (*it)->getSize() == size)
                        it = _orders.erase(it);
                    else
                        ++it;
                }
            }

        private:
            int _id;
            std::vector<std::unique_ptr<IPizza>> _orders;
            std::string _cmd;
    };
}

#endif /* !RECEPTION_HPP_ */
