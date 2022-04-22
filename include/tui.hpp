#pragma once

#include <iostream>
#include <vector>
#include <functional>

//* Define key objects
#define KEY_NULL                            Key {false, 0, "0"}
#define KEY_TAB                             Key {false, 9, "9"}
#define KEY_ENTER                           Key {false, 10, "10"}
#define KEY_ESCAPE                          Key {false, 27, "27"}
#define KEY_SPACE                           Key {false, 32, "32"}
#define KEY_EXCLAMATION                     Key {false, 33, "33"}
#define KEY_DOUBLE_QUOTE                    Key {false, 34, "34"}
#define KEY_HASH                            Key {false, 35, "35"}
#define KEY_DOLLAR                          Key {false, 36, "36"}
#define KEY_PERCENT                         Key {false, 37, "37"}
#define KEY_AND                             Key {false, 38, "38"}
#define KEY_SINGLE_QUOTE                    Key {false, 39, "39"}
#define KEY_PARENTHESIS_OPEN                Key {false, 40, "40"}
#define KEY_PARENTHESIS_CLOSE               Key {false, 41, "41"}
#define KEY_STAR                            Key {false, 42, "42"}
#define KEY_PLUS                            Key {false, 43, "43"}
#define KEY_COMMA                           Key {false, 44, "44"}
#define KEY_DASH                            Key {false, 45, "45"}
#define KEY_PERIOD                          Key {false, 46, "46"}
#define KEY_FORWARD_SLASH                   Key {false, 47, "47"}
#define KEY_ZERO                            Key {false, 48, "48"}
#define KEY_ONE                             Key {false, 49, "49"}
#define KEY_TWO                             Key {false, 50, "50"}
#define KEY_THREE                           Key {false, 51, "51"}
#define KEY_FOUR                            Key {false, 52, "52"}
#define KEY_FIVE                            Key {false, 53, "53"}
#define KEY_SIX                             Key {false, 54, "54"}
#define KEY_SEVEN                           Key {false, 55, "55"}
#define KEY_EIGHT                           Key {false, 56, "56"}
#define KEY_NINE                            Key {false, 57, "57"}
#define KEY_COLON                           Key {false, 58, "58"}
#define KEY_SEMICOLON                       Key {false, 59, "59"}
#define KEY_ANGLE_BRACKET_LEFT              Key {false, 60, "60"}
#define KEY_EQUALS                          Key {false, 61, "61"}
#define KEY_ANGLE_BRACKET_RIGHT             Key {false, 62, "62"}
#define KEY_QUESTION_MARK                   Key {false, 63, "63"}
#define KEY_AT                              Key {false, 64, "64"}
#define KEY_SHIFT_A                         Key {false, 65, "65"}
#define KEY_SHIFT_B                         Key {false, 66, "66"}
#define KEY_SHIFT_C                         Key {false, 67, "67"}
#define KEY_SHIFT_D                         Key {false, 68, "68"}
#define KEY_SHIFT_E                         Key {false, 69, "69"}
#define KEY_SHIFT_F                         Key {false, 70, "70"}
#define KEY_SHIFT_G                         Key {false, 71, "71"}
#define KEY_SHIFT_H                         Key {false, 72, "72"}
#define KEY_SHIFT_I                         Key {false, 73, "73"}
#define KEY_SHIFT_J                         Key {false, 74, "74"}
#define KEY_SHIFT_K                         Key {false, 75, "75"}
#define KEY_SHIFT_L                         Key {false, 76, "76"}
#define KEY_SHIFT_M                         Key {false, 77, "77"}
#define KEY_SHIFT_N                         Key {false, 78, "78"}
#define KEY_SHIFT_O                         Key {false, 79, "79"}
#define KEY_SHIFT_P                         Key {false, 80, "80"}
#define KEY_SHIFT_Q                         Key {false, 81, "81"}
#define KEY_SHIFT_R                         Key {false, 82, "82"}
#define KEY_SHIFT_S                         Key {false, 83, "83"}
#define KEY_SHIFT_T                         Key {false, 84, "84"}
#define KEY_SHIFT_U                         Key {false, 85, "85"}
#define KEY_SHIFT_V                         Key {false, 86, "86"}
#define KEY_SHIFT_W                         Key {false, 87, "87"}
#define KEY_SHIFT_X                         Key {false, 88, "88"}
#define KEY_SHIFT_Y                         Key {false, 89, "89"}
#define KEY_SHIFT_Z                         Key {false, 90, "90"}
#define KEY_SQUARE_BRACKET_OPEN             Key {false, 91, "91"}
#define KEY_BACK_SLASH                      Key {false, 92, "92"}
#define KEY_SQUARE_BRACKET_CLOSE            Key {false, 93, "93"}
#define KEY_CARET                           Key {false, 94, "94"}
#define KEY_UNDERSCORE                      Key {false, 95, "95"}
#define KEY_BACKTICK                        Key {false, 96, "96"}
#define KEY_A                               Key {false, 97, "97"}
#define KEY_B                               Key {false, 98, "98"}
#define KEY_C                               Key {false, 99, "99"}
#define KEY_D                               Key {false, 100, "100"}
#define KEY_E                               Key {false, 101, "101"}
#define KEY_F                               Key {false, 102, "102"}
#define KEY_G                               Key {false, 103, "103"}
#define KEY_H                               Key {false, 104, "104"}
#define KEY_I                               Key {false, 105, "105"}
#define KEY_J                               Key {false, 106, "106"}
#define KEY_K                               Key {false, 107, "107"}
#define KEY_L                               Key {false, 108, "108"}
#define KEY_M                               Key {false, 109, "109"}
#define KEY_N                               Key {false, 110, "110"}
#define KEY_O                               Key {false, 111, "111"}
#define KEY_P                               Key {false, 112, "112"}
#define KEY_Q                               Key {false, 113, "113"}
#define KEY_R                               Key {false, 114, "114"}
#define KEY_S                               Key {false, 115, "115"}
#define KEY_T                               Key {false, 116, "116"}
#define KEY_U                               Key {false, 117, "117"}
#define KEY_V                               Key {false, 118, "118"}
#define KEY_W                               Key {false, 119, "119"}
#define KEY_X                               Key {false, 120, "120"}
#define KEY_Y                               Key {false, 121, "121"}
#define KEY_Z                               Key {false, 122, "122"}
#define KEY_CURLY_BRACES_OPEN               Key {false, 123, "123"}
#define KEY_PIPE                            Key {false, 124, "124"}
#define KEY_CURLY_BRACES_CLOSE              Key {false, 125, "125"}
#define KEY_TILDE                           Key {false, 126, "126"}
#define KEY_BACKSPACE                       Key {false, 127, "127"}
#define KEY_UP_ARROW                        Key {true, 0, "27 91 65"}
#define KEY_DOWN_ARROW                      Key {true, 0, "27 91 66"}
#define KEY_RIGHT_ARROW                     Key {true, 0, "27 91 67"}
#define KEY_LEFT_ARROW                      Key {true, 0, "27 91 68"}

