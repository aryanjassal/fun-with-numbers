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

//* Clean up and exit the program without giving an error
void exit_program(Statistics &stats) {
    //* Exit the program returning the exit value of 0
    exit_program(stats, 0);
}

//* Find all factors of a given 64-bit signed integer
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

//* Remove all occurrences of the character <target> from the input string <str>
std::string strip(std::string str, char target) {
    //* Create the output string
    std::string out;

    //* Iterate over each character in the input string
    for(int i = 0; i < str.length(); i++) {
        //* Only add the character to the output string if it does not match the target we want removed
        if (str[i] != target) {
            out.append(1, str[i]);
        }
    }

    //* Return the output string
    return out;
}

//* Remove all occurrences of the space character (" ") from the input string <str>
std::string strip(std::string str) {
    //* Call strip() on the input string with the target character being a space (" ")
    return strip(str, ' ');
}

//* Returns a random number between <min> and <min> + <range> inclusive
long long random_number(long long min, long long range, long long seed_offset) {
    //* Initialise random seed by using the current time and adding an offset value provided by the user to do consecutive random number generation in a short inteval
    srand(time(NULL) + seed_offset);

    //* Generate random number correspoding to the given inputs and return it
    return rand() % range + min;
}

//* Replace all instances of a particular string <match> by another string <replacement> in the input string <str>
std::string replace(std::string str, std::string match, std::string replacement) {
    //* If there is at least one match, then replace the match with <replacement> where possible then return it
    if (str.find(match) != std::string::npos) return str.replace(str.find(match), match.size(), replacement);
    return str;
}

//* find the length of a string <str> but count unicode characters as one character to return an accurate result
int unicode_len(std::string str) {
    return (str.length() - count_if(str.begin(), str.end(), [](char c) -> bool { return (c & 0xc0) == 0x80; }));
}

//* convert an integer containing the amount of seconds to a properly rendered and formatted string after converting to corresponding units (hours, minutes, seconds)
std::string seconds_to_string(long long s) {
    //* define an output string
    std::string out;

    //* get the number of hours by dividing the seconds by 3600 and flooring it
    long long hours = std::floor(s / 3600);
    //* get the number of minutes by dividing the seconds by 60 and then diving it again by 60 but returning the remainder if the number cannot be divided fully
    long long minutes = std::floor((s / 60) % 60);
    //* define the seconds by passing the remainder of diving the seconds by 60
    long long seconds = s % 60;

    //* if the value of minutes is not equal to zero, then...
    if (minutes != 0) {
        //* ...check if the number of hours is not equal to zero
        if (hours != 0) {
            //* if both cases are true, then the time needs to render hours, minutes, and seconds
            //* render out the corresponding time value then append the unit
            out.append(std::to_string(hours) + ((hours == 1) ? " hour, " : " hours, "));
            out.append(std::to_string(minutes) + ((minutes == 1) ? " minute, and " : " minutes, and "));
            out.append(std::to_string(seconds) + ((seconds == 1) ? " second" : " seconds"));
        } else {
            //* if hours is zero, then the time is only in the unit of minutes and seconds
            //* render out the corresponding time value then append the unit
            out.append(std::to_string(minutes) + ((minutes == 1) ? " minute and " : " minutes and "));
            out.append(std::to_string(seconds) + ((seconds == 1) ? " second" : " seconds"));
        }
    } else {
        //* if the number of minutes is zero, then the time is in seconds
        //* render out the corresponding time value then append the unit
        out.append(std::to_string(seconds) + ((seconds == 1) ? " second" : " seconds"));
    }

    //* return the resulting correctly formatted output string
    return out;
}
