/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** thread_pool
*/

#pragma once

#ifndef THREAD_POOL_HPP_
#define THREAD_POOL_HPP_

#include <thread>
#include <vector>

namespace Plz {

    class ThreadPool {
        private:
            std::vector<std::thread> _threads;
        public:
            ThreadPool() = default;
            ~ThreadPool() = default;
            // add a function to the thread pool with his arguments
            template<typename Func, typename ...Args>
            void pushPool(Func &&fn, Args &&...args) {
                _threads.emplace_back(std::forward<Func>(fn), std::forward<Args>(args)...);
            }
            void remove(size_t position) {
                _threads[position].join();
                _threads.erase(_threads.begin() + position);
            }
        void removeAll() {
            for (auto &thread : _threads)
                thread.join();
            _threads.clear();
        }
    };
}


#endif /* !THREAD_POOL_HPP_ */
