#include <vector>
#include <iostream>

#include "classes.hpp"
#include "tui.hpp"
#include "utils.hpp"

//* Defining methods used by the Menu class

//* Add a new option to the menu with the label <str> and with the action <func>
void Menu::add_option(std::string str, std::function<void()> func) {
    //* Create a new entry object and set all its parameters
    Entry entry;
    entry.id = next_id;
    entry.label = str;
    entry.func = func;
    entry.interactable = true;

    //* Append the new option to the menu
    entries.emplace_back(entry);

    //* Append the next_id variable to prepare for the next interactable option
    next_id++;
}

//* Add a new Entry object to the menu
//! CAUTION: It is easy to mess up the settings and get difficult to debug results. Only use this if you know what you are doing!
void Menu::add_entry(Entry entry) {
    //* Append the entry to the inbuilt list of entries
    entries.emplace_back(entry);

    //* If the entry is interactable, then append the next_id to prepare for the next interactable entry
    if (entry.interactable) {
        next_id++;
    }
}

//* Adds a non-interactable line to the menu which displays <str>
void Menu::add_line(std::string str) {
    //* Create a new entry object and set its parameters to make the line non-interactable
    Entry entry;
    entry.label = str;
    entry.interactable = false;

    //* Append the entry to the list of menu entries
    entries.emplace_back(entry);
}

//* Add a blank line to the menu for padding.
void Menu::add_line() {
    Menu::add_line("");
}

//* Moves the selection up by <by> amount
void Menu::move_selection_up(int by) {
    if (!loop_menu_options) { //* If we are not looping through menu options, then use the simple clamp method to restrict the maximum and minimum values of the selection
        selection = std::clamp(selection - by, 0, next_id - 1);
    } else { //* Otherwise, if loop_menu_options is set, then use this more complex method to navigate the menu
        selection = ((selection - by) < 0) ? next_id - 1 : selection - by;
    }
}

//* Moves the selection up by one
void Menu::move_selection_up() {
    Menu::move_selection_up(1);
}

//* Moves the selection down by <by> amount
void Menu::move_selection_down(int by) {
    if (!loop_menu_options) { //* If we are not looping through menu options, then use the simple clamp method to restrict the maximum and minimum values of the selection
        selection = std::clamp(selection + by, 0, next_id - 1);
    } else { //* Otherwise, if loop_menu_options is set, then use this more complex method to navigate the menu
        selection = ((selection + by) > next_id - 1) ? 0 : selection + by;
    }
}

//* Moves the selection down by one
void Menu::move_selection_down() {
    Menu::move_selection_down(1);
}

//* Set the state of the loop_menu_options variable
void Menu::set_entry_loop(bool val) {
    loop_menu_options = val;
}

//* Render the menu using given render settings 
void Menu::render(MenuRenderSettings render_settings) {
    for (auto& e : entries) {
        //* Align the output to the alignment as specified by the alignment setting
        align(render_settings.alignment);

        //* Create a label to be displayed for this menu entry and pad it according to the selection size as specified in the settings
        std::string label;
        label.append(padded_str(e.label, render_settings.selection_size, ""));

        //* Set the normal foreground and background color
        fg_color(render_settings.fg_color_hex.c_str());
        bg_color(render_settings.bg_color_hex.c_str());

        if (selection == e.id) { //* If selection matches the choice ID of the option, then draw the entry using highlighted foreground and background settings
            //* Calculate the left and right padding required
            std::string pl = extend_string(" ", calculate_padding_left(label));
            std::string pr = extend_string(" ", calculate_padding_right(label));

            if (render_settings.alignment == ALIGN.LEFT) { //* If the menu is left-aligned
                //* Change the foreground and background color to highlighted colors because this entry is highlighted
                fg_color(render_settings.fg_color_highlighted_hex.c_str());
                bg_color(render_settings.bg_color_highlighted_hex.c_str());

                //* Output the label
                std::cout << label;

                //* Revert the colors to normal foreground and background colors
                fg_color(render_settings.fg_color_hex.c_str());
                bg_color(render_settings.bg_color_hex.c_str());

                //* Print the left padding, right padding, and theending string
                std::cout << pl << pr << render_settings.end;
            } else if (render_settings.alignment == ALIGN.CENTER) { //* If the menu is center-aligned
                //* Print out the left padding
                std::cout << pl;

                //* Change the foreground and background color to highlighted colors because this entry is highlighted
                fg_color(render_settings.fg_color_highlighted_hex.c_str());
                bg_color(render_settings.bg_color_highlighted_hex.c_str());

                //* Output the label
                std::cout << label;

                //* Revert the colors to normal foreground and background colors
                fg_color(render_settings.fg_color_hex.c_str());
                bg_color(render_settings.bg_color_hex.c_str());

                //* Print the right padding then print out the ending string
                std::cout << pr << render_settings.end;
            } else if (render_settings.alignment == ALIGN.RIGHT) { //* If the menu is right-aligned
                //* Print out the left and right padding
                std::cout << pl << pr;

                //* Change the foreground and background color to highlighted colors because this entry is highlighted
                fg_color(render_settings.fg_color_highlighted_hex.c_str());
                bg_color(render_settings.bg_color_highlighted_hex.c_str());

                //* Output the label
                std::cout << label;

                //* Revert the colors to normal foreground and background colors
                fg_color(render_settings.fg_color_hex.c_str());
                bg_color(render_settings.bg_color_hex.c_str());

                //* Print the ending string
                std::cout << render_settings.end;
            } else { //* Otherwise, the alignment is in an invalid state
                std::cout << "Invalid alignment state";
                exit(0);
            }
        } else { //* The entry is not selected. Use the normal method to padded-print this option
            print(label);
        }

        for (int i = 0; i < render_settings.line_padding; i++) { //* Print <line_padding> lines to act as a buffer between menu entries
            //* Print <line_padding_string> out between the menu entries as padding
            print(render_settings.line_padding_string);
        }
    }

    if (render_settings.fill_screen) { //* If fill_screen setting is set, then fill the screen with blank prints
        Location2D xy = wherexy();
        while (xy.y < t_size.height - 1) {
            xy = wherexy();
            print();
        }
    }
}

