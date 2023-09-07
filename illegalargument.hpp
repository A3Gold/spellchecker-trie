#include <iostream>

class illegal_argument : public std::exception {
    public:
        std::string what () {
            return "illegal argument";
        }
};