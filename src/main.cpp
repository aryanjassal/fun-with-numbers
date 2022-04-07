#include <ncurses.h>
#include <iostream>
#include <vector>
#include "utils.hpp"

int numbers_entered, total_of_numbers, smallest_number_entered, largest_number_entered, coordinates_plotted;

char display_menu() {
    printw("Welcome to Fun With Numbers!\n");
    printw("Choose from the menu below:\n");
    printw(" (A) Check number features\n");
    printw(" (B) Plot numbers\n");
    printw(" (C) Check overall stats\n");
    printw("\n");
    printw(" (X) Save and exit\n");
    printw("Choice: ");

    return tolower(get_string()[0]);
}

void check_number_features() {
    clear();

    printw("Please enter a whole number that will be checked over: ");
    refresh();
    std::string num_str = get_string();
    int num = std::stoi(num_str);

    printw("\n");
    printw("The features of %d are...\n", num);
    refresh();

    printw(num > 0 ? "  Positive\n" : num < 0 ? "  Negative\n" : "  Zero\n");
    refresh();

    printw(num % 2 == 0 ? "  Even\n" : "  Odd\n");
    refresh();

    printw("  Factors are ");
    std::vector<int> factors;

    for (int i = 1; i <= (num / 2); i++) {
        if (num % i == 0) {
            factors.push_back(i);
            printw(" %d", i);
        }
    }
    factors.push_back(num);
    printw(" %d", num);
    refresh();

    printw("\n");
    printw(factors.size() == 2 ? "  Is a prime number\n" : "  Is not a prime number\n");

    if (numbers_entered == 0) {
        smallest_number_entered = num;
        largest_number_entered = num;
    } else {
        if (num < smallest_number_entered) { 
            smallest_number_entered = num;
        } else if (num > largest_number_entered) {
            largest_number_entered = num;
        }
    }

    numbers_entered++;
    total_of_numbers += num;

    getch();
    return;
}

void plot_numbers() {
    clear();
    printw("                                                           x axis                                                      \n");
    printw("      1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 \n");
    printw("   ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printw("  1│                                                                                                                  │\n");
    printw("   │                                                                                                                  │\n");
    printw("  2│                                                                                                                  │\n");
    printw("   │                                                                                                                  │\n");
    printw("  3│                                                                                                                  │\n");
    printw("   │                                                                                                                  │\n");
    printw("  4│                                                                                                                  │\n");
    printw("   │                                                                                                                  │\n");
    printw("y 5│                                                                                                                  │\n");
    printw("   │                                                                                                                  │\n");
    printw("a 6│                                                                                                                  │\n");
    printw("x  │                                                                                                                  │\n");
    printw("i 7│                                                                                                                  │\n");
    printw("s  │                                                                                                                  │\n");
    printw("  8│                                                                                                                  │\n");
    printw("   │                                                                                                                  │\n");
    printw("  9│                                                                                                                  │\n");
    printw("   │                                                                                                                  │\n");
    printw(" 10│                                                                                                                  │\n");
    printw("   │                                                                                                                  │\n");
    printw(" 11│                                                                                                                  │\n");
    printw("   │                                                                                                                  │\n");
    printw(" 12│                                                                                                                  │\n");
    printw("   └──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
    refresh();

    int start_x, start_y;
    getyx(stdscr, start_y, start_x);

    printw("Enter a coordinate below to be added to the plot:\n");

    for (;;) {
        int x_coord, y_coord;
        for (;;) {
            printw("x axis: ");
            refresh();
            x_coord = stoi(get_string());

            if (x_coord <= 38 && x_coord > 0) {
                printw("y axis: ");
                y_coord = stoi(get_string());
                refresh();

                if (y_coord <= 12 && y_coord > 0) {
                    break;
                }
            }
        }

        int temp_x, temp_y = 0;
        getyx(stdscr, temp_y, temp_x);
        refresh();

        move((y_coord * 2 + 1), (x_coord * 3) + 3);
        refresh();
        printw("x");
        refresh();
        move(temp_y, temp_x);
        refresh();

        coordinates_plotted++;

        move(start_y, start_x);
        refresh();
        clrtobot();

        printw("Do you wish to add another coordinate (Y/n)? ");
        refresh();

        char ch = get_string()[0]; 
        if (ch == 'n') {
            return;
        }
    }
    return;    
}

void check_overall_stats() {
    clear();

    printw("Here are your statistics of overall use:");
    printw("\n Numbers entered: %d", numbers_entered);
    printw("\n Total of numbers: %d", total_of_numbers);
    printw("\n Average of numbers: %d", total_of_numbers / numbers_entered);
    printw("\n Smallest number entered: %d", smallest_number_entered);
    printw("\n Largest number entered: %d", largest_number_entered);
    printw("\n Coordinates plotted: %d", coordinates_plotted);
    refresh();

    getch();
    return;
}

int main() {
    init_ncurses();

    for (;;) {
        clear();
        char choice = display_menu();
        switch (choice) {
            case 'a':
                check_number_features();
                break;

            case 'b':
                plot_numbers();
                break;

            case 'c':
                check_overall_stats();
                break;

            case 'x':
                exit_ncurses();
                return 0;
            
            default:
                break;
        }
    }
}