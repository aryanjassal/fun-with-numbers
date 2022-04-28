#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <math.h>

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
    entry.id = -1;
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
    set_cursor_position();
    //* Set the normal foreground and background color
    fg_color(g_fg_color);
    bg_color(g_bg_color);

    print_loop("", render_settings.padding_above_title);
    render_settings.title_renderer(render_settings.title_style);
    print_loop ("", render_settings.padding_below_title);

    for (auto& e : entries) {
        //* Align the output to the alignment as specified by the alignment setting
        align(render_settings.alignment);

        //* Create a label to be displayed for this menu entry and pad it according to the selection size as specified in the settings
        std::string label;
        label.append(padded_str(e.label, render_settings.selection_size, ""));

        if (selection == e.id) { //* If selection matches the choice ID of the option, then draw the entry using highlighted foreground and background settings
            //* Calculate the left and right padding required
            std::string pl = extend_string(" ", calculate_padding_left(label));
            std::string pr = extend_string(" ", calculate_padding_right(label));

            if (render_settings.alignment == ALIGN.LEFT) { //* If the menu is left-aligned
                //* Change the foreground and background color to highlighted colors because this entry is highlighted
                fg_color(g_fg_color_highlighted);
                bg_color(g_bg_color_highlighted);

                //* Output the label
                std::cout << label;

                //* Revert the colors to normal foreground and background colors
                fg_color(g_fg_color);
                bg_color(g_bg_color);

                //* Print the left padding, right padding, and theending string
                std::cout << pl << pr << render_settings.end;
            } else if (render_settings.alignment == ALIGN.CENTER) { //* If the menu is center-aligned
                //* Print out the left padding
                std::cout << pl;

                //* Change the foreground and background color to highlighted colors because this entry is highlighted
                fg_color(g_fg_color_highlighted);
                bg_color(g_bg_color_highlighted);
                //* Output the label
                std::cout << label;

                //* Revert the colors to normal foreground and background colors
                fg_color(g_fg_color);
                bg_color(g_bg_color);

                //* Print the right padding then print out the ending string
                std::cout << pr << render_settings.end;
            } else if (render_settings.alignment == ALIGN.RIGHT) { //* If the menu is right-aligned
                //* Print out the left and right padding
                std::cout << pl << pr;

                //* Change the foreground and background color to highlighted colors because this entry is highlighted
                fg_color(g_fg_color_highlighted);
                bg_color(g_bg_color_highlighted);

                //* Output the label
                std::cout << label;

                //* Revert the colors to normal foreground and background colors
                fg_color(g_fg_color);
                bg_color(g_bg_color);

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

    if (render_settings.fill_screen) fill_screen();
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
void CheckNumberFeatures::add_attribute(std::string label, std::function<std::string(long long)> func, bool append_label) {
    add_attribute(Attribute {label, func, append_label});
}

//* Add a number attribute to show to the user but pass in the required parameters to the function
void CheckNumberFeatures::add_attribute(const char* label, std::function<std::string(long long)> func, bool append_label) {
    add_attribute(Attribute {(std::string)label, func, append_label});
}

int CheckNumberFeatures::render(CNFRenderSettings render_settings, Statistics &stats) {
    //* Clear the screen to indicate to the user that we have entered a new section of the program
    bg_color(g_bg_color);
    fg_color(g_fg_color);


    for (;;) {
        //* Set the cursor to home (0, 0)
        set_cursor_position();

        //* Print the title and the appropriate padding
        print_loop("", render_settings.padding_from_top);
        render_settings.title_renderer(render_settings.title_style);
        print_loop("", render_settings.padding_below_title);

        //* Align left so the padding works properly
        align_left();

        //* Build the input line by padding it with blanks as indicated by the render settings
        std::string input_line = padded_str(input, render_settings.input_filler, render_settings.digits, "");

        //* Align by the provided alignment setting
        align(render_settings.alignment);

        //* Print spaces before the input
        print_loop("", render_settings.padding_from_top, "");

        //* Render the text to prompt the user to enter a number
        print(render_settings.input_prompt_text);

        if (error) {
            //* Print padding below the prompt
            print_loop("", render_settings.padding_before_error, "");

            //* Change the foreground and background color
            bg_color(g_bg_color_error);
            fg_color(g_fg_color_error);

            //* Print out the error message
            print(error_msg);

            //* Revert the change in foreground and background color
            bg_color(g_bg_color);
            fg_color(g_fg_color);

            //* Print out the padding below the error message
            print_loop("", render_settings.padding_after_error, "");

            //* Clear the input and recalculate the padded input too
            input = "";
            input_line = padded_str(input, render_settings.input_filler, render_settings.digits, "");
            error = false;
            error_msg = "";
            waited_once = false;
        } else {
            //* Add padding below the prompt
            print_loop("", render_settings.padding_below_prompt);
        }

        //* Build the first line of the input
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

        if (render_settings.fill_screen) set_cursor_position(fill_screen());

        return handle_input(render_settings, stats);
    }
}

int CheckNumberFeatures::handle_input(CNFRenderSettings render_settings, Statistics &stats) {
    Key key = get_key();

    if (waited_once) {
        input = "";
        waited_once = false;
    }

    if (key == KEY_BACKSPACE) {
        if (!input.empty()) {
            input.pop_back();
        }
    } else if (key == KEY_ENTER) {
        if (waited_once && !input.empty()) {
            input = "";
            waited_once = false;
            return 0;
        }
        if (!waited_once && !input.empty()) {
            waited_once = true;
        }

        if (input.empty()) {
            return 0;
        }

        long long num;
        try {
            std::size_t pos;
            num = std::stoll(input, &pos);
            if (pos < input.size()) {
                throw "Words in input";
            }
        } catch (std::out_of_range &err) {
            error = true;
            error_msg = render_settings.num_too_big_error;
            return 0;
        } catch (...) {
            error = true;
            error_msg = render_settings.invalid_input_feedback;
            return 0;
        }

        print_loop("", render_settings.padding_below_input_field);
        print(render_settings.features_display_text.replace(render_settings.features_display_text.find("|num|"), 5, input), "");
        print_loop("", render_settings.padding_before_features);

        for (auto a : attributes) {
            std::string out;
            if (a.append_label) {
                out.append(a.label);
                out.append(": ");
            }
            out.append(a.func(num));
            print(out);

            print_loop("", render_settings.padding_between_features);
        }

        long long num_entries = stats.get_stat(NUMBERS_ENTERED).val;
        long long total = stats.get_stat(TOTAL_OF_NUMBERS).val;
        long long average;

        long long smallest_num = stats.get_stat(SMALLEST_NUMBER_ENTERED).val;
        long long largest_num = stats.get_stat(LARGEEST_NUMBER_ENTERED).val;

        if (total == 0) {
            largest_num = num;
            smallest_num = num;
        }
        if (num < smallest_num) {
            smallest_num = num;
        }
        if (num > largest_num) {
            largest_num = num;
        }

        num_entries += 1;
        total += num;

        if (total > 0 && num_entries > 0) {
            average = (int)(total / num_entries);
        }
        if (num_entries < 0) {
            throw std::runtime_error("Total numbers processed cannot be negative");
        }

        stats.set_stat(NUMBERS_ENTERED, num_entries);
        stats.set_stat(TOTAL_OF_NUMBERS, total);
        stats.set_stat(AVERAGE_OF_NUMBERS, average);
        stats.set_stat(SMALLEST_NUMBER_ENTERED, smallest_num);
        stats.set_stat(LARGEEST_NUMBER_ENTERED, largest_num);

        if (render_settings.fill_screen) fill_screen();

        get_key();
        input = "";

        return 0;
    } else if (key == KEY_ESCAPE) {
        return 1;
    } else if (input.length() < render_settings.digits && std::count(BASIC_KEYS.begin(), BASIC_KEYS.end(), key)) {
        input += key.key;
    }
    return 0;
}

void CheckNumberFeatures::reset() {
    input = "";
}


//*****************************************************************************************************
//*****************************************************************************************************


void Statistics::add_stat(Stat stat) {
    stat.id == next_id;
    stats.emplace_back(stat);
    next_id++;
}

void Statistics::add_stat(std::string label, long long val, std::string section_id) {
    Stat stat;
    stat.id = next_id;
    stat.label = label;
    stat.val = val;
    stat.units = "";
    stat.section = section_id;
    stat.rendered = true;
    stats.emplace_back(stat);
    next_id++;
}

void Statistics::add_stat(std::string label, std::string section_id, std::string units) {
    Stat stat;
    stat.id = next_id;
    stat.label = label;
    stat.val = 0;
    stat.units = units;
    stat.section = section_id;
    stat.rendered = true;
    stats.emplace_back(stat);
    next_id++;
}

void Statistics::add_stat(std::string label, long long val, std::string section_id, std::string units) {
    Stat stat;
    stat.id = next_id;
    stat.label = label;
    stat.val = val;
    stat.units = units;
    stat.section = section_id;
    stat.rendered = true;
    stats.emplace_back(stat);
    next_id++;
}

void Statistics::add_stat(std::string label, std::string section_id) {
    Stat stat;
    stat.id = next_id;
    stat.label = label;
    stat.val = 0;
    stat.section = section_id;
    stat.units = "";
    stat.rendered = true;
    stats.emplace_back(stat);
    next_id++;
}

void Statistics::add_stat(std::string label, long long val, std::string section_id, bool rendered) {
    Stat stat;
    stat.rendered = rendered;
    stat.id = next_id;
    stat.label = label;
    stat.val = val;
    stat.units = "";
    stat.section = section_id;
    stats.emplace_back(stat);
    next_id++;
}

void Statistics::add_stat(std::string label, std::string section_id, std::string units, bool rendered) {
    Stat stat;
    stat.rendered = rendered;
    stat.id = next_id;
    stat.label = label;
    stat.val = 0;
    stat.units = units;
    stat.section = section_id;
    stats.emplace_back(stat);
    next_id++;
}

void Statistics::add_stat(std::string label, long long val, std::string section_id, std::string units, bool rendered) {
    Stat stat;
    stat.rendered = rendered;
    stat.id = next_id;
    stat.label = label;
    stat.val = val;
    stat.units = units;
    stat.section = section_id;
    stats.emplace_back(stat);
    next_id++;
}

void Statistics::add_stat(std::string label, std::string section_id, bool rendered) {
    Stat stat;
    stat.rendered = rendered;
    stat.id = next_id;
    stat.label = label;
    stat.val = 0;
    stat.section = section_id;
    stat.units = "";
    stats.emplace_back(stat);
    next_id++;
}

struct Stat Statistics::get_stat(int id) {
        for (auto s : stats) {
        if (s.id == id) {
            return s;
        }
    }
    throw std::invalid_argument("Stat with ID not found");
}

void Statistics::set_stat(int id, long long val) {
    stats.at(id - 1).val = val;
    save_stats();
}

void Statistics::save_stats(std::string file_name) {
    std::ofstream file;
    file.open(file_name);
    for (auto stat : stats) {
        file << stat.id << ":" << stat.val << ":" << stat.section << "\n";
    }
    file.close();
}

void Statistics::save_stats() {
    save_stats("statistics.save");
}

void Statistics::load_stats(std::string file_name) {
    std::ifstream file;
    file.open(file_name);

    try {
        for (auto& stat : stats) {
            std::string line;
            getline(file, line, '\n');
            std::vector<std::string> id_val_form = split(line, ':');

            Stat s;
            try {
                s = get_stat(std::stoi(id_val_form.at(0)));
            } catch (...) {
                continue;
            }

            stat.val = std::stoll(id_val_form.at(1));
            stat.section = id_val_form.at(2);
        }
    } catch (...) {
        clear();
        print("Save file corrupt. Remove the " + file_name + " file and re-launch the program.");
        reset_formatting();
        print();
        exit(1);
    }
    file.close();
}

void Statistics::load_stats() {
    load_stats("statistics.save");
}

int Statistics::render(StatsRenderSettings render_settings) {
    bg_color(g_bg_color);
    fg_color(g_fg_color);
    set_cursor_position();

    align(render_settings.alignment);
    print_loop("", render_settings.padding_from_top);
    render_settings.title_renderer(render_settings.title_rendering_style);
    print_loop("", render_settings.padding_below_title);

    std::string section_blank_line = render_settings.vertical_bar + padded_str("", render_settings.section_width - 4, "") + render_settings.vertical_bar;
    std::string section_bottom_line = render_settings.bottom_left_corner + extend_string(render_settings.horizontal_bar, render_settings.section_width - 4) + render_settings.bottom_right_corner + "\n";

    std::string o_sec = "";
    for (auto s : stats) {
        if (s.rendered) {
            std::string section;

            std::string out;
            if (render_settings.render_label) {
                out.append(s.label);
                out.append(": ");
            }

            if (!s.units.empty()) {
                if (s.units == "time|seconds") {
                    out.append(seconds_to_string(s.val));   
                } else if (s.units == "unit|percentage") {
                    out.append(std::to_string(s.val) + "%");
                }
            } else {
                out.append(std::to_string(s.val));
            }

            align_center();

            if (s.section != o_sec) {
                if (s.id != stats.at(0).id) {
                    print_loop(section_blank_line, render_settings.padding_between_lines, "");
                    print(section_bottom_line, "");
                    print();
                }
                align_center();
                section.append(render_settings.top_left_corner + padded_str(render_settings.text_start + " " + s.section + " " + render_settings.text_end, render_settings.horizontal_bar, render_settings.section_width - 4, "") + render_settings.top_right_corner + "\n");
                section.append(section_blank_line + "\n");
                section.append(render_settings.vertical_bar + padded_str(out, render_settings.section_width - 4, "") + render_settings.vertical_bar);
            } else {
                section.append(render_settings.vertical_bar + padded_str(out, render_settings.section_width - 4, "") + render_settings.vertical_bar);
                print_loop(section_blank_line, render_settings.padding_between_lines);
            }
            o_sec = s.section;   
            print(section, "");
        }
    }

    print_loop(section_blank_line, render_settings.padding_between_lines, "");
    print(section_bottom_line, "");

    align_center();
    if (render_settings.fill_screen) fill_screen();

    get_key();
    return 1;
}

int Statistics::render() {
    StatsRenderSettings render_settings;
    return render(render_settings);
}

void Statistics::reset() {
    for (int i = 1; i <= stats.size(); i++) {
        set_stat(i, 0);
    }
}


//*****************************************************************************************************
//*****************************************************************************************************

void PointPlotter::add_point(Location2D point) {
    points.emplace_back(point);
}

void PointPlotter::add_point(int x, int y) {
    points.emplace_back(Location2D {x, y});
}

int PointPlotter::render(GraphRenderSettings render_settings, Statistics &stats) {
    Dimension2D origin;
    origin.width = -1;
    origin.height = -1;
    graph_dimension = origin;

    bg_color(g_bg_color);
    fg_color(g_fg_color);
    set_cursor_position();

    print_loop("", render_settings.padding_before_graph);
    render_graph(render_settings);

    align(render_settings.alignment);

    print_loop("", render_settings.padding_before_input_prompt);
    print(render_settings.input_prompt_text);
    print_loop("", render_settings.padding_after_input_prompt);

    align_left();
    std::string input_line = padded_str(input, render_settings.input_filler, render_settings.input_width, "");
    align(render_settings.alignment);

    //* Build the first line of the input
    //!: Unicode characters will break the pre-padding; only ASCII characters work
    std::string top_line;
    top_line.append(render_settings.top_left_corner);
    top_line.append(extend_string(render_settings.horizontal_bar, render_settings.prompt.length() + (2 * render_settings.horizontal_padding.length())));
    top_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
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
    bottom_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
    bottom_line.append(render_settings.bottom_right_corner);

    if (error) {
        //* Change the foreground and background color
        bg_color(g_bg_color_error);
        fg_color(g_fg_color_error);

        //* Print out the error message
        print(error_msg);

        //* Revert the change in foreground and background color
        bg_color(g_bg_color);
        fg_color(g_fg_color);

        //* Print out the padding below the error message
        print_loop("", render_settings.padding_after_error, "");

        //* Clear the input and recalculate the padded input too
        input = "";

        align_left();
        input_line = padded_str(input, render_settings.input_filler, render_settings.input_width, "");
        align(render_settings.alignment);

        error = false;
        error_msg = "";
    }

    print(top_line);
    print(middle_line);
    print(bottom_line);

    align_center();
    if (render_settings.fill_screen) fill_screen();

    return handle_input(render_settings, stats);
}

void PointPlotter::render_graph(GraphRenderSettings render_settings) {
    int graph_width = render_settings.graph_width <= 0 ? t_size.width : render_settings.graph_width;

    std::string line_padding = padded_str(" ", render_settings.graph_horizontal_padding, "");
    std::string top_line;
    top_line = extend_string(render_settings.horizontal_bar, graph_width - 5 - (render_settings.graph_horizontal_padding * 2) - line_padding.size());
    align_center();
    print(line_padding + render_settings.top_left_corner + top_line + render_settings.top_right_corner);

    for (int i = render_settings.graph_height; i >= 0; i--) {
        std::string in_graph = "";
        if (i % render_settings.y_axis_step == 0) {
            graph_dimension.height++;
            align_right();
            std::string line_no = padded_str(std::to_string(i / render_settings.y_axis_step) + render_settings.vertical_bar, render_settings.graph_horizontal_padding, "");

            for (int j = 0; j <= graph_width - 4 - (render_settings.graph_horizontal_padding * 2) - line_no.size(); j++) {
                if (j % render_settings.x_axis_step == 0) {

                    Location2D point;
                    point.x = j / render_settings.x_axis_step;
                    point.y = i / render_settings.y_axis_step;

                    if (std::count(points.begin(), points.end(), point)) {
                        in_graph.append("x");
                    } else {
                        in_graph.append(" ");
                    }
                } else {
                    in_graph.append(" ");
                }
            }
            align_center();
            print(line_no + in_graph + render_settings.vertical_bar);
        } else {
            align_right();
            std::string line_no = padded_str(render_settings.vertical_bar, render_settings.graph_horizontal_padding, "");
            for (int j = 0; j <= graph_width - 4 - (render_settings.graph_horizontal_padding * 2) - line_no.size(); j++) {
                in_graph.append(" ");
            }
            align_center();
            print(line_no + in_graph + render_settings.vertical_bar);
        }
    }

    std::string bottom_line;
    bottom_line = extend_string(render_settings.horizontal_bar, graph_width - 5 - (render_settings.graph_horizontal_padding * 2) - line_padding.size());
    align_center();
    print(line_padding + render_settings.bottom_left_corner + bottom_line + render_settings.bottom_right_corner);

    std::string x_axis_numbers;
    for (int i = 0; i <= graph_width - (5 * render_settings.graph_horizontal_padding); i++) {
        if (i % render_settings.x_axis_step == 0) {
            graph_dimension.width++;
            std::string temp_num;
            align_right();
            temp_num = padded_str(std::to_string(i / render_settings.x_axis_step), render_settings.x_axis_step, "");

            x_axis_numbers.append(temp_num);
        }
    }
    align_left();
    print(line_padding + extend_string(" ", render_settings.graph_horizontal_padding - 1) + x_axis_numbers);
}

int PointPlotter::handle_input(GraphRenderSettings render_settings, Statistics &stats) {
    Key key = get_key();

    if (waited_once) {
        input = "";
        waited_once = false;
    }

    if (key == KEY_BACKSPACE) {
        if (!input.empty()) {
            input.pop_back();
        }
    } else if (key == KEY_ENTER) {
        if (waited_once && !input.empty()) {
            input = "";
            waited_once = false;
            return 0;
        }
        if (!waited_once && !input.empty()) {
            waited_once = true;
        }

        if (input.empty()) {
            return 0;
        }

        input = strip(input);
        std::vector<std::string> c = split(input, ',');

        if (c.size() != 2) {
            error = true;
            error_msg = render_settings.invalid_input_format;
            return 0;
        }

        Location2D point;
        try {
            std::size_t pos1, pos2 = 0;
            point.x = std::stoi(c.at(0), &pos1);
            point.y = std::stoi(c.at(1), &pos2);

            if (pos1 < c.at(0).size() || pos2 < c.at(1).size()) {
                throw "Words in input";
            }
        } catch (...) {
            error = true;
            error_msg = render_settings.invalid_input_feedback;
            return 0;
        }

        if (point.x < 0 || point.x > graph_dimension.width || point.y < 0 || point.y > graph_dimension.height) {
            error = true;
            error_msg = render_settings.out_of_bounds_feedback;
            return 0;
        }

        points.emplace_back(point);

        int coordinates_plotted = stats.get_stat(6).val;
        coordinates_plotted++;
        stats.set_stat(COORDINATE_ENTERED, coordinates_plotted);

        return 0;
    } else if (key == KEY_ESCAPE) {
        return 1;
    } else if (input.length() < render_settings.input_width && std::count(BASIC_KEYS.begin(), BASIC_KEYS.end(), key)) {
        input += key.key;
    }
    return 0;
}

void PointPlotter::reset_graph() {
    points.clear();
    input = "";
    waited_once = false;
}



//************************************************************************************************
//************************************************************************************************

void BrainSpeedTest::render(BSTRenderSettings render_settings, Statistics &stats) {
    fg_color(g_fg_color);
    bg_color(g_bg_color);
    set_cursor_position();

    align(render_settings.alignment);
    print_loop("", render_settings.padding_from_top);
    render_settings.title_renderer(render_settings.title_style);
    print_loop("", render_settings.padding_below_title);

    print("  Instructions:");
    print();
    align_left();
    for (auto s : render_settings.explanation) {
        print(basic_text_wrapping(extend_string(' ', render_settings.padding_for_left_text) + "• " + replace(s, "|num|", std::to_string(render_settings.max_questions))));
        print();
    }
    print_loop("\n", render_settings.padding_from_help);

    align(render_settings.alignment);
    if (render_settings.fill_screen) fill_screen();

    Key k = get_key();
    if (k == KEY_ESCAPE) return;

    start_time = std::chrono::steady_clock::now();
    int old_i = -1;

    for (int i = 0; i < render_settings.max_questions; i++) {
        num1 = random_number(10, 30, 5);
        num2 = random_number(10, 30, 99);
        int operation = random_number(0, 2, 8);

        switch (operation) {
            case 0: op = '+'; ans = num1 + num2; break;
            case 1: op = '-'; ans = num1 - num2; break;
            // case 2: op = '*'; ans = num1 * num2; break;
            // case 3: op = '/';
            default: throw "Operation conversion error";
        }



        for (;;) {
            set_cursor_position();

            print_loop("", render_settings.padding_from_top);
            render_settings.title_renderer(render_settings.title_style);
            print_loop("", render_settings.padding_below_title);

            align(render_settings.alignment);

            print("(" + std::to_string(question_number) + ") " + std::to_string(num1) + " " + op + " " + std::to_string(num2) + " " + "=" + " " + "?");
            if (i != old_i) question_start = std::chrono::steady_clock::now();
            old_i = i;

            print_loop("", render_settings.padding_after_question);

            align_left();
            std::string input_line = padded_str(input, render_settings.input_filler, render_settings.input_width, "");
            align(render_settings.alignment);

            std::string top_line;
            top_line.append(render_settings.top_left_corner);
            top_line.append(extend_string(render_settings.horizontal_bar, render_settings.prompt.length() + (2 * render_settings.horizontal_padding.length())));
            top_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
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
            bottom_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
            bottom_line.append(render_settings.bottom_right_corner);

            print(top_line);
            print(middle_line);
            print(bottom_line);

            if (render_settings.fill_screen) fill_screen();

            want_exit = handle_input(render_settings, stats);
            if (want_exit != 0) break;
        }
        if (want_exit == 1) break;
    }

    if (want_exit == 1) {
        set_cursor_position();
        end_time = std::chrono::steady_clock::now();

        print_loop("", render_settings.padding_from_top);
        render_settings.title_renderer(render_settings.title_style);
        print_loop("", render_settings.padding_below_title);

        align(render_settings.alignment);

        print(basic_text_wrapping("Test aborted. Press any key to return to the main menu. Your score or progress will not be saved."));

        if (render_settings.fill_screen) fill_screen();

        get_key();
        return;
    } else {
        //* On test clear
        set_cursor_position();
        end_time = std::chrono::steady_clock::now();

        print_loop("", render_settings.padding_from_top);
        render_settings.title_renderer(render_settings.title_style);
        print_loop("", render_settings.padding_below_title);

        align(render_settings.alignment);
        long long time_taken = std::chrono::duration_cast<std::chrono::seconds> (end_time - start_time).count();

        for (auto s : render_settings.test_finished) {
            print(basic_text_wrapping(replace(s, "|time|", seconds_to_string(time_taken)) + "\n"));
        }

        long long q_all = stats.get_stat(BRAIN_SPEED_TOTAL_QUESTIONS).val;
        long long q_correct = stats.get_stat(BRAIN_SPEED_CORRECT_ANSWERS).val;
        long long score = stats.get_stat(BRAIN_SPEED_TEST_SCORE).val;
        q_all += questions_asked;
        q_correct += correct_answers;
        stats.set_stat(BRAIN_SPEED_TOTAL_QUESTIONS, q_all);
        stats.set_stat(BRAIN_SPEED_CORRECT_ANSWERS, q_correct);

        int percentage = 0;
        if (q_all != 0) {
            percentage = (int)(((float)(q_correct) / (float)(q_all)) * 100);
        }
        stats.set_stat(BRAIN_SPEED_ACCURACY_PERCENTAGE, percentage);

        if (time_taken < score || score == 0) {
            stats.set_stat(BRAIN_SPEED_TEST_SCORE, time_taken);
        }

        if (render_settings.fill_screen) fill_screen();

        get_key();
    }
}

int BrainSpeedTest::handle_input(BSTRenderSettings render_settings, Statistics &stats) {
    Key key = get_key();

    if (key == KEY_BACKSPACE) {
        if (!input.empty()) {
            input.pop_back();
        }
    } else if (key == KEY_ESCAPE) {
        return 1;
    } else if (key == KEY_ENTER) {
        try {
            if (std::stoll(input) == ans) {
                question_end = std::chrono::steady_clock::now();

                questions_asked++;
                correct_answers++;

                set_cursor_position();

                print_loop("", render_settings.padding_from_top);
                render_settings.title_renderer(render_settings.title_style);
                print_loop("", render_settings.padding_below_title);

                align(render_settings.alignment);

                print("(" + std::to_string(question_number) + ") " + std::to_string(num1) + " " + op + " " + std::to_string(num2) + " = ?");

                print_loop("", render_settings.padding_after_question);

                align_left();
                std::string input_line = padded_str(input, render_settings.input_filler, render_settings.input_width, "");
                align(render_settings.alignment);

                std::string top_line;
                top_line.append(render_settings.top_left_corner);
                top_line.append(extend_string(render_settings.horizontal_bar, render_settings.prompt.length() + (2 * render_settings.horizontal_padding.length())));
                top_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
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
                bottom_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
                bottom_line.append(render_settings.bottom_right_corner);

                print(top_line);
                print(middle_line);
                print(bottom_line);
                print_loop("", render_settings.padding_below_input);
                print(replace(render_settings.answer_correct, "|time|", seconds_to_string(std::chrono::duration_cast<std::chrono::seconds> (question_end - question_start).count())));

                if (render_settings.fill_screen) fill_screen();

                get_key();

                question_number++;
                input = "";
                return 2;
            } else {
                questions_asked++;

                set_cursor_position();

                print_loop("", render_settings.padding_from_top);
                render_settings.title_renderer(render_settings.title_style);
                print_loop("", render_settings.padding_below_title);

                align(render_settings.alignment);

                print("(" + std::to_string(question_number) + ") " + std::to_string(num1) + " " + op + " " + std::to_string(num2) + " = ?");

                print_loop("", render_settings.padding_after_question);

                align_left();
                std::string input_line = padded_str(input, render_settings.input_filler, render_settings.input_width, "");
                align(render_settings.alignment);

                std::string top_line;
                top_line.append(render_settings.top_left_corner);
                top_line.append(extend_string(render_settings.horizontal_bar, render_settings.prompt.length() + (2 * render_settings.horizontal_padding.length())));
                top_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
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
                bottom_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
                bottom_line.append(render_settings.bottom_right_corner);

                print(top_line);
                print(middle_line);
                print(bottom_line);
                print_loop("", render_settings.padding_below_input);
                print(render_settings.answer_incorrect);

                if (render_settings.fill_screen) fill_screen();

                get_key();

                input = "";
                return 0;
            }
        } catch (...) {
            //* Error in converting input string to an integer
            if (input != "-") input = "";
        }
    } else if (input.length() < render_settings.input_width && (key == KEY_ONE || key == KEY_TWO || key == KEY_THREE || key == KEY_FOUR || key == KEY_FIVE || key == KEY_SIX || key == KEY_SEVEN || key == KEY_EIGHT || key == KEY_NINE || key == KEY_ZERO || key == KEY_DASH)) {
        input += key.key;
    }
    return 0;
}

void BrainSpeedTest::reset() {
    input = "";
    question_number = 1;
    test_started = false;
    want_exit = false;
    questions_asked = 0;
    correct_answers = 0;

    start_time = std::chrono::steady_clock::now();
    end_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point question_start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point question_end = std::chrono::steady_clock::now();
}


//**************************************************************************************************
//**************************************************************************************************

void MemoryBenchmark::render(MBRenderSettings render_settings, Statistics &stats) {
    bg_color(g_bg_color);
    fg_color(g_fg_color);
    set_cursor_position();

    align_center();
    print_loop("", render_settings.padding_from_top);
    render_settings.title_renderer(render_settings.title_style);
    print_loop("", render_settings.padding_below_title);


    align_left();
    print("  Instructions:");
    print();
    for (auto s : render_settings.explanation) {
        print(basic_text_wrapping(extend_string(' ', render_settings.padding_for_left_text) + "• " + s));
        print("", "");
    }
    print_loop("", render_settings.padding_from_help);

    align(render_settings.alignment);
    if (render_settings.fill_screen) fill_screen();

    Key k = get_key();
    if (k == KEY_ESCAPE) return;

    for(;;) {
        set_cursor_position();

        print_loop("", render_settings.padding_from_top);
        render_settings.title_renderer(render_settings.title_style);
        print_loop("", render_settings.padding_below_title);

        align(render_settings.alignment);

        if (calculate_new_num) {
            if (digits > render_settings.max_digits) break;

            num = "";
            for (int i = 0; i < digits; i++) {
                if (i == 0) num.append(std::to_string(random_number(1, 9, (i * i))));
                else num.append(std::to_string(random_number(0, 9, (i * i))));
            }
            num = strip(num, '-');
            calculate_new_num = false;

            print(num);
            fill_screen();
            std::this_thread::sleep_for(std::chrono::seconds((int)((float)digits * 0.8) + (int)(2 / digits)));
            continue;
        }

        align_left();
        std::string input_line = padded_str(input, render_settings.input_filler, render_settings.input_width, "");
        align(render_settings.alignment);

        std::string top_line;
        top_line.append(render_settings.top_left_corner);
        top_line.append(extend_string(render_settings.horizontal_bar, render_settings.prompt.length() + (2 * render_settings.horizontal_padding.length())));
        top_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
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
        bottom_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
        bottom_line.append(render_settings.bottom_right_corner);

        print(top_line);
        print(middle_line);
        print(bottom_line);

        if (render_settings.fill_screen) fill_screen();

        want_exit = handle_input(render_settings, stats);
        if (want_exit > 0) break;
    }
    
    //* Test finished or aborted
    if (want_exit == 1) return;
    if (want_exit == 2) {
        set_cursor_position();

        print_loop("", render_settings.padding_from_top);
        render_settings.title_renderer(render_settings.title_style);
        print_loop("", render_settings.padding_below_title);

        align(render_settings.alignment);

        print(basic_text_wrapping("Test aborted. Press any key to return to the main menu. Your score or progress will not be saved."));

        if (render_settings.fill_screen) fill_screen();

        get_key();
        return;
    }
}

int MemoryBenchmark::handle_input(MBRenderSettings render_settings, Statistics &stats) {
    Key key = get_key();

    if (waited_once) {
        input = "";
        waited_once = false;
    }

    if (key == KEY_BACKSPACE) {
        if (!input.empty()) {
            input.pop_back();
        }
    } else if (key == KEY_ESCAPE) {
        return 2;
    } else if (key == KEY_ENTER) {        
        try {
            if (input == num) {
                digits++;
                calculate_new_num = true;

                if (digits > render_settings.max_digits) {
                    set_cursor_position();
                    print_loop("", render_settings.padding_from_top);
                    render_settings.title_renderer(render_settings.title_style);
                    print_loop("", render_settings.padding_below_title);

                    align_center();
                    for (auto s : render_settings.test_finished) {
                        print(basic_text_wrapping(replace(s, "|max|", std::to_string(render_settings.max_digits))));
                        print();
                    }

                    align_left();
                    std::string input_line = padded_str(input, render_settings.input_filler, render_settings.input_width, "");
                    align(render_settings.alignment);

                    std::string top_line;
                    top_line.append(render_settings.top_left_corner);
                    top_line.append(extend_string(render_settings.horizontal_bar, render_settings.prompt.length() + (2 * render_settings.horizontal_padding.length())));
                    top_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
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
                    bottom_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
                    bottom_line.append(render_settings.bottom_right_corner);

                    print(top_line);
                    print(middle_line);
                    print(bottom_line);

                    print_loop("", render_settings.padding_before_feedback);
                    for (auto s : render_settings.test_finished) {
                        print(basic_text_wrapping(replace(s, "|max|", std::to_string(render_settings.max_digits))));
                        print();
                    }

                    long long max_digits_memorised = stats.get_stat(MEMORY_BENCHMARK_MAX_DIGITS).val;
                    if (digits > max_digits_memorised || max_digits_memorised == 0) {
                        stats.set_stat(MEMORY_BENCHMARK_MAX_DIGITS, digits - 1);
                    }

                    if (render_settings.fill_screen) fill_screen();
                    input = "";
                    get_key();

                    return 1;
                } else {
                    set_cursor_position();
                    print_loop("", render_settings.padding_from_top);
                    render_settings.title_renderer(render_settings.title_style);
                    print_loop("", render_settings.padding_below_title);

                    align_center();

                    std::string correct = render_settings.answer_correct;
                    correct = replace(correct, "|score|", std::to_string(digits - 1));

                    align_left();
                    std::string input_line = padded_str(input, render_settings.input_filler, render_settings.input_width, "");
                    align(render_settings.alignment);

                    std::string top_line;
                    top_line.append(render_settings.top_left_corner);
                    top_line.append(extend_string(render_settings.horizontal_bar, render_settings.prompt.length() + (2 * render_settings.horizontal_padding.length())));
                    top_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
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
                    bottom_line.append(padded_str("", render_settings.horizontal_bar, render_settings.input_width, ""));
                    bottom_line.append(render_settings.bottom_right_corner);

                    print(top_line);
                    print(middle_line);
                    print(bottom_line);

                    print_loop("", render_settings.padding_before_feedback);

                    print(basic_text_wrapping(correct));

                    if (render_settings.fill_screen) fill_screen();
                    get_key();
                    input = "";
                    return 0;
                }
            } else {
                set_cursor_position();
                print_loop("", render_settings.padding_from_top);
                render_settings.title_renderer(render_settings.title_style);
                print_loop("", render_settings.padding_below_title);

                align_center();

                //! Do not leave multiple matches in. They would not work, and only the last match will be processed.
                for (auto s : render_settings.test_failed) {
                    std::string r = s;
                    if (s.find("|input|") != std::string::npos) r = replace(s, "|input|", input);
                    if (s.find("|answer|") != std::string::npos) r = replace(s, "|answer|", num);
                    if (s.find("|score|") != std::string::npos) r = replace(s, "|score|", std::to_string(digits));
                    print(basic_text_wrapping(r));
                    print();
                }

                long long max_digits_memorised = stats.get_stat(MEMORY_BENCHMARK_MAX_DIGITS).val;
                if (digits > max_digits_memorised || max_digits_memorised == 0) {
                    stats.set_stat(MEMORY_BENCHMARK_MAX_DIGITS, digits);
                }

                if (render_settings.fill_screen) fill_screen();
                get_key();
                return 1;
            }
        } catch (...) {
            //* Error in converting input string to an integer
            input = "";
        }
    } else if (input.length() < render_settings.input_width && (key == KEY_ONE || key == KEY_TWO || key == KEY_THREE || key == KEY_FOUR || key == KEY_FIVE || key == KEY_SIX || key == KEY_SEVEN || key == KEY_EIGHT || key == KEY_NINE || key == KEY_ZERO)) {
        input += key.key;
    }
    return 0;
}

void MemoryBenchmark::reset() {
    input = "";
    digits = 1;
    want_exit = false;
    num = "";
    calculate_new_num = true;
    test_finished = false;
    waited_once = false;
}
