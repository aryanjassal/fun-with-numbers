#include <iostream>

#include "utils.hpp"
#include "tui.hpp"

//* Initialise the program
void init_program() {
    clear();
    init_tui();
    Align ALIGN;
}

//* Clean up and exit the program
void exit_program() {
    reset_formatting();
    print();
    exit(0);
}

//* Works like (string * num) in python, appending a string x amount of times and returning the string
std::string extend_string(std::string str, int times) {
    std::string out;
    for (int i = 0; i < times; i++) {
        out.append(str);
    }
    return out;
}
