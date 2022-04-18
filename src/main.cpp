#include <iostream>
#include <string>

#include "utils.hpp"
#include "ascii.hpp"
#include "tui.hpp"
#include "conio.h"

int main() {
    // init_program();

    // for(;;) {
    //     char c = getch();
    //     std::cout << std::to_string(c) << " ";
    // }
    // char c = getch();
    // std::cout << std::to_string(c) << " ";

    for(;;) {
        // set_cursor_position();
        // fg_color("#f7768e");
        // bg_color("#1a1b26");

        // print_loop(3, "\n");
        // print_title("ansi");
        // print_loop(3, "\n");


        // set_cursor_position(0, 30);

        switch(get_key()) {
            case UP_ARROW:
                print("Up was pressed!");
                break;
            case DOWN_ARROW:
                print("Down was pressed!");
                break;
            case LEFT_ARROW:
                print("Left was pressed!");
                break;
            case RIGHT_ARROW:
                print("Right was pressed!");
                break;
            case ESCAPE:
                exit_program();
                return 0;
            case KEY_Q:
                exit_program();
                return 0;
        }
    }

    exit_program();
    return 0;
}
