#include <iostream>

#include "utils.hpp"
#include "tui.hpp"

void init_program() {
    clear();
    init_tui();
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
