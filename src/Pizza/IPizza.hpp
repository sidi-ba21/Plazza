/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Pizza
*/

#ifndef IPIZZA_HPP_
    #define IPIZZA_HPP_

    #include "PizzaUtils.hpp"
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
            std::vector<PizzaIngredient> _ingredients {};
            int _time;
    };

};

#endif /* !IPIZZA_HPP_ */
