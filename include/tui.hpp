#pragma once

#include <iostream>
#include <vector>
#include <functional>

//* Define key objects
#define KEY_TAB                             Key {false, 9, "9", "9"}
#define KEY_ENTER                           Key {false, 10, "10", "10"}
#define KEY_ESCAPE                          Key {false, 27, "27", "27"}
#define KEY_SPACE                           Key {false, 32, "32", "32"}
#define KEY_EXCLAMATION                     Key {false, 33, "33", "33"}
#define KEY_DOUBLE_QUOTE                    Key {false, 34, "34", "34"}
#define KEY_HASH                            Key {false, 35, "35", "35"}
#define KEY_DOLLAR                          Key {false, 36, "36", "36"}
#define KEY_PERCENT                         Key {false, 37, "37", "37"}
#define KEY_AND                             Key {false, 38, "38", "38"}
#define KEY_SINGLE_QUOTE                    Key {false, 39, "39", "39"}
#define KEY_PARENTHESIS_OPEN                Key {false, 40, "40", "40"}
#define KEY_PARENTHESIS_CLOSE               Key {false, 41, "41", "41"}
#define KEY_STAR                            Key {false, 42, "42", "42"}
#define KEY_PLUS                            Key {false, 43, "43", "43"}
#define KEY_COMMA                           Key {false, 44, "44", "44"}
#define KEY_DASH                            Key {false, 45, "45", "45"}
#define KEY_PERIOD                          Key {false, 46, "46", "46"}
#define KEY_FORWARD_SLASH                   Key {false, 47, "47", "47"}
#define KEY_ZERO                            Key {false, 48, "48", "48"}
#define KEY_ONE                             Key {false, 49, "49", "49"}
#define KEY_TWO                             Key {false, 50, "50", "50"}
#define KEY_THREE                           Key {false, 51, "51", "51"}
#define KEY_FOUR                            Key {false, 52, "52", "52"}
#define KEY_FIVE                            Key {false, 53, "53", "53"}
#define KEY_SIX                             Key {false, 54, "54", "54"}
#define KEY_SEVEN                           Key {false, 55, "55", "55"}
#define KEY_EIGHT                           Key {false, 56, "56", "56"}
#define KEY_NINE                            Key {false, 57, "57", "57"}
#define KEY_COLON                           Key {false, 58, "58", "58"}
#define KEY_SEMICOLON                       Key {false, 59, "59", "59"}
#define KEY_ANGLE_BRACKET_LEFT              Key {false, 60, "60", "60"}
#define KEY_EQUALS                          Key {false, 61, "61", "61"}
#define KEY_ANGLE_BRACKET_RIGHT             Key {false, 62, "62", "62"}
#define KEY_QUESTION_MARK                   Key {false, 63, "63", "63"}
#define KEY_AT                              Key {false, 64, "64", "64"}
#define KEY_SHIFT_A                         Key {false, 65, "65", "65"}
#define KEY_SHIFT_B                         Key {false, 66, "66", "66"}
#define KEY_SHIFT_C                         Key {false, 67, "67", "67"}
#define KEY_SHIFT_D                         Key {false, 68, "68", "68"}
#define KEY_SHIFT_E                         Key {false, 69, "69", "69"}
#define KEY_SHIFT_F                         Key {false, 70, "70", "70"}
#define KEY_SHIFT_G                         Key {false, 71, "71", "71"}
#define KEY_SHIFT_H                         Key {false, 72, "72", "72"}
#define KEY_SHIFT_I                         Key {false, 73, "73", "73"}
#define KEY_SHIFT_J                         Key {false, 74, "74", "74"}
#define KEY_SHIFT_K                         Key {false, 75, "75", "75"}
#define KEY_SHIFT_L                         Key {false, 76, "76", "76"}
#define KEY_SHIFT_M                         Key {false, 77, "77", "77"}
#define KEY_SHIFT_N                         Key {false, 78, "78", "78"}
#define KEY_SHIFT_O                         Key {false, 79, "79", "79"}
#define KEY_SHIFT_P                         Key {false, 80, "80", "80"}
#define KEY_SHIFT_Q                         Key {false, 81, "81", "81"}
#define KEY_SHIFT_R                         Key {false, 82, "82", "82"}
#define KEY_SHIFT_S                         Key {false, 83, "83", "83"}
#define KEY_SHIFT_T                         Key {false, 84, "84", "84"}
#define KEY_SHIFT_U                         Key {false, 85, "85", "85"}
#define KEY_SHIFT_V                         Key {false, 86, "86", "86"}
#define KEY_SHIFT_W                         Key {false, 87, "87", "87"}
#define KEY_SHIFT_X                         Key {false, 88, "88", "88"}
#define KEY_SHIFT_Y                         Key {false, 89, "89", "89"}
#define KEY_SHIFT_Z                         Key {false, 90, "90", "90"}
#define KEY_SQUARE_BRACKET_OPEN             Key {false, 91, "91", "91"}
#define KEY_BACK_SLASH                      Key {false, 92, "92", "92"}
#define KEY_SQUARE_BRACKET_CLOSE            Key {false, 93, "93", "93"}
#define KEY_CARET                           Key {false, 94, "94", "94"}
#define KEY_UNDERSCORE                      Key {false, 95, "95", "95"}
#define KEY_BACKTICK                        Key {false, 96, "96", "96"}
#define KEY_A                               Key {false, 97, "97", "97"}
#define KEY_B                               Key {false, 98, "98", "98"}
#define KEY_C                               Key {false, 99, "99", "99"}
#define KEY_D                               Key {false, 100, "100", "100"}
#define KEY_E                               Key {false, 101, "101", "101"}
#define KEY_F                               Key {false, 102, "102", "102"}
#define KEY_G                               Key {false, 103, "103", "103"}
#define KEY_H                               Key {false, 104, "104", "104"}
#define KEY_I                               Key {false, 105, "105", "105"}
#define KEY_J                               Key {false, 106, "106", "106"}
#define KEY_K                               Key {false, 107, "107", "107"}
#define KEY_L                               Key {false, 108, "108", "108"}
#define KEY_M                               Key {false, 109, "109", "109"}
#define KEY_N                               Key {false, 110, "110", "110"}
#define KEY_O                               Key {false, 111, "111", "111"}
#define KEY_P                               Key {false, 112, "112", "112"}
#define KEY_Q                               Key {false, 113, "113", "113"}
#define KEY_R                               Key {false, 114, "114", "114"}
#define KEY_S                               Key {false, 115, "115", "115"}
#define KEY_T                               Key {false, 116, "116", "116"}
#define KEY_U                               Key {false, 117, "117", "117"}
#define KEY_V                               Key {false, 118, "118", "118"}
#define KEY_W                               Key {false, 119, "119", "119"}
#define KEY_X                               Key {false, 120, "120", "120"}
#define KEY_Y                               Key {false, 121, "121", "121"}
#define KEY_Z                               Key {false, 122, "122", "122"}
#define KEY_CURLY_BRACES_OPEN               Key {false, 123, "123", "123"}
#define KEY_PIPE                            Key {false, 124, "124", "124"}
#define KEY_CURLY_BRACES_CLOSE              Key {false, 125, "125", "125"}
#define KEY_TILDE                           Key {false, 126, "126", "126"}
#define KEY_BACKSPACE                       Key {false, 127, "127", "127"}
#define KEY_UP_ARROW                        Key {true, 0, "2791865", "27 91 65"}
#define KEY_DOWN_ARROW                      Key {true, 0, "2791866", "27 91 66"}
#define KEY_RIGHT_ARROW                     Key {true, 0, "2791867", "27 91 67"}
#define KEY_LEFT_ARROW                      Key {true, 0, "2791868", "27 91 68"}
#define KEY_F1                              Key {true, 0, "277980", "27 79 80"}
#define KEY_F2                              Key {true, 0, "277981", "27 79 81"}
#define KEY_F3                              Key {true, 0, "277982", "27 79 82"}
#define KEY_F4                              Key {true, 0, "277983", "27 79 83"}
#define KEY_F5                              Key {true, 0, "27914953126", "27 91 49 53 126"}
#define KEY_F6                              Key {true, 0, "27914955126", "27 91 49 55 126"}
#define KEY_F7                              Key {true, 0, "27914956126", "27 91 49 56 126"}
#define KEY_F8                              Key {true, 0, "27914957126", "27 91 49 57 126"}
#define KEY_F9                              Key {true, 0, "27915048126", "27 91 50 48 126"}
#define KEY_F10                             Key {true, 0, "27915049126", "27 91 50 49 126"}
#define KEY_SHIFT_F11                       Key {true, 0, "279150515950126", "27 91 50 51 59 50 126"}
#define KEY_F12                             Key {true, 0, "27915052126", "27 91 50 52 126"}

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
    std::string space_delimited_full_string;
};

