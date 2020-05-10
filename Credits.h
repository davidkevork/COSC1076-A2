#ifndef CREDITS_H
#define CREDITS_H

#include <iostream>
#include <string>

class Credits {
    public:
        Credits(std::string name, std::string id);
        ~Credits();

        void print();

    private:
        std::string name;
        std::string id;
};

#endif // CREDITS_H
