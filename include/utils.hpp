#pragma once

#include <iostream>

//* Define special constants
#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68
#define ESCAPE 27
#define KEY_Q 113

//* Initialise and exit the program
void init_program();
void exit_program();

//* General helpers
std::string extend_string(std::string str, int times);