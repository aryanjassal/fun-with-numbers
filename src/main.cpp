#include <iostream>
#include <string>
#include <sstream>

#include "utils.hpp"
#include "ascii.hpp"
#include "tui.hpp"
#include "classes.hpp"

//TODO: Find factors of a number FAST
//TODO: Add enums for alignment and other stuff
//TODO: Move title rendering code inside Menu.render()

int main() {
    init_program();

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
