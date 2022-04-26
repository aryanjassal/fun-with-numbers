#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <chrono>

#include "tui.hpp"

//************************************************************************************************
//************************************************************************************************


struct StatsRenderSettings {
    std::string title_rendering_style = "ansi";
    std::function<void(std::string)> title_renderer;
    
    std::string text_start = "{";
    std::string text_end = "}";
    std::string top_left_corner = "╭";
    std::string top_right_corner = "╮";
    std::string bottom_left_corner = "╰";
    std::string bottom_right_corner = "╯";
    std::string vertical_bar = "│";
    std::string horizontal_bar = "─";
    int section_width = 80;

    std::string alignment = "center";
    int padding_between_lines = 1;
    int padding_from_top = 4;

    int padding_below_title = 4;
    bool render_label = true;

    bool fill_screen = true;
};

struct Stat {
    //* The ID of the object, so the ordering of the save file won't matter
    int id;

    //* The label that will be rendered for this specific stat entry
    std::string label;

    //* The value for this Stat object
    long long val;

    //* The units optionally displayed after the value
    std::string units;

    //* The section in which they belong
    std::string section;

    //* Should this stat be rendered?
    bool rendered = true;
};

class Statistics {
    public:
        void add_stat(Stat stat);
        void add_stat(std::string label, std::string section_id);
        void add_stat(std::string label, std::string section_id, bool rendered);
        void add_stat(std::string label, long long val, std::string section_id);
        void add_stat(std::string label, std::string section_id, std::string units);
        void add_stat(std::string label, long long val, std::string section_id, bool rendered);
        void add_stat(std::string label, std::string section_id, std::string units, bool rendered);
        void add_stat(std::string label, long long val, std::string section_id, std::string units);
        void add_stat(std::string label, long long val, std::string section_id, std::string units, bool rendered);
        struct Stat get_stat(int id);
        void set_stat(int id, long long val);
        void save_stats();
        void save_stats(std::string file_name);
        void load_stats();
        void load_stats(std::string file_name);
        int render();
        int render(StatsRenderSettings render_settings);
        void reset();
    private:
        std::vector<Stat> stats;
        int next_id = 1;
};


//************************************************************************************************
//************************************************************************************************


//* Line struct to store information about each line being displayed on the menu
struct Entry {
    //* ID of the menu entry. Must be unset for non-interactive elements barring unintentional results.
    int id = -1;

    //* The string that should be displayed while rendering the menu
    std::string label = "";

    //* The corresponding function that will be run when the option is selected. Will not be called if interactable is unset.
    std::function<void()> func;

    //* Whether the option can be selected or not
    bool interactable = false;
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

    int padding_above_title = 3;
    std::function<void(std::string)> title_renderer;
    std::string title_style;
    int padding_below_title = 3;
};

//* Menu class
class Menu {
    public:
        //* Add an option to be displayed on the menu screen
        void add_option(std::string str, std::function<void()> func);

        //* Adds a menu entry with given Entry settings
        void add_entry(Entry entry);

        //* Add a non-selectable line on the menu screen to add padding or display text
        void add_line(std::string str);
        void add_line();

        //* Move the current selection up by a given amount
        void move_selection_up(int by);
        void move_selection_up();

        //* Move the current selection down by a given amount
        void move_selection_down(int by);
        void move_selection_down();

        //* Should the menu entry loop back up to the first element after attempting to go down after the last element?
        void set_entry_loop(bool val);

        //* Render the menu with the given settings
        void render(MenuRenderSettings render_settings);
        void render();

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

//************************************************************************************************
//************************************************************************************************

//* Attribute struct for adding new attributes to output of check number features
struct Attribute {
    std::string label;
    std::function<std::string(long long)> func;
    bool append_label;
};

//* Render settings for the Check Number Features renderer
struct CNFRenderSettings {
    std::string top_left_corner = "╔";
    std::string top_right_corner = "╗";
    std::string bottom_left_corner = "╚";
    std::string bottom_right_corner = "╝";
    std::string vertical_bar = "║";
    std::string horizontal_bar = "═";
    std::string horizontal_padding = " ";
    int digits = 19;
    int padding_from_top = 3;
    std::string input_prompt_text = "Enter a number";
    int padding_below_prompt = 2;
    std::string prompt = "# > ";
    std::string input_filler = "_";
    std::string invalid_input_feedback = "Invalid input";
    std::string failed_conversion_feedback = "Failed conversion";
    std::string empty_input_feedback = "Empty input";
    std::string num_too_big_error = "The number you have entered exceeds the 64-bit signed integer limit. Please try entering a smaller number.";
    int padding_before_error = 2;
    int padding_after_error = 2;
    int padding_below_input_field = 3;
    std::string features_display_text = "Number features";
    int padding_before_features = 2;
    int padding_between_features = 1;
    std::string alignment = "center";
    bool fill_screen = true;
    int max_width = 60;
};

//* Check number features class
class CheckNumberFeatures {
    public:
        void add_attribute(Attribute attr);
        void add_attribute(std::string label, std::function<std::string(long long)> func, bool append_label);
        void add_attribute(const char* label, std::function<std::string(long long)> func, bool append_label);
        int render(CNFRenderSettings render_settings, Statistics &stats);
        int handle_input(CNFRenderSettings render_settings, Statistics &stats);
        void reset();
    private:
        std::vector<Attribute> attributes;
        bool error = false;
        std::string error_msg;
        std::string input;
        bool waited_once = false;
};


//************************************************************************************************
//************************************************************************************************

struct GraphRenderSettings {
    std::string alignment = "center";

