#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

//* Initialise the program
void init_program();
//* Clean up and exit the program
void exit_program();

//* Works like (string * num) in python, appending a string x amount of times and returning the string
std::string extend_string(std::string str, int times);
