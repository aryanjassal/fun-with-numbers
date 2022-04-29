#pragma once

#include <functional>  //* for std::function<>
#include <iostream>  //* for std::string
#include <vector>  //* for std::vector<>
#include <chrono>  //* for std::chrono::steady_clock::time_point
#include <utility>  //* for std::pair

#include "tui.hpp"  //* for 

//************************************************************************************************
//************************************************************************************************


struct StatsRenderSettings {
    //* the rendering style to use for the title rendering
    std::string title_rendering_style = "ansi";

    //* the title renderer function, which takes the title rendering style as an argument
    std::function<void(std::string)> title_renderer;
    
    //* the character displayed before the text title of the group is printed
    std::string text_start = "{";

    //* the character displayed after the text title of the group is printed
    std::string text_end = "}";

    //* the character displayed at the top left of the section box
    std::string top_left_corner = "╭";

    //* the character displayed at the top right of the section box
    std::string top_right_corner = "╮";
    
    //* the character displayed at the bottom left of the section box
    std::string bottom_left_corner = "╰";

    //* the character displayed at the bottom right of the section box
    std::string bottom_right_corner = "╯";

    //* the charcter displayed at the vertical boundary of the program
    std::string vertical_bar = "│";

    //* the charcter displayed at the horizontal boundary of the program
    std::string horizontal_bar = "─";

    //* the width of the section
    int section_width = 80;

    //* the alignment for prints
    std::string alignment = "center";

    //* padding between each line inside the section
    int padding_between_lines = 1;

    //* padding from the top for the title
    int padding_from_top = 4;

    //* padding below the title
    int padding_below_title = 4;

    //* should the label be rendered, or just render the values
    //* idk why this would be set as false, but kept the option just in case
    bool render_label = true;

    //* does the program fill the screen to completely refresh it?
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
        //* add a statistic to track
        void add_stat(Stat stat);
        void add_stat(std::string label, std::string section_id);
        void add_stat(std::string label, std::string section_id, bool rendered);
        void add_stat(std::string label, long long val, std::string section_id);
        void add_stat(std::string label, std::string section_id, std::string units);
        void add_stat(std::string label, long long val, std::string section_id, bool rendered);
        void add_stat(std::string label, std::string section_id, std::string units, bool rendered);
        void add_stat(std::string label, long long val, std::string section_id, std::string units);
        void add_stat(std::string label, long long val, std::string section_id, std::string units, bool rendered);

        //* return a particular statistic with the given id
        struct Stat get_stat(int id);

        //* set the value of a statistic with the given id
        void set_stat(int id, long long val);

        //* save all stats
        void save_stats();
        void save_stats(std::string file_name);

        //* load all stats from the save file
        void load_stats();
        void load_stats(std::string file_name);

        //* render the statistics to the screen using grouping and the render settings
        int render();
        int render(StatsRenderSettings render_settings);

        //* reset all the statistics to zeroes
        void reset();
    private:
        //* the vector which contains all the tracked Stat objects 
        std::vector<Stat> stats;

        //* the id of the next auto-generated stats object
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

    //* the padding above the title from the top
    int padding_above_title = 3;

    //* the function to render the title given a style in the format of a string
    std::function<void(std::string)> title_renderer;

    //* the title rendering style
    std::string title_style;

    //* the padding to put below the title
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
    //* the label (to differentiate for the user or to print it)
    std::string label;

    //* the function to execute to get the value of this attribute given the number and should return a string to be printed
    std::function<std::string(long long)> func;

    //* should the label be added before rendering the values or not
    bool append_label;
};

//* Render settings for the Check Number Features renderer
struct CNFRenderSettings {
    //* the function to render the title using the given style 
    std::function<void(std::string)> title_renderer;

    //* the style to render the title in
    std::string title_style;

    //* padding from the top of the screen and above the title
    int padding_from_top = 4;

    //* padding below the title
    int padding_below_title = 3;

    //* the character to draw at the top left corner of the input box
    std::string top_left_corner = "╔";

    //* the character to draw at the top right corner of the input box
    std::string top_right_corner = "╗";
    
