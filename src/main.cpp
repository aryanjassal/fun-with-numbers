#include <ncurses.h>
#include <iostream>
#include "utils.hpp"

int main() {
    init_ncurses();

    clear();
    printw("Hello, world!");
    refresh();
    getch();

    exit_ncurses();
    return 0;
}