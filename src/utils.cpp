#include <iostream>

#include "utils.hpp"
#include "tui.hpp"

//* Initialise the program
void init_program() {
    //* Clear the screen
    clear();
    //* Initialise the terminal user interface
    init_tui();
    //* Create the alignment object to not mistype an alignment value and crash the program
    Align ALIGN;
}

//* Clean up and exit the program
void exit_program() {
    //* Remove all formatting
    reset_formatting();
    //* Print a new line. Not necessary but closing looks more graceful
    print();
    //* Exit the program
    exit(0);
}

//* Works like (string * num) in python, appending a string x amount of times and returning the string
std::string extend_string(std::string str, int times) {
    //* Create the output string
    std::string out;
    
    //* Append the string str to the output string out as many times as specified by the user
    for (int i = 0; i < times; i++) {
        out.append(str);
    }

    //* Return the extended string
    return out;
}
