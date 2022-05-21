/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Fridge
*/

#ifndef FRIDGE_HPP_
#define FRIDGE_HPP_

#include "../Pizza/PizzaUtils.hpp"
#include <chrono>
#include <memory>
#include <atomic>
#include <array>

class Fridge {
    public:
        Fridge() {
            this->replace = std::time(nullptr);
        }
        ~Fridge() = default;
        void replaceIngredients() {
            for (int i = 0; i < 9; i++)
                this->_stock[i] += 1;
        };
        void checkReplace() {
            std::time_t tmp = std::time(nullptr);
            if ((tmp - this->replace) > (this->replaceTime / 1000)) {
                this->replaceIngredients();
                this->replace = std::time(nullptr);
            }
        }
        void setReplaceTime(int time) { this->replaceTime = time; };
        bool getIngredient(Plz::PizzaType type) {
            std::vector<Plz::PizzaIngredient> ingredients = this->getPizzaIngredients(type);
            for (auto ingredient : ingredients) {
                if (this->_stock[ingredient] > 0)
                    this->_stock[ingredient] -= 1;
                else
                    return false;
            }
            this->checkReplace();
            return true;
        }

    protected:
    private:
        int replaceTime;
        std::time_t replace;
        std::array<std::atomic<int>, 9> _stock {5, 5, 5, 5, 5, 5, 5, 5, 5};
        std::vector<Plz::PizzaIngredient> getPizzaIngredients(const Plz::PizzaType &type) {
            return Plz::pizza_ingredients[type];
        }

};

#endif /* !FRIDGE_HPP_ */
