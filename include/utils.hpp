#pragma once

#include <iostream>

//* Declare the functions here, so when the header is imported, all the corresponding functions are imported from the utils.cpp too
void init_ncurses();
void exit_ncurses();
std::string get_string();
char get_char();
