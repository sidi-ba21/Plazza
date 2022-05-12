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

    enum PizzaType {
        REGINA = 1,
        MARGARITA = 2,
        AMERICANA = 4,
        FANTASIA = 8
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

    inline std::map<PizzaType, std::vector<PizzaIngredient>> pizza_ingredients {
        {REGINA, {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Gruyere, PizzaIngredient::Ham, PizzaIngredient::Mushrooms}},
        {MARGARITA, {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Gruyere}},
        {AMERICANA, {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Gruyere, PizzaIngredient::Steak}},
        {FANTASIA, {PizzaIngredient::Doe, PizzaIngredient::Tomato, PizzaIngredient::Eggplant, PizzaIngredient::GoatCheese, PizzaIngredient::ChiefLove}}
    };

    inline std::map<PizzaIngredient, std::string> pizza_ingredients_names {
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

    inline std::map<std::string, PizzaType> pizza_types {
        {"regina", PizzaType::REGINA},
        {"margarita", PizzaType::MARGARITA},
        {"americana", PizzaType::AMERICANA},
        {"fantasia", PizzaType::FANTASIA}
    };

    inline std::map<std::string, PizzaSize> pizza_sizes {
        {"S", PizzaSize::S},
        {"M", PizzaSize::M},
        {"L", PizzaSize::L},
        {"XL", PizzaSize::XL},
        {"XXL", PizzaSize::XXL}
    };

};

#endif /* !IPIZZA_HPP_ */
