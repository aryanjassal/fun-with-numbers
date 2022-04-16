#pragma once

#include <vector>
#include <iostream>

//* Declare the functions here, so when the header is imported, all the corresponding functions are imported from the utils.cpp too
void init_program();
void exit_program();
void get_terminal_size(int& width, int& height);
const char* fg_color(int r, int g, int b);
const char* fg_color(std::vector<int> rgb);
const char* fg_color(const char* hex);
const char* bg_color(int r, int g, int b);
const char* bg_color(std::vector<int> rgb);
const char* bg_color(const char* hex);
const char* reset_formatting();
const char* clear();
const char* set_cursor_position(int x, int y);
void hex_to_rgb(const char* hex, int* r, int* g, int* b);
std::vector<int> hex_to_rgb(const char* hex);
std::vector<std::string> split(std::string str, char delimiter);
std::string calculate_padding(std::string str, int w);
void print();
void print(std::string str);
void print(std::string str, bool add_padding);
void print_loop(int times, std::string str);
void print_loop(int times, std::string str, bool add_padding);
void print_centered(std::string str, int w);
void print_centered(std::string str);
