#include <chrono>
#include <iostream>
#include <utility>
#include <vector>
#include <math.h>
#include <algorithm>

using PrimeFactors = std::vector<std::pair<uint64_t, uint64_t>>;

std::vector<std::pair<uint64_t, uint64_t>> FindFactors(uint64_t n)
{
    PrimeFactors primeFactors;

    uint64_t square = static_cast<uint64_t>(std::sqrt(n));
    for (uint64_t i = 2; i <= square && i <= n; ++i)
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
            uint64_t count = 0;
            while (n % i == 0)
            {
                ++count;
                n /= i;
            }
            primeFactors.emplace_back(i, count);
            if (count != 0)
            {
                square = static_cast<uint64_t>(std::sqrt(n));
            }
        }
    }
    if (n != 1)
    {
        primeFactors.emplace_back(n, 1);
    }
    return primeFactors;
}

std::vector<unsigned long long> f;
void PrintFactors(uint64_t factor, PrimeFactors::const_iterator pos, PrimeFactors::const_iterator const end)
{
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
            f.push_back(newFactor);
            PrintFactors(newFactor, pos + 1, end);
        }
        ++pos;
    }
}


int main()
{
    using Clock = std::chrono::steady_clock;

    // uint64_t const input = 10'000'000'000'000'000ull;
    std::system("clear");
    std::cout << "input a number: ";
    std::string num;
    std::getline(std::cin, num);

    uint64_t input = std::stoull(num);
    
    //uint64_t const input = 2ull * 3ull * 5ull * 7ull *11ull * 13ull *17ull * 19ull * 23ull * 29ull *31ull*37ull * 41ull*43ull;

    auto start = Clock::now();
    auto factors = FindFactors(input);

    // print
    std::cout << 1 << ' ';
    PrintFactors(1, factors.begin(), factors.end());
    std::sort(f.begin(), f.end());
    for (auto n : f) {
        std::cout << n << " ";
    }
    auto end = Clock::now();
    std::cout << "\ntook " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}