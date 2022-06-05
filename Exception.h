#pragma once
#include <exception>
#include <string>

class Exception : public std::exception {
    std::string msg;
public:
    Exception(std::string message);
    std::string what ();
};
