#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

//* Define special constants
#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68
#define ESCAPE 27
#define KEY_Q 113
#define RETURN 10

//* Initialise and exit the program
void init_program();
void exit_program();

//* General helpers
std::string extend_string(std::string str, int times);

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