//* Create a struct to store any two dimensions
struct Dimension2D {
    int width;
    int height;
};

//* Create a struct to store two dimensional information
//* This is the same as Dimension2D, but has element names for location
struct Location2D {
    int x;
    int y;
};

//* Create a struct to store colour information in RGB
struct ColorRGB {
    int r;
    int g;
    int b;
};

//* Create a struct to store the key entered
struct Key {
    bool escape_sequence = false;
    char key;
    std::string full_string;
};

//* Overloading the == operator to compare Key structs
bool operator == (const Key& lhs, const Key& rhs);

//* Struct to store alignment information
struct Align {
    std::string LEFT = "left";
    std::string CENTER = "center";
    std::string RIGHT = "right";
};

//* Initialise the TUI functions
void init_tui();

//* Set the dimensions of the terminal
void set_terminal_size();

//* Get the dimensions of the terminal
Dimension2D get_terminal_size();

//! Validity checks for values in fg_color and bg_color haven't been done, and an invalid value will most definitely result in a crash

//* Set the foreground (text) color
void fg_color(int r, int g, int b);
void fg_color(ColorRGB rgb);
void fg_color(const char* hex);
void fg_color(std::string hex);

//* Set the background color of the text
void bg_color(int r, int g, int b);
void bg_color(ColorRGB rgb);
void bg_color(const char* hex);
void bg_color(std::string hex);

