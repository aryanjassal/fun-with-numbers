#include <iostream>
#include <string>

#include "utils.hpp"
#include "ascii.hpp"

int main() {
    init_program();

    int width, height;
    get_terminal_size(width, height);

    fg_color("#f7768e");
    bg_color("#1a1b26");

    print_loop(3, "\n");
    print_title("ansi");

    exit_program();
    return 0;
}
