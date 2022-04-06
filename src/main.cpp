#include <ncurses.h>
#include <iostream>
#include "utils.hpp"


int main() {
    init_ncurses();

    printw("Hello, world!\n");
    refresh();

    exit_ncurses();
    return 0;    
}