//* Reset formatting of the terminal
void reset_formatting();

//* Clear the terminal in different ways
void clear();

//* Set the cursor position anywhere on the terminal
void set_cursor_position();
void set_cursor_position(Location2D location);
void set_cursor_position(int x, int y);

//* Return the location of the cursor in a Location2D object
struct Location2D wherexy();

//* Convert a hexadecimal color code to RGB values and return a ColorRGB object
struct ColorRGB hex_to_rgb(const char* hex);
struct ColorRGB hex_to_rgb(std::string hex);

//* Split string by a character wide delimiter
std::vector<std::string> split(std::string str);
std::vector<std::string> split(std::string str, char delimiter);

//* Align the text by providing an alignment state as a string
void align(std::string align);

//* Align prints to the left
void align_left();
//* Align the prints to the center
void align_center();
//* Align the prints to the right
void align_right();
//* Reverts the alignment to the previous one
//! NOT IMPLEMENTED
void revert_align();

//* Return the string padded to fit the width
std::string padded_str(std::string str);
std::string padded_str(std::string str, int w);
std::string padded_str(std::string str, std::string end);
std::string padded_str(std::string str, std::string filler);
std::string padded_str(std::string str, int w, std::string end);
std::string padded_str(std::string str, std::string filler, int w);
std::string padded_str(std::string str, std::string filler, std::string end);
std::string padded_str(std::string str, std::string filler, int w, std::string end);

//* Helper function to calculate the number of spaces required on the left to pad the string to match the terminal width or the given width
int calculate_padding_left(std::string str);
int calculate_padding_left(std::string str, int w);

//* Helper function to calculate the number of spaces required on the right to pad the string to match the terminal width or the given width
int calculate_padding_right(std::string str);
int calculate_padding_right(std::string str, int w);

//* Printing text to the terminal
void print();
void print(std::string str);
void print(std::string str, int w);
void print(std::string str, std::string end);
void print(std::string str, std::string end, int w);

//* Print a string multiple times on the screen using one line.
//* Useful for printing multiple blank lines for the interface
void print_loop(std::string str, int times);
void print_loop(std::string str, int times, std::string end);

//* Check if a key is present in the input buffer
bool kbhit();
//* Get a character from the keyboard input buffer
char getch();
//* Return the key pressed, while accounting for special keys
Key get_key();

//* Works like (string * num) in python, appending a string x amount of times and returning the string
std::string extend_string(std::string str, int times);
std::string extend_string(char str, int times);

//* Fills the remaining lines on the screen
Location2D fill_screen();

//* Wraps the text by a given width
std::string basic_text_wrapping(std::string str);
std::string basic_text_wrapping(const char* str);
std::string basic_text_wrapping(std::string str, int width);
std::string basic_text_wrapping(const char* str, int width);

//* Extern important global variables
extern Align ALIGN;
//! GLOBAL COLORS are not used anywhere in the code and should not be set. This is for future use.
extern ColorRGB g_bg_color;
extern ColorRGB g_bg_color_highlighted;
extern ColorRGB g_bg_color_error;
extern ColorRGB g_fg_color;
extern ColorRGB g_fg_color_highlighted;
extern ColorRGB g_fg_color_error;
//? May be removed
extern Dimension2D t_size;
extern std::vector<Key> BASIC_KEYS;
