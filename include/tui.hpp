#pragma once

#include <iostream>
#include <vector>

//* Create a struct to store any two dimensions
struct Dimension2D {
    int width;
    int height;
};

//* Create a struct to store colour information in RGB
//! Currently unimplemented
struct ColorRGB {
    int r;
    int g;
    int b;
};

//* Initialise the TUI functions
void init_tui();

//* Terminal utility functions
void get_terminal_size(int& width, int& height);
void get_terminal_size();

//* Setting the foreground and background colour
std::string fg_color(int r, int g, int b);
std::string fg_color(std::vector<int> rgb);
std::string fg_color(const char* hex);

std::string bg_color(int r, int g, int b);
std::string bg_color(std::vector<int> rgb);
std::string bg_color(const char* hex);

//* Reset formatting of the terminal
std::string reset_formatting();

//* Clear the terminal in different ways
std::string clear();

//* Cursor control
std::string set_cursor_position();
std::string set_cursor_position(int x, int y);
std::string move_cursor_up();
std::string move_cursor_up(int lines);

//! NON FUNCTIONAL
const char* hide_cursor();
//! NON FUNCTIONAL
const char* show_cursor();

//* Hex to RGB
void hex_to_rgb(const char* hex, int* r, int* g, int* b);
std::vector<int> hex_to_rgb(const char* hex);

//* Split string by a character wide delimiter
std::vector<std::string> split(std::string str, char delimiter);

//* Align the text
void align(std::string align);
void align_center();
void align_left();
void align_right();

//* Extras to help bring flair to print statements
std::string padded_str(std::string str);
std::string padded_str(std::string str, int w);
std::string padded_str(std::string str, int w, const char* end);

int calculate_padding(std::string str);
int calculate_padding(std::string str, int w);

//* Printing content to the screen/terminal
void print();
void print(std::string str);
void print(std::string str, int w);
void print(std::string str, std::string end);
void print(std::string str, std::string end, int w);

void print_raw(std::string);

void print_loop(int times, std::string str);

//* Receiving inputs and input helpers
char getch();
char get_key();
