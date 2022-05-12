/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
    #define PIZZA_HPP_

    #include "IPizza.hpp"

namespace Plz {
    class regina : public IPizza {
        public:
            regina(const PizzaSize &size) {
                _type = PizzaType::REGINA;
                _size = size;
                _time = 2;
                _ingredients.insert(_ingredients.end(),
                Plz::pizza_ingredients[REGINA].begin(),
                Plz::pizza_ingredients[REGINA].begin());
            };
            ~regina() override = default;
    };

    class margarita : public IPizza {
        public:
            margarita(const PizzaSize &size) {
                _type = PizzaType::MARGARITA;
                _size = size;
                _time = 1;
                _ingredients.insert(_ingredients.end(),
                Plz::pizza_ingredients[MARGARITA].begin(),
                Plz::pizza_ingredients[MARGARITA].begin());
            };
            ~margarita() override = default;
    };

    class americana : public IPizza {
        public:
            americana(const PizzaSize &size) {
                _type = PizzaType::AMERICANA;
                _size = size;
                _time = 2;
                _ingredients.insert(_ingredients.end(),
                Plz::pizza_ingredients[AMERICANA].begin(),
                Plz::pizza_ingredients[AMERICANA].begin());
            };
            ~americana() override = default;
    };

    class fantasia : public IPizza {
        public:
            fantasia(const PizzaSize &size) {
                _type = PizzaType::FANTASIA;
                _size = size;
                _time = 4;
                _ingredients.insert(_ingredients.end(),
                Plz::pizza_ingredients[FANTASIA].begin(),
                Plz::pizza_ingredients[FANTASIA].begin());
            };
            ~fantasia() override = default;
    };

};

#endif /* !PIZZA_HPP_ */
