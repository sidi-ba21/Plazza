/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

void Plz::Cook::push(const std::shared_ptr<Plz::IPizza> &pizza)
{
    _mutex.lock();
    _orders.push_back(pizza);
    _mutex.unlock();
    _cookWorking++;
}

std::shared_ptr<Plz::IPizza> Plz::Cook::pop()
{
    _mutex.lock();
    if (_orders.empty()) {
        _mutex.unlock();
        return nullptr;
    }
    auto ready = _orders.back();
    _orders.pop_back();
    _mutex.unlock();
    return ready;
}

void *Plz::kitchen_thread(std::shared_ptr<bool> _isWorking, Plz::Kitchen &reception, std::shared_ptr<Plz::Cook> cook)
{
    
}