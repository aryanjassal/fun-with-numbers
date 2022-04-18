#include <iostream>

#include "utils.hpp"
#include "tui.hpp"
#include "conio.h"

void init_program() {
    std::ios::sync_with_stdio(false);
    clear();
    init_tui();
}

void exit_program() {
    reset_formatting();
    print();
}

// char get_key() {
//     return 0;
// }

char get_key() {
    char c = getch();
    if (c == 27) {
        char d = getch();
        if (d == 91) {
            return getch();
        }
        return 27;
    }
    return c;
}
