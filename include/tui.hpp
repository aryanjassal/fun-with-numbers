#pragma once

#include <iostream>
#include <vector>
#include <functional>

//* Define key codes
#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68
#define ESCAPE 27
#define KEY_Q 113
#define RETURN 10

//TODO: see if return types for ANSI sequences are required

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
    bool escape_sequence;
    char key;
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