    //* the character to draw at the bottom left corner of the input box
    std::string bottom_left_corner = "╚";
    
    //* the character to draw at the bottom right corner of the input box
    std::string bottom_right_corner = "╝";

    //* the character to draw at the vertical border
    std::string vertical_bar = "║";

    //* the character to draw at the horizontal border
    std::string horizontal_bar = "═";

    //* the padding to append before and after the vertical border
    std::string horizontal_padding = " ";

    //* the maximum amount of digits that can be entered
    int digits = 19;

    //* the helper text to give more information to the user and to make the program more intuitive
    std::string input_prompt_text = "Enter a number";

    //* the padding that will be added below the helper text
    int padding_below_prompt = 2;

    //* the text to render to tell the user where to enter the number
    std::string prompt = "# > ";

    //* the padding that goes on input where no inputs have been inputted yet
    std::string input_filler = "_";

    //* error to render if the input is in invalid format
    std::string invalid_input_feedback = "Invalid input";

    //* error to render if some unknown error goes wrong in the conversion
    std::string failed_conversion_feedback = "Failed conversion";

    //* error to render if the user goes over the 64 bit signed integer limit
    std::string num_too_big_error = "The number you have entered exceeds the 64-bit signed integer limit. Please try entering a smaller number.";

    //* padding to render before the error
    int padding_before_error = 2;

    //* padding to render after the error
    int padding_after_error = 2;

    //* padding below the input field
    int padding_below_input_field = 3;

    //* the title to display as a pretext to the attributes section
    std::string features_display_text = "Number features";

    //* the padding before the number attributes
    int padding_before_features = 2;

    //* padding between the number attributes
    int padding_between_features = 1;

    //* the gloabl print alignment
    std::string alignment = "center";

    //* should the screen be fully repainted
    bool fill_screen = true;

    //* the maximum width of rendering
    int max_width = 60;
};

//* Check number features class
class CheckNumberFeatures {
    public:
        //* add a number attribute
        void add_attribute(Attribute attr);
        void add_attribute(std::string label, std::function<std::string(long long)> func, bool append_label);
        void add_attribute(const char* label, std::function<std::string(long long)> func, bool append_label);

        //* render the mode using the render statistics
        int render(CNFRenderSettings render_settings, Statistics &stats);

        //* handle the inputs following the rendering
        int handle_input(CNFRenderSettings render_settings, Statistics &stats);

        //* reset all variables
        void reset();
    private:
        //* the vector storing all attributes
        std::vector<Attribute> attributes;

        //* if there is an error and needs to be printed
        bool error = false;

        //* the error message to print
        std::string error_msg;

        //* the custom keyboard input buffer
        std::string input;

        //* if the user has waited once after the error and the error can be removed in the next render cycle
        bool waited_once = false;
};


//************************************************************************************************
//************************************************************************************************

struct GraphRenderSettings {
    //* the global alignment to align the prints by
    std::string alignment = "center";

    //* padding from the top before the graph
    int padding_before_graph = 3;

    //* the maximum width of the graph. if set 0, then the maximum width is taken
    int graph_width = 0;

    //* set the height to 2/3 of the screen. needs to be re-called every update loop to make it responsive
    int graph_height = (int)((t_size.height * 2) / 3);

    //* the padding between the edges of the screen
    int graph_horizontal_padding = 3;

    //* the number of characters to skip before rendering the next character for x axis
    int x_axis_step = 4;
    //* the number of characters to skip before rendering the next character for y axis
    int y_axis_step = 2;

    //* the maximum digits allowed in the input
    int input_width = 15;

    //* the character to draw at the top left corner of the input box
    std::string top_left_corner = "╔";

    //* the character to draw at the top right corner of the input box
    std::string top_right_corner = "╗";
    
    //* the character to draw at the bottom left corner of the input box
    std::string bottom_left_corner = "╚";
    
    //* the character to draw at the bottom right corner of the input box
    std::string bottom_right_corner = "╝";

    //* the character to draw at the vertical border
    std::string vertical_bar = "║";

    //* the character to draw at the horizontal border
    std::string horizontal_bar = "═";

