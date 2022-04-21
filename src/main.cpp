#include <iostream>
#include <string>
#include <sstream>

#include "utils.hpp"
#include "ascii.hpp"
#include "tui.hpp"
#include "classes.hpp"

int main() {
    init_program();

    CheckNumberFeatures cnf;
    cnf.add_attribute("Status", [] () -> std::string { return "NICE"; }, true);

    CNFRenderSettings cnf_render_settings;
    cnf_render_settings.bg_color_hex = "#1a1b26";
    cnf_render_settings.fg_color_hex = "#f7768e";
    cnf_render_settings.error_bg_color_hex = "#1a1b26";
    cnf_render_settings.error_fg_color_hex = "#ff9e64";
    cnf_render_settings.invalid_input_feedback = "Seriously? I asked you to do ONE thing, enter a whole number.";
    cnf_render_settings.features_display_text = ">--------------------< NUMBER FEATURES OF |n_out| >--------------------<";
    cnf_render_settings.input_prompt_text = "Please enter a whole number";
    // cnf_render_settings.empty_input_feedback = "Input cannot be empty";
    cnf_render_settings.allow_empty_input = true;

    Menu menu;
    menu.set_entry_loop(true);
    menu.add_option("Check number features", [&cnf, &cnf_render_settings] {
        int quit = 0;

        while(!quit) {
            quit = cnf.render(cnf_render_settings);
        }
        return;
    });
    menu.add_option("Plot numbers", [&] { return 0; });
    menu.add_option("Check overall stats", [&] { return 0; });
    menu.add_line();
    menu.add_option("Quit", [] { exit_program(); });

    MenuRenderSettings render_settings;
    render_settings.bg_color_hex = "#1a1b26";
    render_settings.fg_color_hex = "#f7768e";
    render_settings.bg_color_highlighted_hex = "#414868";
    render_settings.fg_color_highlighted_hex = "#9ece6a";

    for(;;) {
        set_terminal_size();
        set_cursor_position();
        fg_color("#f7768e");
        bg_color("#1a1b26");

        print_loop("\n", 3);
        print_title("ansi");
        print_loop("\n", 3);

        menu.render(render_settings);
        menu.handle_input();
    }
    // for (;;) std::cout << std::to_string(getch()) << " " << std::to_string(getch()) << " " << std::to_string(getch()) << " " << std::to_string(getch()) << " " << std::to_string(getch()) << " " << std::to_string(getch()) << " ";

    exit_program();
}

/*
    if (kbhit()) { getch(); }
    // this may work for no blocking getch
    // untested, but it may work
*/
