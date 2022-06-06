#pragma once
#include <exception>
#include <string>

/**
 * Custom exception class.
 * Inherited from std::exception
 */
class Exception : public std::exception {
    std::string msg;
public:

    /**
     * Constructor
     * @param message - Exception message
     */
    Exception(std::string message);

    /**
     * Returns the exception message
     * @return Exception message
     */
    std::string what ();
};