    //* the padding to append before and after the vertical border
    std::string horizontal_padding = " ";

    //* the padding before rendering helper text
    int padding_before_input_prompt = 2;

    //* what the helper text should render as
    std::string input_prompt_text = "Enter numerical whole number coordinates separated by a comma (x axis goes first then y axis comes later)";

    //* padding after the helper text
    int padding_after_input_prompt = 2;

    //* extra padding in case there was an error rendered
    int padding_after_error = 2;

    //* the text to guide the users where the input is
    std::string prompt = "coordinates > ";

    //* the filler in the input if no characters are entered
    std::string input_filler = "_";

    //* the error text if input does not have integers
    std::string invalid_input_feedback = "Coordinates need to be integers. Come on, man. It even says so on the instructions above.";

    //* the error message if the input has incorrect number of commas
    std::string invalid_input_format = "Forgot some commas or added too many?";

    //* the error message if the number is out of bounds of the graph
    std::string out_of_bounds_feedback = "Number out of bounds.";

    //* should the screen be fully repainted?
    bool fill_screen = true;
};

class PointPlotter {
    public:
        //* add a point to be rendered onto the graph
        void add_point(int x, int y);
        void add_point(Location2D point);

        //* render the graph
        int render(GraphRenderSettings render_settings, Statistics &stats);

        //* handle inputs after rendering
        int handle_input(GraphRenderSettings render_settings, Statistics &stats);

        //* reset the variables of the graph
        void reset_graph();
    private:
        //* the vector storing all points on the graph using a Location2D type
        std::vector<Location2D> points;

        //* private function to render the graph (excluding the goodies like input, etc.)
        void render_graph(GraphRenderSettings render_settings);

        //* the custom keyboard input buffer
        std::string input;

        //* is there an error that needs printing?
        bool error = false;

        //* the error message to be printed
        std::string error_msg;

        //* the graph dimensions (in step numbers)
        Dimension2D graph_dimension;

        //* has the user waited once after error (before removing the error text to ensure the user saw it)
        bool waited_once = false;
};


//************************************************************************************************
//************************************************************************************************

struct BSTRenderSettings {
    //* the padding from the top or above the title
    int padding_from_top = 3;

    //* the title rendering style
    std::string title_style = "ansi";

    //* the function to render the title given a style
    std::function<void(std::string)> title_renderer;

    //* padding below the title
    int padding_below_title = 4;

    //* the global alignment to align the prints to
    std::string alignment = "center";

    //* the maximum number of questions that will be asked
    int max_questions = 3;

    //* the vector explaining the rules
    std::vector<std::string> explanation;

    //* padding from the help text
    int padding_from_help = 2;

    //* the padding used to pad the left aligned text
    int padding_for_left_text = 5;

    //* the max numbers of digits allowed to enter
    int input_width = 15;

    //* the prompt to tell the user where to enter the text
    std::string prompt = "your answer > ";

    //* the character to draw at the top left corner of the input box
    std::string top_left_corner = "╔";

    //* the character to draw at the top right corner of the input box
    std::string top_right_corner = "╗";
    
    //* the character to draw at the bottom left corner of the input box
    std::string bottom_left_corner = "╚";
    
    //* the character to draw at the bottom right corner of the input box
    std::string bottom_right_corner = "╝";

    //* the character to draw at the vertical border
    std::string vertical_bar = "║";

    //* the character to draw at the horizontal border
    std::string horizontal_bar = "═";

    //* the padding to append before and after the vertical border
    std::string horizontal_padding = " ";

    //* the input filler used to replace empty input
    std::string input_filler = "_";

    //* padding to render after the question
    int padding_after_question = 2;

    //* padding below the input field
    int padding_below_input = 1;

    //* the text if the user is correct
    std::string answer_correct = "Correct answer! Took |time|.";
    
    //* the message if the answer is incorrect
    std::string answer_incorrect = "Incorrect answer! Please try again.";

    //* a bullet point to show before help text
    std::string bullet_point = "•";

    //* the message to print when the test is finished
    std::vector<std::string> test_finished;

    //* should the whole screen be repainted
    bool fill_screen = true;
};

