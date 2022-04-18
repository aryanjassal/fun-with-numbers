#include <iostream>
#include <string>
#include <sstream>

#include "utils.hpp"
#include "ascii.hpp"
#include "tui.hpp"

int main() {
    init_program();

    for(;;) {
        get_terminal_size();
        set_cursor_position();
        fg_color("#f7768e");
        bg_color("#1a1b26");

        print_loop(3, "\n");
        print_title("ansi");
        print_loop(3, "\n");

        align_center();

        std::string selected_text;
        // selected_text.append(fg_color("#ffffff"));
        // selected_text.append(bg_color("#000000"));
        selected_text.append(padded_str("Check number features", 40, ""));
        // selected_text.append(fg_color("#f7768e"));
        // selected_text.append(bg_color("#1a1b26"));
        // print(std::to_string(calculate_padding(selected_text, 40)));
        // getch();

        fg_color("#f7768e");
        bg_color("#1a1b26");

        std::string p = extend_string(" ", calculate_padding(selected_text));

        std::cout << p;
        fg_color("#9ece6a");
        bg_color("#414868");
        std::cout << selected_text;
        fg_color("#f7768e");
        bg_color("#1a1b26");        
        std::cout << p;

        print();

        getch();

        // print("Plot numbers\n");
        // print("Check overall stats\n");
        // print();
        // print("Quit\n");

        // switch(get_key()) {
        //     case UP_ARROW:
        //         print("Up was pressed!");
        //         break;
        //     case DOWN_ARROW:
        //         print("Down was pressed!");
        //         break;
        //     case LEFT_ARROW:
        //         print("Left was pressed!");
        //         break;
        //     case RIGHT_ARROW:
        //         print("Right was pressed!");
        //         break;
        //     case KEY_Q:
        //         exit_program();
        //         return 0;
        // }
    }

    exit_program();
    return 0;
}

// WHITE #cfc9c2
// PINKPURPLE #bb9af7