//* Renders menu with default settings
void Menu::render() {
    MenuRenderSettings render_settings;
    Menu::render(render_settings);
}

//* Handles the keyboard inputs
//* Typically used after rendering menu
void Menu::handle_input() {
    Key k = get_key();
    if (k == KEY_UP_ARROW) {
        move_selection_up();
    } else if (k == KEY_DOWN_ARROW) {
        move_selection_down();
    } else if (k == KEY_ENTER) {
        for (auto& e : entries) {
            if (e.id == selection) {
                e.func();
            }
        }
    } else if (k == KEY_Q) {
        exit_program();
    }
}


//************************************************************************************************
//************************************************************************************************

//* Definition for CheckNumberFeatures functions

//* Add a number attribute to show to the user
void CheckNumberFeatures::add_attribute(Attribute attr) {
    attributes.emplace_back(attr);
}

//* Add a number attribute to show to the user but pass in the required parameters to the function
void CheckNumberFeatures::add_attribute(std::string label, std::function<std::string()> func, bool append_label) {
    add_attribute(Attribute {label, func, append_label});
}

void CheckNumberFeatures::render() {
    //* Clear the screen to indicate to the user that we have entered a new section of the program
    clear();

    //* Define an input string that will hold all the entered information
    std::string input;

    for (;;) {
        //* Set the cursor to home (0, 0)
        set_cursor_position();

        //* Align left so the padding works properly
        align_left();

        //* Build the input line by padding it with blanks as indicated by the render settings
        std::string input_line = padded_str(input, render_settings.input_filler, render_settings.digits, "");

        //* Align by the provided alignment setting
        align(render_settings.alignment);

        //* Print spaces before the input
        print_loop("\n", render_settings.padding_from_top, "");

        //* Render the text to prompt the user to enter a number
        print(render_settings.input_prompt_text);

        if (error) {
            //* Print padding below the prompt
            print_loop("\n", render_settings.padding_before_error, "");

            //* Change the foreground and background color
            bg_color(render_settings.error_bg_color);
            fg_color(render_settings.error_fg_color);

            //* Print out the error message
            print(error_msg);

            //* Revert the change in foreground and background color
            bg_color(render_settings.bg_color);
            fg_color(render_settings.fg_color);

            //* Print out the padding below the error message
            print_loop("\n", render_settings.padding_after_error, "");

            //* Wait for a user input
            // getch();

            //* Then clear the error, error message, and the input box
            error = false;
            error_msg = "";
            input = "";
        } else {
            //* Add padding below the prompt
            print_loop("\n", render_settings.padding_below_prompt);
        }

        //* Build the first line of the input
        //TODO: Unicode characters will break the pre-padding; only ASCII characters work
        std::string top_line;
        top_line.append(render_settings.top_left_corner);
        top_line.append(extend_string(render_settings.horizontal_bar, render_settings.prompt.length() + (2 * render_settings.horizontal_padding.length())));
        top_line.append(padded_str("", render_settings.horizontal_bar, render_settings.digits, ""));
        top_line.append(render_settings.top_right_corner);

        std::string middle_line;
        middle_line.append(render_settings.vertical_bar);
        middle_line.append(render_settings.horizontal_padding);
        middle_line.append(render_settings.prompt);
        middle_line.append(input_line);
        middle_line.append(render_settings.horizontal_padding);
        middle_line.append(render_settings.vertical_bar);

        std::string bottom_line;
        bottom_line.append(render_settings.bottom_left_corner);
        bottom_line.append(extend_string(render_settings.horizontal_bar, render_settings.prompt.length() + (2 * render_settings.horizontal_padding.length())));
        bottom_line.append(padded_str("", render_settings.horizontal_bar, render_settings.digits, ""));
        bottom_line.append(render_settings.bottom_right_corner);

        print(top_line);
        print(middle_line);
        print(bottom_line);

        handle_input(input);
    }
}

void CheckNumberFeatures::handle_input(std::string input) {
    Key key = get_key();
    if (key == KEY_BACKSPACE) {
        if (!input.empty()) {
            input.pop_back();
            // continue;
        }
    } else if (input.length() < render_settings.digits && key != KEY_ENTER) {
        input += key.key;
    } else if (key == KEY_ENTER) {
        long long num;
        try {
            std::size_t pos;
            num = std::stoll(input, &pos);
            if (pos < input.size()) {
                throw "Words in input";
            }
        } catch (...) {
            // set_cursor_position(Location2D {0, 12});
            error = true;
            error_msg = render_settings.invalid_input_feedback;
            // fg_color("#ff9e64");
            // print("Seriously? I asked you to do ONE thing, enter a whole number.");
            // fg_color("#f7768e");
            // getch();
            // input = "";
            // continue;
        }

        print_loop("\n", render_settings.padding_below_input_field, "");
        
        // std::string num_feat;
        // num_feat.append(">--------------------< NUMBER FEATURES OF ");
        // num_feat.append(std::to_string(num));
        // num_feat.append(" >--------------------<");

        // print(num_feat);
        print(render_settings.features_display_text);
        print_loop("\n", render_settings.padding_between_features, "");
        
        for (auto a : attributes) {
            // std::string out = a.func();
            std::string out;
            if (a.append_label) {
                out.append(a.label);
                out.append(": ");
            }
            out.append(a.func());
            print(out);
        }

        getch();
        return;
    }
}
