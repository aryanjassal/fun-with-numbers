#include <iostream>

#include "utils.hpp"
#include "tui.hpp"

void init_program() {
    clear();
    init_tui();
    hide_cursor();
}

void exit_program() {
    reset_formatting();
    print();
}

std::string extend_string(std::string str, int times) {
    std::string out;
    for (int i = 0; i < times; i++) {
        out.append(str);
    }
    return out;
}

//* Defining menu functions
void Menu::add_option(std::string str, std::function<void()> func) {
    Line line;
    line.id = next_id;
    line.label = str;
    line.func = func;
    line.interactable = true;
    lines.emplace_back(line);
    next_id++;
}

void Menu::add_line() {
    Menu::add_line("");
}

void Menu::add_line(std::string str) {
    Line line;
    line.label = str;
    line.interactable = false;
    lines.emplace_back(line);
}

void Menu::move_selection_up() {
    Menu::move_selection_up(1);
}

void Menu::move_selection_up(int by=1) {
    if (!loop_menu_options) {
        selection = std::clamp(selection - by, 0, next_id - 1);
    } else {
        selection = ((selection - by) < 0) ? next_id - 1 : selection - by;
    }
}

void Menu::move_selection_down() {
    Menu::move_selection_down(1);
}

void Menu::move_selection_down(int by=1) {
    if (!loop_menu_options) {
        selection = std::clamp(selection + by, 0, next_id - 1);
    } else {
        selection = ((selection + by) > next_id - 1) ? 0 : selection + by;
    }
}

void Menu::set_entry_loop(bool val) {
    loop_menu_options = val;
}

void Menu::render() {
    MenuRenderSettings render_settings;
    render_settings.selector_size = 40;
    
    Menu::render();
}

void Menu::render(MenuRenderSettings render_settings) {
    for (auto& l : lines) {
        std::string text;
        text.append(padded_str(l.label, render_settings.selector_size, ""));

        fg_color("#f7768e");        
        bg_color("#1a1b26");

        if (selection == l.id) {
            std::string pl = extend_string(" ", calculate_padding_left(text));
            std::string pr = extend_string(" ", calculate_padding_right(text));
            std::cout << pl;
            fg_color("#9ece6a");
            bg_color("#414868");
            std::cout << text;
            fg_color("#f7768e");
            bg_color("#1a1b26");  
            std::cout << pr << "\n";
        } else {
            print(text);
        }
        print();
    }
}

void Menu::handle_input() {
    switch(get_key()) {
        case UP_ARROW:
            move_selection_up();
            break;
        case DOWN_ARROW:
            move_selection_down();
            break;
        case RETURN:
            for (auto& l : lines) {
                if (l.id == selection) {
                    l.func();
                }
            }
        case KEY_Q:
            exit_program();
    }
}