    int padding_before_graph = 3;
    int graph_width = 0;
    int graph_height = (int)((t_size.height * 2) / 3);
    int graph_horizontal_padding = 3;
    int x_axis_step = 4;
    int y_axis_step = 2;

    int input_width = 15;
    std::string top_left_corner = "╔";
    std::string top_right_corner = "╗";
    std::string bottom_left_corner = "╚";
    std::string bottom_right_corner = "╝";
    std::string vertical_bar = "║";
    std::string horizontal_bar = "═";
    std::string horizontal_padding = " ";
    int padding_before_input_prompt = 2;
    std::string input_prompt_text = "Enter numerical whole number coordinates separated by a comma (x axis goes first then y axis comes later)";
    int padding_after_input_prompt = 2;
    int padding_after_error = 2;
    std::string prompt = "coordinates > ";
    std::string input_filler = "_";
    std::string invalid_input_feedback = "Coordinates need to be integers. Come on, man. It even says so on the instructions above.";
    std::string invalid_input_format = "Forgot some commas or added too many?";
    std::string out_of_bounds_feedback = "Number out of bounds.";

    bool fill_screen = true;
};

class PointPlotter {
    public:
        void add_point(int x, int y);
        void add_point(Location2D point);
        int render(GraphRenderSettings render_settings, Statistics &stats);
        int handle_input(GraphRenderSettings render_settings, Statistics &stats);
        void reset_graph();
    private:
        std::vector<Location2D> points;
        void render_graph(GraphRenderSettings render_settings);
        std::string input;
        bool error = false;
        std::string error_msg;
        Dimension2D graph_dimension;
        bool waited_once = false;
};


//************************************************************************************************
//************************************************************************************************

struct BSTRenderSettings {
    int padding_from_top = 3;
    std::string title_style = "ansi";
    std::function<void(std::string)> title_renderer;
    int padding_below_title = 4;
    std::string alignment = "center";
    int max_questions = 3;

    std::vector<std::string> explanation;
    int padding_from_help = 2;
    int padding_for_left_text = 5;

    int input_width = 15;
    std::string prompt = "your answer > ";
    std::string input_filler = "_";
    std::string top_left_corner = "╔";
    std::string top_right_corner = "╗";
    std::string bottom_left_corner = "╚";
    std::string bottom_right_corner = "╝";
    std::string vertical_bar = "║";
    std::string horizontal_bar = "═";
    std::string horizontal_padding = " ";
    int padding_after_question = 2;
    int padding_below_input = 1;
    std::string answer_correct = "Correct answer! Took |time|.";
    std::string answer_incorrect = "Incorrect answer! Please try again.";

    std::string test_finished = "Well done! The test was finished in |time|. Press any key to escape to the main menu.";

    bool fill_screen = true;
};

class BrainSpeedTest {
    public:
        void render(BSTRenderSettings render_settings, Statistics &stats);
        int handle_input(BSTRenderSettings render_settings, Statistics &stats);
        void reset();
    private:
        std::chrono::steady_clock::time_point start_time;
        std::chrono::steady_clock::time_point end_time;
        std::chrono::steady_clock::time_point question_start;
        std::chrono::steady_clock::time_point question_end;
        std::string input = "";
        int question_number = 1;
        bool test_started = false;
        int want_exit = false;
        int ans;
        int num1, num2 = 0;
        char op;
        int questions_asked;
        int correct_answers;
};


//************************************************************************************************
//************************************************************************************************


struct MBRenderSettings {
    int padding_from_top = 4;
    std::string title_style = "ansi";
    std::function<void(std::string)> title_renderer;
    int padding_below_title = 4;
    std::string alignment = "center";
    int max_digits = 17;

    std::vector<std::string> explanation;
    int padding_from_help = 2;

    int input_width = max_digits;
    std::string prompt = "the number > ";
    std::string input_filler = "_";
    std::string top_left_corner = "╔";
    std::string top_right_corner = "╗";
    std::string bottom_left_corner = "╚";
    std::string bottom_right_corner = "╝";
    std::string vertical_bar = "║";
    std::string horizontal_bar = "═";
    std::string horizontal_padding = " ";
    int padding_after_question = 2;
    int padding_for_left_text = 5;
    int padding_before_feedback = 3;

    std::string test_failed = "Incorrect! Your answer was |input| and the correct answer was |answer|. Your score was |score|!";
    std::string test_finished = "Correct! You have cleared |max| digits! That was the end of the test. Press any key to escape to the main menu.";
    std::string answer_correct = "Correct! Your score is |score|! Press any key to continue.";

    bool fill_screen = true;
};

class MemoryBenchmark {
    public:
        void render(MBRenderSettings render_settings, Statistics &stats);
        int handle_input(MBRenderSettings render_settings, Statistics &stats);
        void reset();
    private:
        std::string input;
        int digits = 1;
        int want_exit = false;
        int num;
        bool calculate_new_num = true;
        bool test_finished = false;
        bool waited_once;
};
