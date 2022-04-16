#include <iostream>
#include <string>

#include "utils.hpp"
#include "ascii.hpp"

void init_program() {
    std::ios::sync_with_stdio(false);
}

void exit_program() {
    reset_formatting();
    std::cout << "\n";
}

int main() {
    init_program();

    int width, height;
    get_terminal_size(width, height);

    fg_color("#f7768e");
    bg_color("#1a1b26");

    print_title("doom");

    exit_program();
    return 0;
}
