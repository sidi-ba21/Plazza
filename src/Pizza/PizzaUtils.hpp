/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** PizzaUtils
*/

#ifndef PIZZAUTILS_HPP_
    #define PIZZAUTILS_HPP_

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

    inline std::map<PizzaType, std::string> pizza_names {
        {PizzaType::REGINA, "regina"},
        {PizzaType::MARGARITA, "margarita"},
        {PizzaType::AMERICANA, "americana"},
        {PizzaType::FANTASIA, "fantasia"}
    };

    inline std::map<PizzaSize, std::string> pizza_str_size {
        {PizzaSize::S, "S"},
        {PizzaSize::M, "M"},
        {PizzaSize::L, "L"},
        {PizzaSize::XL, "XL"},
        {PizzaSize::XXL, "XXL"}
    };

    inline std::map<std::string, PizzaSize> pizza_sizes {
        {"S", PizzaSize::S},
        {"M", PizzaSize::M},
        {"L", PizzaSize::L},
        {"XL", PizzaSize::XL},
        {"XXL", PizzaSize::XXL}
    };

    inline std::map<PizzaType, int> pizza_time {
        {PizzaType::REGINA, 2000},
        {PizzaType::MARGARITA, 1000},
        {PizzaType::AMERICANA, 2000},
        {PizzaType::FANTASIA, 4000}
    };

};

#endif /* !PIZZAUTILS_HPP_ */
