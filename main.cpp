#include <iostream>
#include <string>
#include <cstdlib>

#include "display_communicator/display_communicator.h"

int convert_input(std::string input);

display_communicator *communicator;

int main(int argc, char *argv[])
{
    std::string option = argv[1];

    if (option == "--brightness") {
        int value = convert_input(argv[2]);
        std::cout << "Setting brightness to " << value << "%\n";
        communicator->setValue(0x10, value);
    } else if (option == "--contrast") {
        int value = convert_input(argv[2]);
        std::cout << "Setting contrast to " << value << "%\n";
        communicator->setValue(0x12, value);
    } else {
        std::cout << "Usage: --contrast <value>, --brightness <value>" << std::endl;
        return 1;
    }

    return 0;
}

int convert_input(std::string input)
{
    int int_value = 0;
    try {
        int_value = std::stoi(input);
    } catch (const std::exception &e) {
        std::cout << "Invalid numeric value: " << input << std::endl;
        exit(1);
    }

    if (int_value < 0 || int_value > 100) {
        std::cout << "Value must be between 0 and 100" << std::endl;
        exit(1);
    }

    return int_value;
}
