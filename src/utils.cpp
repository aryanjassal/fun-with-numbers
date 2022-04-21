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
void exit_program(int return_value) {
    //* Remove all formatting
    reset_formatting();
    //* Print a new line. Not necessary but closing looks more graceful
    print();
    //* Exit the program
    exit(return_value);
}

void exit_program() {
    exit_program(0);
}
