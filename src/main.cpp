#include <ncurses.h>
#include <iostream>
#include <vector>
#include <fstream>

//* File which contains utility functions such as initialising and exiting ncurses, etc.
#include "utils.hpp"

//* Declaring variables for statistics
int numbers_entered, total_of_numbers, smallest_number_entered, largest_number_entered, coordinates_plotted;

//* Method to render out the main menu and return the choice selected by the user
char display_menu() {
    //* Printing the menu
    printw("Welcome to Fun With Numbers!\n");
    printw("Choose from the menu below:\n");
    printw(" (A) Check number features\n");
    printw(" (B) Plot numbers\n");
    printw(" (C) Check overall stats\n");
    printw("\n");
    printw(" (X) Save and exit\n");
    printw("Choice: ");

    //* Returning the first charactr of the input string converted to lower case
    return tolower(get_string()[0]);
}

//* Method handing the functionto check number features
void check_number_features() {
    //* Clear the screen to indicate to the user that they are in a different part of the program now
    clear();

    //* Get the user input and convert it to an integer
    printw("Please enter a whole number that will be checked over: ");
    refresh();
    std::string num_str = get_string();
    int num = std::stoi(num_str);

    printw("\n");
    printw("The features of %d are...\n", num);
    refresh();

    //* Prints if the number is positive, negative, or zero
    printw(num > 0 ? "  Positive\n" : num < 0 ? "  Negative\n" : "  Zero\n");
    refresh();

    //* Prints if the number is even or odd
    printw(num % 2 == 0 ? "  Even\n" : "  Odd\n");
    refresh();

    //* Prints out all the factors of the number
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

    //* Prints out if the number is prime or not
    printw("\n");
    printw(factors.size() == 2 ? "  Is a prime number\n" : "  Is not a prime number\n");

    //* Updates the statistics variables
    if (numbers_entered == 0) {
        //* If user has not entered any numbers yet, then the number being processed right now is the smallest and the largest number entered yet
        smallest_number_entered = num;
        largest_number_entered = num;
    } else {
        //* Otherwise, execute checks as normal
        if (num < smallest_number_entered) { 
            smallest_number_entered = num;
        } else if (num > largest_number_entered) {
            largest_number_entered = num;
        }
    }

    numbers_entered++;
    total_of_numbers += num;

    //* Wait for the user to press a key before returning to the main menu
    getch();
    return;
}

//* Method handling plotting numbers
void plot_numbers() {
    //* Clear the screen to inform the user that we are in a different part of the program
    clear();

    //* Print out the grid
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

    //* The point where the program will jump back to to clear the console
    int start_x, start_y;
    getyx(stdscr, start_y, start_x);

    //* Prompt the user for coordinates
    printw("Enter a coordinate below to be added to the plot:\n");

    //* Keep looping until a valid set of coordinates are entered
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

        //* Move to the corresponding location in the plot while accounting for the offset caused by the padding
        move((y_coord * 2 + 1), (x_coord * 3) + 3);
        refresh();
        printw("x");
        refresh();

        //* Update coordinates_plotted variable
        coordinates_plotted++;

        //* Move to the starting point and clear the screen from below the cursor
        move(start_y, start_x);
        refresh();
        clrtobot();

        //* Prompt user if they wish to add more coordinates
        printw("Do you wish to add another coordinate (Y/n)? ");
        refresh();

        //* Parse the user's input
        //* If the user enters 'n', then they exit, otherwise it loops again
        char ch = get_string()[0]; 
        if (ch == 'n') {
            return;
        }
    }
    return;    
}

//* Method to handle the function to check the overall usage statistics
void check_overall_stats() {
    //* Clear the screen to inform the user that we are in a different part of the program
    clear();

    //* Print out the statistics
    printw("Here are your statistics of overall use:");
    printw("\n Numbers entered: %d", numbers_entered);
    printw("\n Total of numbers: %d", total_of_numbers);
    printw("\n Average of numbers: %d", total_of_numbers / numbers_entered);
    printw("\n Smallest number entered: %d", smallest_number_entered);
    printw("\n Largest number entered: %d", largest_number_entered);
    printw("\n Coordinates plotted: %d", coordinates_plotted);
    refresh();

    //* Wair for user input before exiting back to the main menu
    getch();
    return;
}

int exit() {
    //* Save stats in the stats.txt file
    std::ofstream stats_file;
    stats_file.open("stats.txt");
    stats_file << numbers_entered << "\n";
    stats_file << total_of_numbers << "\n";
    stats_file << smallest_number_entered << "\n";
    stats_file << largest_number_entered << "\n";
    stats_file << coordinates_plotted << "\n";
    stats_file.close();
    
    exit_ncurses();
    return 0;
};

void load_data() {
    std::ifstream stats_file("stats.txt");

    std::vector<int> lines;
    for (std::string line; std::getline(stats_file, line);) {
        lines.push_back(std::stoi(line));
    }

    numbers_entered = lines.at(0);
    total_of_numbers = lines.at(1);
    smallest_number_entered = lines.at(2);
    largest_number_entered = lines.at(3);
    coordinates_plotted = lines.at(4);

    stats_file.close();
    return;
}

int main() {
    init_ncurses();
    load_data();

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
                return exit();
            
            default:
                break;
        }
    }
}