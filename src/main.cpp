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
    cnf.add_attribute("Status", [] { print("NICE"); });

    Menu menu;
    menu.set_entry_loop(true);
    menu.add_option("Check number features", cnf.render);
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
