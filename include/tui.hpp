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
const char* fg_color(int r, int g, int b);
const char* fg_color(std::vector<int> rgb);
const char* fg_color(const char* hex);

const char* bg_color(int r, int g, int b);
const char* bg_color(std::vector<int> rgb);
const char* bg_color(const char* hex);

//* Reset formatting of the terminal
const char* reset_formatting();

//* Clear the terminal in different ways
const char* clear();

//* Cursor control
const char* set_cursor_position(int x, int y);
const char* set_cursor_position();
const char* hide_cursor();
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

//* Printing content to the screen/terminal
void print();
void print(std::string str);
void print(char str);
void print(int str);
void print_loop(int times, std::string str);
