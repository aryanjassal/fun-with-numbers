#include <iostream>
#include <ncurses.h>
#include <vector>

// using namespace std;

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

void print_plane() {
    printw("                                                       x axis                                                          \n");
    printw("      1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 \n");
    printw("   +------------------------------------------------------------------------------------------------------------------+\n");
    printw("  1|                                                                                                                  |\n");
    printw("   |                                                                                                                  |\n");
    printw("  2|                                                                                                                  |\n");
    printw("   |                                                                                                                  |\n");
    printw("  3|                                                                                                                  |\n");
    printw("   |                                                                                                                  |\n");
    printw("  4|                                                                                                                  |\n");
    printw("   |                                                                                                                  |\n");
    printw("y 5|                                                                                                                  |\n");
    printw("   |                                                                                                                  |\n");
    printw("a 6|                                                                                                                  |\n");
    printw("x  |                                                                                                                  |\n");
    printw("i 7|                                                                                                                  |\n");
    printw("s  |                                                                                                                  |\n");
    printw("  8|                                                                                                                  |\n");
    printw("   |                                                                                                                  |\n");
    printw("  9|                                                                                                                  |\n");
    printw("   |                                                                                                                  |\n");
    printw(" 10|                                                                                                                  |\n");
    printw("   |                                                                                                                  |\n");
    printw(" 11|                                                                                                                  |\n");
    printw("   |                                                                                                                  |\n");
    printw(" 12|                                                                                                                  |\n");
    printw("   +------------------------------------------------------------------------------------------------------------------+\n");
}

void plot_numbers() {
    int start_x, start_y = 0;
    getyx(stdscr, start_y, start_x);

    printw("Enter a coordinate below to be added to the plot:\n");

    printw("x axis: ");
    int x_coord = stoi(get_string());
    refresh();

    printw("y axis: ");
    int y_coord = stoi(get_string());
    refresh();

    int temp_x, temp_y = 0;
    getyx(stdscr, temp_y, temp_x);
    refresh();

    if (y_coord > 12) {
        // return;
    }
    if (x_coord > 38) {
        // return;
    }

    move((y_coord * 2 + 1), (x_coord * 3) + 3);
    refresh();
    printw("x");
    refresh();
    move(temp_y, temp_x);
    refresh();

    // getch();
    move(start_y, start_x);
    refresh();
    clrtobot();

    printw("Do you wish to add another coordinate (Y/n)? ");
    refresh();

    char ch = get_char(); 
    if (ch == 'n') {
        return;
    }

    move(start_y, start_x);
    refresh();
    clrtobot();
   
    plot_numbers();
}

int main() {
    //* Initialise ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // std::vector<std::pair<std::pair<int, int>, char>> coordinates;
    // coordinates.emplace_back(std::make_pair(5, 1), 'x');
    // coordinates.emplace_back(std::make_pair(4, 2), 'x');
    // coordinates.emplace_back(std::make_pair(3, 3), 'x');
    // coordinates.emplace_back(std::make_pair(2, 4), ' ');
    // coordinates.emplace_back(std::make_pair(1, 5), ' ');

    // for (auto [coords, content] : coordinates) {
    //     std::string debug_msg = std::to_string(coords.first);
    //     debug_msg.append(", ");
    //     debug_msg.append(std::to_string(coords.second));
    //     debug_msg.append(": ");
    //     debug_msg.push_back(content);

    //     printw(debug_msg.c_str());
    //     printw("\n");
    //     refresh();
    // }

    // getch();
    print_plane();
    plot_numbers();
    //* Safely shut down ncurses
    endwin();
    return 0;
}
