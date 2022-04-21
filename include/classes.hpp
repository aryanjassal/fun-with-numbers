#include <functional>
#include <iostream>
#include <vector>

#include "tui.hpp"

//TODO: GET THE COLORRGB COLORS WORKING IN THE RENDERER SETTINGS

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

//************************************************************************************************
//************************************************************************************************

//* Attribute struct for adding new attributes to output of check number features
struct Attribute {
    std::string label;
    std::function<std::string()> func;
    bool append_label;
};

//* Render settings for the Check Number Features renderer
struct CNFRenderSettings {
    int digits = 19;
    std::string top_left_corner = "╔";
    std::string top_right_corner = "╗";
    std::string bottom_left_corner = "╚";
    std::string bottom_right_corner = "╝";
    std::string vertical_bar = "║";
    std::string horizontal_bar = "═";
    std::string horizontal_padding = " ";
    int padding_from_top = 3;
    std::string input_prompt_text = "Enter a number";
    int padding_below_prompt = 2;
    std::string prompt = "# > ";
    std::string input_filler = "_";
    struct ColorRGB fg_color = { 255, 255, 255 };
    struct ColorRGB bg_color = { 0, 0, 0 };
    struct ColorRGB error_fg_color = { 255, 0, 0 };
    struct ColorRGB error_bg_color = { 0, 0, 0 };
    std::string error_fg_color_hex = "#ff0000";
    std::string error_bg_color_hex = "#000000";
    std::string fg_color_hex = "#ffffff";
    std::string bg_color_hex = "#000000";
    std::string invalid_input_feedback = "Invalid input";
    std::string failed_conversion_feedback = "Failed conversion";
    bool allow_empty_input = false;
    std::string empty_input_feedback = "Empty input";
    int padding_before_error = 2;
    int padding_after_error = 2;
    int padding_below_input_field = 3;
    std::string features_display_text = "Number features";
    int padding_before_features = 1;
    int padding_between_features = 1;
    std::string alignment = "center";
};

//* Check number features class
class CheckNumberFeatures {
    public:
        void add_attribute(Attribute attr);
        void add_attribute(std::string label, std::function<std::string()> func, bool append_label);
        void add_attribute(const char* label, std::function<std::string()> func, bool append_label);
        int render(CNFRenderSettings render_settings);
        int render();
        int handle_input(CNFRenderSettings render_settings);
    private:
        std::vector<Attribute> attributes;
        bool error = false;
        std::string error_msg;
        std::string input;
        // CNFRenderSettings render_settings;
};
