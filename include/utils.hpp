#pragma once

#include <vector>

//* Declare the functions here, so when the header is imported, all the corresponding functions are imported from the utils.cpp too
void get_terminal_size(int& width, int& height);
const char* fg_color(int r, int g, int b);
const char* fg_color(std::vector<int> rgb);
const char* fg_color(const char* hex);
const char* bg_color(int r, int g, int b);
const char* bg_color(std::vector<int> rgb);
const char* bg_color(const char* hex);
const char* reset_formatting();
void hex_to_rgb(const char* hex, int* r, int* g, int* b);
std::vector<int> hex_to_rgb(const char* hex);
std::vector<std::string> split(std::string str, char delimiter);
void print_centered(std::string str, int w);
void print_centered(std::string str);
