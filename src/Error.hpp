/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <string>
#include <exception>

class Error : public std::exception
{
    public:
        Error(std::string const &message)
        : _message(message) {}

        char const *what() const noexcept { return _message.c_str(); }

    protected:
        std::string _message;
};

class ErrorUsage : public Error
{
    public:
        const std::string _message { "Bad usage.\n" };
        ErrorUsage(): Error(_message) {};
};

class ErrorMultiplier : public Error
{
    public:
        const std::string _message { "Multiplier value "
            "must be a positive number.\n" };
        ErrorMultiplier(): Error(_message) {};
};

class ErrorCooks : public Error
{
    public:
        const std::string _message { "Cooks value "
            "must be a positive number.\n" };
        ErrorCooks(): Error(_message) {};
};

class ErrorTime : public Error
{
    public:
        const std::string _message { "Time value "
            "must be a positive number.\n" };
        ErrorTime(): Error(_message) {};
};

class InvalidCmd : public Error
{
    public:
        const std::string _message { "Invalid command.\n" };
        InvalidCmd(): Error(_message) {};
};

class MsQueues : public Error
{
    public:
        MsQueues(const std::string &message) noexcept : Error(message) {}
};

#endif /* !ERROR_HPP_ */