//* Struct to store alignment information
struct Align {
    std::string LEFT = "left";
    std::string CENTER = "center";
    std::string RIGHT = "right";
};

//* Line struct to store information about each line being displayed on the menu
struct Entry {
    //* ID of the menu entry. Must be unset for non-interactive elements barring unintentional results.
    int id;
    //* The string that should be displayed while rendering the menu
    std::string label;

    //* The corresponding function that will be run when the option is selected. Will not be called if interactable is unset.
    std::function<void()> func;

    //* Whether the option can be selected or not
    bool interactable;
};

//* Struct to customise menu render settings
struct MenuRenderSettings {
    //* The total width of the menu
    int width;

    //* wether to use feedback bar
    bool use_feedback_bar = true;

    //* The width of the menu entry and, by extension, feedback bar
    int selection_size = 40;

    //* Append this character at the end of rendering a menu entry
    std::string end = "\n";

    //* Lines of padding between menu entries
    int line_padding = 1;

    //* What the padding between the menu items will render as (non-repeating)
    std::string line_padding_string = " ";

    //* Default alignment of the menu entries
    //* Recommended to use ALIGN.<alignment> to set alignment 
    std::string alignment = "center";

    //* Wheather the menu should fill the entire screen or only update the amount of screen it needs to render itself
    bool fill_screen = true;
    
