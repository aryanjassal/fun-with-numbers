#include <ncurses.h>

#include "utils.hpp"

int main() { 
    init_ncurses();

    printw("Hello, world!");
    getch();

    exit_ncurses();
    return 0;
}
