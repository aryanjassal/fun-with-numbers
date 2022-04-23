#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
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
void exit_program(int return_value) {
    //* Remove all formatting
    reset_formatting();
    //* Print a new line. Not necessary but closing looks more graceful
    print();
    //* Exit the program
    exit(return_value);
}

void exit_program() {
    exit_program(0);
}

//TODO: fix negative -1
std::vector<long long> find_factors(long long num) {
    std::vector<long long> factors;

    for (long long i = 2; i <= abs(num) / 2; i++) {
        if (num % i == 0) factors.push_back(i);
    }
    if (num != 1 && num != -1) factors.push_back(abs(num));
    factors.push_back(1);

    if (num < 0) {
        std::vector<long long> temp;
        for (auto fac : factors) {
            temp.push_back(-fac);
        }
        factors.insert(factors.end(), temp.begin(), temp.end());
    } else if (num == 0) {
        factors.push_back(0);
        return factors;
    }

    std::sort(factors.begin(), factors.end());

    return factors;
}

//* Finding prime factors of a given number extremely efficiently.
//* Credit to fabian (https://stackoverflow.com/questions/70411886/whats-the-fastest-way-to-find-the-factors-of-a-number-in-c) for creating this code
using PrimeFactors = std::vector<std::pair<long long, long long>>;

std::vector<std::pair<long long, long long>> FindFactors(long long n)
{
    PrimeFactors primeFactors;

    long long square = static_cast<long long>(std::sqrt(n));
    for (long long i = 2; i <= square && i <= n; ++i)
    {
        bool isPrime = true;
        for (auto [prime, exponent] : primeFactors)
        {
            if (prime * prime > i)
            {
                break;
            }
            if (i % prime == 0u)
            {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
        {
            long long count = 0;
            while (n % i == 0)
            {
                ++count;
                n /= i;
            }
            primeFactors.emplace_back(i, count);
            if (count != 0)
            {
                square = static_cast<long long>(std::sqrt(n));
            }
        }
    }
    if (n != 1)
    {
        primeFactors.emplace_back(n, 1);
    }
    return primeFactors;
}

std::vector<long long> PrintFactors(long long factor, PrimeFactors::const_iterator pos, PrimeFactors::const_iterator const end)
{
    std::vector<long long> factors;
    while (pos != end)
    {
        while (pos != end && pos->second == 0)
        {
            ++pos;
        }
        auto newFactor = factor;
        for (auto count = pos->second; count != 0; --count)
        {
            newFactor *= pos->first;
            // std::cout << newFactor << '\n';
            factors.emplace_back(newFactor);
            PrintFactors(newFactor, pos + 1, end);
        }
        ++pos;
    }

    std::sort(factors.begin(), factors.end());
    return factors;
}
