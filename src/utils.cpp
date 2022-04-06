#include <ncurses.h>
#include <iostream>

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void exit_ncurses() {
    endwin();
}

std::string get_string() {
    std::string out;

    nocbreak();
    echo();

    char ch = getch();

    while (ch != '\n') {
        out.push_back(ch);
        ch = getch();
    }

    cbreak();
    noecho();

    return out;
}

char get_char() {
    nocbreak();
    echo();

    char ch = getch();

    cbreak();
    noecho();

    return ch;
}