class BrainSpeedTest {
    public:
        //* render the mode using render settings and stats variable to change stats when needs be
        void render(BSTRenderSettings render_settings, Statistics &stats);

        //* handle the inputs after rendering
        int handle_input(BSTRenderSettings render_settings, Statistics &stats);

        //* reset all variables
        void reset();
    private:
        //* the start and end time of the program
        std::chrono::steady_clock::time_point start_time;
        std::chrono::steady_clock::time_point end_time;

        //* the start and end times of individual questions
        std::chrono::steady_clock::time_point question_start;
        std::chrono::steady_clock::time_point question_end;

        //* custom keyboard input buffer
        std::string input = "";

        //* question number to render on the screen
        int question_number = 1;

        //* has the test started yet?
        bool test_started = false;

        //* does the user want to exit?
        int want_exit = false;

        //* the answer in integer form to compare with the user input
        int ans;

        //* declare the two integets to operate on
        int num1, num2 = 0;

        //* declare the operation character
        char op;

        //* the number of questions asked
        int questions_asked;

        //* the number of questions answered correctly
        int correct_answers;
};


//************************************************************************************************
//************************************************************************************************


struct MBRenderSettings {
    //* padding from the top or the padding before the title
    int padding_from_top = 4;

    //* the title rendering style
    std::string title_style = "ansi";

    //* the title rendering function which takes a style as an argument
    std::function<void(std::string)> title_renderer;

    //* the padding to print below the title
    int padding_below_title = 4;

    //* the global alignment to align the prints by
    std::string alignment = "center";

    //* the maximum digits that the program will ever ask
    int max_digits = 40;

    //* the explanation text explaining how the program works
    std::vector<std::string> explanation;

    //* padding below the help text
    int padding_from_help = 2;

    //* the maximum number of digits allowed to enter
    int input_width = max_digits;

    //* the prompt to help the user locate where to enter the number
    std::string prompt = "the number > ";

    //* the input filler used to fill blank spaces in the rendering
    std::string input_filler = "_";

    //* the character to draw at the top left corner of the input box
    std::string top_left_corner = "╔";

    //* the character to draw at the top right corner of the input box
    std::string top_right_corner = "╗";
    
    //* the character to draw at the bottom left corner of the input box
    std::string bottom_left_corner = "╚";
    
    //* the character to draw at the bottom right corner of the input box
    std::string bottom_right_corner = "╝";

    //* the character to draw at the vertical border
    std::string vertical_bar = "║";

    //* the character to draw at the horizontal border
    std::string horizontal_bar = "═";

    //* the padding to append before and after the vertical border
    std::string horizontal_padding = " ";

    //* padding after each question
    int padding_after_question = 2;

    //* padding for left aligned text from the side of the screen
    int padding_for_left_text = 5;

    //* padding before providing answer feedback
    int padding_before_feedback = 3;

    //* how a bullet point should be rendered
    std::string bullet_point = "•";

    //* text to render when the user has failed the test
    std::vector<std::string> test_failed;

    //* text to render if the user successfully finishe the text
    std::vector<std::string> test_finished;

    //* text to render if the user gave a correct answer
    std::string answer_correct = "Correct! Your score is |score|! Press any key to continue.";

    //* should the whole screen be repainted
    bool fill_screen = true;
};

class MemoryBenchmark {
    public:
        //* render the mode with the given render settings and a reference to stats to upate the stats variable later
        void render(MBRenderSettings render_settings, Statistics &stats);

        //* handle the input after finishing a rendering cycle
        int handle_input(MBRenderSettings render_settings, Statistics &stats);
        
        //* reset all variables
        void reset();
    private:
        //* the custom keyboard input buffer
        std::string input;

        //* the number of current digits to memorise
        int digits = 1;

        //* does the user want to exit?
        int want_exit = false;

        //* do we need to calculate a new question?
        bool calculate_new_num = true;

        //* is the test finished or aborted?
        bool test_finished = false;

        //* thehas the user waited once (before removing the error message)
        bool waited_once;

        //* the strig to store current number
        std::string num;
};