    //* Use angled brackets or any other pointer to provide feedback. Can be used alongside feedback bars
    //! NOT IMPLEMENTED YET
    bool use_entry_pointers = false;

    //* Feedback pointer positioned on the left side of the entry
    //! NOT IMPLEMENTED YET
    std::string left_pointer = ">";

    //* Feedback pointer positioned on the right side of the entry
    //! NOT IMPLEMENTED YET
    std::string right_pointer = "<";

    //* Should feedback pointers be right next to the text
    //! NOT IMPLEMENTED YET
    bool pointer_next_to_text = false;

    //* Space between the pointers and the text. Needs to be set if pointer_next_to_text is set
    //! NOT IMPLEMENTED YET
    int pointer_space_from_text;

    //* Setting the foreground color using hexadecimal color codes
    std::string fg_color_hex = "#ffffff";
    //* Setting the background color using hexadecimal color color
    std::string bg_color_hex = "#000000";

    //* Setting the foreground color using a ColorRGB object
    struct ColorRGB fg_color = {255, 255, 255};
    //* Setting the background color using a ColorRGB object
    struct ColorRGB bg_color = {0, 0, 0};

    //* Setting the foreground color of the highlighted section using hexadecimal color codes
    std::string fg_color_highlighted_hex = "#000000";
    //* Setting the background color of the highlighted section using hexadecimal color codes
    std::string bg_color_highlighted_hex = "#ffffff";

    //* Setting the foreground color of the highlighted section using a ColorRGB object
    struct ColorRGB fg_color_highlighted = {0, 0, 0};
    //* Setting the background color of the highlighted section using a ColorRGB object
    struct ColorRGB bg_color_highlighted = {255, 255, 255};
};

//* Menu class
class Menu {
    public:
        //* Add an option to be displayed on the menu screen
        void add_option(std::string str, std::function<void()> func);

        //* Adds a menu entry with given Entry settings
        void add_entry(Entry entry);

        //* Add a non-selectable line on the menu screen to add padding or display text
        void add_line();
        void add_line(std::string str);

        //* Move the current selection up by a given amount
        void move_selection_up();
        void move_selection_up(int by);

        //* Move the current selection down by a given amount
        void move_selection_down();
        void move_selection_down(int by);

        //* Should the menu entry loop back up to the first element after attempting to go down after the last element?
        void set_entry_loop(bool val);

        //* Render the menu with the given settings
        void render();
        void render(MenuRenderSettings render_settings);

        //* Handle the input by the user.
        //* Typically used after rendering the menu
        void handle_input();

    private:
        //* Should the menu loop around?
        bool loop_menu_options = false;

        //* The vector storing all menu entry elements including non-selectable lines
        std::vector<Entry> entries;

        //* Current selection of the menu entry
        int selection = 0;

        //* What should the ID of the next selectable menu entry be?
        int next_id = 0;
};

//* Initialise the TUI functions
void init_tui();

//* Set the dimensions of the terminal
void set_terminal_size();

//* Get the dimensions of the terminal
Dimension2D get_terminal_size();

//* Set the foreground (text) color
void fg_color(int r, int g, int b);
void fg_color(ColorRGB rgb);
void fg_color(const char* hex);

//* Set the background color of the text
void bg_color(int r, int g, int b);
void bg_color(ColorRGB rgb);
void bg_color(const char* hex);

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
std::string padded_str(std::string str, int w, const char* end);

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

//* Check if a key is present in the input buffer
bool kbhit();
//* Get a character from the keyboard input buffer
char getch();
//* Return the key pressed, while accounting for special keys
char get_key();
