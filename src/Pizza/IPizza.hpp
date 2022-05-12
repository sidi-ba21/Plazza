/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Pizza
*/

#ifndef IPIZZA_HPP_
    #define IPIZZA_HPP_

    #include <vector>
    #include <map>
    #include <iostream>

namespace Plz {

    class IPizza
    {
        public:
            virtual ~IPizza() = default;
            const PizzaType &getType() const {
                return _type;
            }
            const PizzaSize &getSize() const {
                return _size;
            }
            const int &getTime() const {
                return _time;
            }
            const std::vector<PizzaIngredient> &getIngredients() const {
                return _ingredients;
            }
        protected:
            PizzaType _type;
            PizzaSize _size;
            int _time;
            std::vector<PizzaIngredient> _ingredients {};
    };

    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    enum PizzaIngredient {
        Doe = 0,
        Tomato = 1,
        Gruyere = 2,
        Ham = 3,
        Mushrooms = 4,
        Steak = 5,
        Eggplant = 6,
        GoatCheese = 7,
        ChiefLove = 8,
    };

    std::map<PizzaType, std::vector<PizzaIngredient>> pizza_ingredients {
        {Regina, {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Gruyere, PizzaIngredient::Ham, PizzaIngredient::Mushrooms}},
        {Margarita, {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Gruyere}},
        {Americana, {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Gruyere, PizzaIngredient::Steak}},
        {Fantasia, {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Eggplant, PizzaIngredient::GoatCheese, PizzaIngredient::ChiefLove}}
    };

    std::map<PizzaIngredient, std::string> pizza_ingredients_names {
        {PizzaIngredient::Doe, "Doe"},
        {PizzaIngredient::Tomato, "Tomato"},
        {PizzaIngredient::Gruyere, "Gruyere"},
        {PizzaIngredient::Ham, "Ham"},
        {PizzaIngredient::Mushrooms, "Mushrooms"},
        {PizzaIngredient::Steak, "Steak"},
        {PizzaIngredient::Eggplant, "Eggplant"},
        {PizzaIngredient::GoatCheese, "GoatCheese"},
        {PizzaIngredient::ChiefLove, "ChiefLove"}
    };
};

#endif /* !IPIZZA_HPP_ */
