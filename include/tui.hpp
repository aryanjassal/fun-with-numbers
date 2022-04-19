#pragma once

#include <iostream>
#include <vector>
#include <functional>

//* Define special constants
#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68
#define ESCAPE 27
#define KEY_Q 113
#define RETURN 10

//* Create a struct to store any two dimensions
struct Dimension2D {
    int width;
    int height;
};

//* Create a struct to store colour information in RGB
//! Currently unimplemented in code
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

int calculate_padding_left(std::string str);
int calculate_padding_left(std::string str, int w);
int calculate_padding_right(std::string str);
int calculate_padding_right(std::string str, int w);

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

//* Stuff to render the menu properly
//* Line struct
struct Line {
    int id;
    std::string label;
    std::function<void()> func;
    bool interactable;
};

struct MenuRenderSettings {
    int width;
    int selector_size;
    
    bool use_entry_pointers;
    std::string left_pointer;
    std::string right_pointer;
    bool pointer_on_sides;
    int pointer_space_from_text;

    std::string fg_color_hex = "#ffffff";
    std::string bg_color_hex = "#000000";
    //! Not implemented using ColorRGB yet
    struct ColorRGB fg_color = {255, 255, 255};
    //! Not implemented using ColorRGB yet
    struct ColorRGB bg_color = {0, 0, 0};

    std::string fg_color_highlighted_hex = "#000000";
    std::string bg_color_highlighted_hex = "#ffffff";
    //! Not implemented using ColorRGB yet
    struct ColorRGB fg_color_highlighted = {0, 0, 0};
    //! Not implemented using ColorRGB yet
    struct ColorRGB bg_color_highlighted = {255, 255, 255};
};

//* Menu class
class Menu {
    public:
        void add_option(std::string str, std::function<void()> func);
        void add_line();
        void add_line(std::string str);
        void move_selection_up();
        void move_selection_up(int by);
        void move_selection_down();
        void move_selection_down(int by);
        void set_entry_loop(bool val);
        void render();
        void render(MenuRenderSettings render_settings);
        void handle_input();
    private:
        bool loop_menu_options = false;
        std::vector<Line> lines;
        int selection = 0;
        int next_id = 0;
};
