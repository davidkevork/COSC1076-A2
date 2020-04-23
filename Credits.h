#ifndef COSC_ASS_TWO_CREDITS
#define COSC_ASS_TWO_CREDITS

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

#endif // COSC_ASS_TWO_CREDITS
