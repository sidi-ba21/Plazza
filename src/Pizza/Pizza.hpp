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
                _type = PizzaType::Regina;
                _size = size;
                _time = 2;
                _ingredients.insert(_ingredients.end(),
                Plz::pizza_ingredients[Regina].begin(),
                Plz::pizza_ingredients[Regina].begin());
            };
            ~regina() override = default;
    };

    class margarita : public IPizza {
        public:
            margarita(const PizzaSize &size) {
                _type = PizzaType::Margarita;
                _size = size;
                _time = 1;
                _ingredients.insert(_ingredients.end(),
                Plz::pizza_ingredients[Margarita].begin(),
                Plz::pizza_ingredients[Margarita].begin());
            };
            ~margarita() override = default;
    };

    class americana : public IPizza {
        public:
            americana(const PizzaSize &size) {
                _type = PizzaType::Americana;
                _size = size;
                _time = 2;
                _ingredients.insert(_ingredients.end(),
                Plz::pizza_ingredients[Americana].begin(),
                Plz::pizza_ingredients[Americana].begin());
            };
            ~americana() override = default;
    };

    class fantasia : public IPizza {
        public:
            fantasia(const PizzaSize &size) {
                _type = PizzaType::Fantasia;
                _size = size;
                _time = 4;
                _ingredients.insert(_ingredients.end(),
                Plz::pizza_ingredients[Fantasia].begin(),
                Plz::pizza_ingredients[Fantasia].begin());
            };
            ~fantasia() override = default;
    };

};

#endif /* !PIZZA_HPP_ */
