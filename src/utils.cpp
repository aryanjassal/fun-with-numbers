#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "utils.hpp"
#include "tui.hpp"

//* Initialise the program
void init_program() {
    //* Clear the screen
    clear();
    //* Initialise the terminal user interface
    init_tui();
    //* Create the alignment object to not mistype an alignment value and crash the program
    Align ALIGN;
}

//* Clean up and exit the program
void exit_program(Statistics &stats, int return_value) {
    //* Save the stats to the stats file before exiting
    stats.save_stats();

    //* Remove all formatting
    reset_formatting();
    //* Print a new line. Not necessary but closing looks more graceful
    print();
    //* Exit the program
    exit(return_value);
}

void exit_program(Statistics &stats) {
    exit_program(stats, 0);
}

std::vector<long long> find_factors(long long num) {
    //* Create an empty vector of factors
    std::vector<long long> factors;

    //* If the number is 0, then it has infinite factors. Push 0 in the factors vector and return it.
    //* The code needs to know how to handle 0 being a factor.
    if (num == 0) {
        factors.push_back(0);
        return factors;
    }

    //* Otherwise, find the factors of the number
    long long limit = std::sqrt(abs(num));
    for (long long i = 2; i <= limit; ++i) {
        if (num % i == 0) {
            factors.push_back(i);
            if (num / i != i) { factors.push_back(num / i); }
        }
    }
    
    //* Append 1 to the factors vector depending on the number.
    if (num != 0) {
        if (num != 1 && num != -1) factors.push_back(abs(num));
        factors.push_back(1);
    }
    
    //* If the number is negative, then duplicate its positive factors, flip it, and append it at the beginning of the factors vector.
    if (num < 0) {
        std::vector<long long> temp;
        for (auto fac : factors) {
            temp.push_back(-fac);
        }
        factors.insert(factors.begin(), temp.begin(), temp.end());
    }

    //* Sort the vector in ascending order
    std::sort(factors.begin(), factors.end());

    //* Return the vector of factors
    return factors;
}

std::string strip(std::string str, char target) {
    std::string out;
    for(int i = 0; i < str.length(); i++) {
        if (str[i] != target) {
            out.append(1, str[i]);
        }
    }
    return out;
}

std::string strip(std::string str) {
    return strip(str, ' ');
}

//* Returns a random number between <min> and <min> + <range> inclusive
long long random_number(long long min, long long range, long long seed_offset) {
    //* Initialise random seed
    srand(time(NULL) + seed_offset);

    //* Generate random number between the given inputs and return it
    return rand() % range + min;
}

std::string replace(std::string str, std::string match, std::string replacement) {
    if (str.find(match) != std::string::npos) return str.replace(str.find(match), match.size(), replacement);
    return str;
}

int unicode_len(std::string str) {
    return (str.length() - count_if(str.begin(), str.end(), [](char c) -> bool { return (c & 0xc0) == 0x80; }));
}

std::string seconds_to_string(long long s) {
    std::string out;
    int hours = std::floor(s / 3600);
    int minutes = std::floor((s / 60) % 60);
    int seconds = s % 60;

    if (minutes > 0) {
        if (hours > 0) {
            out.append(std::to_string(hours) + ((hours == 1) ? " hour, " : " hours, "));
            out.append(std::to_string(minutes) + ((minutes == 1) ? " minute, and " : " minutes, and "));
            out.append(std::to_string(seconds) + ((seconds == 1) ? " second" : " seconds"));
        } else {
            out.append(std::to_string(minutes) + ((minutes == 1) ? " minute, " : " minutes and "));
            out.append(std::to_string(seconds) + ((seconds == 1) ? " second" : " seconds"));
        }
    } else {
        out.append(std::to_string(seconds) + ((seconds == 1) ? " second" : " seconds"));
    }
    return out;
}
