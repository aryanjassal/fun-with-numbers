#include <ncurses.h>
#include <iostream>

#include "utils.hpp"

//* Initialise the ncurses window
void init_ncurses() {
    //* Set locale to render UTF-8 characters
    setlocale(LC_ALL, "");
    //* Initialise the screen
    initscr();
    //* Cbreak makes each key pressed immediately available to the program, while disabling features such as backspace, etc.
    cbreak();
    //* Do not echo all characters automatically
    noecho();
    //* Enable keypad
    keypad(stdscr, TRUE);

    //* Check if terminal supports colour. Otherwise print that colour isn't supported and no colour will be used.
    if (has_colors() == FALSE) {
        printw("Your terminal does not support coloured output. Continuing on regardless.");
        refresh();
    } 
}

//* Exit the ncurses window
void exit_ncurses() {
    endwin();
}

//* Get a string from the user
std::string get_string() {
    //* The output string
    std::string out;

    //* Give input handling control to the terminal and echo the input to the user
    nocbreak();
    echo();

    //* Get each character pressed
    char ch = getch();

    //* While the character is not newline, append the character onto the output string
    while (ch != '\n') {
        out.push_back(ch);
        ch = getch();
    }

    //* Return the terminal to how it was before
    cbreak();
    noecho();

    //* Return the output string
    return out;
}

//* Get a single character from the user while echoing the output
char get_char() {
    //* Give input handling control to the terminal and echo the input to the user
    nocbreak();
    echo();

    //* Get the character pressed
    char ch = getch();

    //* Return the terminal to the state it was before
    cbreak();
    noecho();

    //* Return the key pressed
    return ch;
}