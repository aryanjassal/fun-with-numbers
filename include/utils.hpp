#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include "classes.hpp"

//* Required for the prime factor finding process
using PrimeFactors = std::vector<std::pair<long long, long long>>;

//* Initialise the program
void init_program();
//* Clean up and exit the program
void exit_program(Statistics &stats);
void exit_program(Statistics &stats, int return_value);

//* Find all factors of a number the standard way
std::vector<long long> find_factors(long long num);

//* Find all factors of a number very fast
std::vector<std::pair<long long, long long>> FindFactors(long long n);

//* Print the factors into a vector
std::vector<long long> PrintFactors(long long factor, PrimeFactors::const_iterator pos, PrimeFactors::const_iterator const end);

//* Strips all characters from the input
std::string strip(std::string str, char target);
std::string strip(std::string str);
