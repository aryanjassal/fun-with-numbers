#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "utils.hpp"
#include "ascii.hpp"
#include "tui.hpp"

int main() {
    init_program();

    Menu menu;
    menu.set_entry_loop(true);
    menu.add_option("Check number features", [&] { return 0; });
    menu.add_option("Plot numbers", [&] { return 0; });
    menu.add_option("Check overall stats", [&] { return 0; });
    menu.add_line();
    menu.add_option("Quit", [] { exit_program(); });

    for(;;) {
        get_terminal_size();
        set_cursor_position();
        fg_color("#f7768e");
        bg_color("#1a1b26");

        print_loop(3, "\n");
        print_title("ansi");
        print_loop(3, "\n");

        align_center();

        menu.render();
        menu.handle_input();
        // switch(get_key()) {
        //     case UP_ARROW:
        //         menu.move_selection_up();
        //         break;
        //     case DOWN_ARROW:
        //         menu.move_selection_down();
        //         break;
        //     case KEY_Q:
        //         exit_program();
        //         return 0;
        // }
    }

    exit_program();
    return 0;
}
