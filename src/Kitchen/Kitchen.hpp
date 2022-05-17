/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

#include "../Pizza/IPizza.hpp"
#include <memory>
#include <vector>
#include <mutex>
#include <atomic>

namespace Plz {

    class Cook {
        public:
            std::atomic<int> _cookWorking {};
            std::array<std::atomic<int>, 9> _ingredients_left {5, 5, 5, 5, 5, 5, 5, 5, 5};
            mutable std::mutex _mutex;
            std::vector<std::shared_ptr<IPizza>> _orders {};

        public:
            Cook() = default;
            ~Cook() = default;
            void push(const std::shared_ptr<IPizza> &pizza);
            std::shared_ptr<IPizza> pop();
    };

    class Kitchen {
        public:
            Kitchen() = default;
            ~Kitchen() = default;
            mutable std::mutex _mutex;
            std::vector<std::shared_ptr<IPizza>> _orders {};
            std::vector<std::shared_ptr<IPizza>> _ready {};
    };

    void *kitchen_thread(std::shared_ptr<bool> _isWorking, Plz::Kitchen &reception, std::shared_ptr<Plz::Cook> cook);
    void *cook_thread(std::shared_ptr<bool> _isWorking, Plz::Kitchen &reception, std::shared_ptr<Plz::Cook> cook, std::shared_ptr<Plz::IPizza> pizza);
}

#endif /* !KITCHEN_HPP_ */
