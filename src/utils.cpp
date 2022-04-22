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

    CNFRenderSettings cnf_render_settings;
    cnf_render_settings.bg_color_hex = "#1a1b26";
    cnf_render_settings.fg_color_hex = "#f7768e";
    cnf_render_settings.error_bg_color_hex = "#1a1b26";
    cnf_render_settings.error_fg_color_hex = "#ff9e64";
    cnf_render_settings.invalid_input_feedback = "Seriously? I asked you to do ONE thing: enter a WHOLE number.";
    cnf_render_settings.features_display_text = ">--------------------< NUMBER FEATURES OF |num| >--------------------<";
    cnf_render_settings.input_prompt_text = "Please enter a whole number that will be checked. Press ESC to go back to the menu.";
    cnf_render_settings.allow_empty_input = true;
    cnf_render_settings.max_width = 80;

    CheckNumberFeatures cnf;
    cnf.add_attribute("Positive/Negative/Zero", [] (long long num) -> std::string { return num > 0 ? "Positive" : num < 0 ? "Negative" : "Zero"; }  , false);
    cnf.add_attribute("Even/Odd", [] (long long num) -> std::string { return num % 2 == 0 ? "Even" : "Odd"; } , false);
    cnf.add_attribute("Factors", [&cnf_render_settings] (long long num) -> std::string { 
        std::vector <long long> factors = find_factors(num);

        std::string factors_out = "Factors are: ";

        if (factors.at(0) == 0) {
            factors_out = "Infinite factors";
        }

        for (long long factor : factors) {
            factors_out.append(std::to_string(factor));
            factors_out.append(" ");
        }
        factors_out.pop_back();

        return basic_text_wrapping(factors_out, cnf_render_settings.max_width);
    } , false);
    cnf.add_attribute("PrimeOrNot", [] (long long num) -> std::string { int n = find_factors(num).size(); return n > 2 ? "Composite number" : n != 1 ? "Prime number" : "Unique Number"; } , false);

    Statistics stats;
    stats.add_stat("Numbers entered");
    stats.add_stat("Total of numbers");
    stats.add_stat("Average of numbers");
    stats.add_stat("Smallest number entered");
    stats.add_stat("Largest number entered");
    stats.load_stats();

    StatsRenderSettings s_render_settings;
    s_render_settings.title_renderer = [&s_render_settings] (std::string style) { print_usage_stats(style); };
    s_render_settings.bg_color_hex = "#1a1b26";
    s_render_settings.fg_color_hex = "#f7768e";

    Menu menu;
    menu.set_entry_loop(true);
    menu.add_option("Check number features", [&cnf, &cnf_render_settings, &stats] {
        int quit = 0;

        while(!quit) {
            quit = cnf.render(cnf_render_settings, stats);
        }
        return;
    });
    menu.add_option("Plot numbers", [] { return 0; });
    menu.add_option("Check overall stats", [&stats, &s_render_settings] { 
        int quit = 0;

        while(!quit) {
            quit = stats.render(s_render_settings);
        }
    });
    menu.add_option("Memory benchmark", [] { return 0; });
    menu.add_option("Brain speed test", [] { return 0; });
    menu.add_line();
    menu.add_option("Settings", [] { return 0; });
    menu.add_option("Quit", [&stats, &s_render_settings] { 
        stats.save_stats();
        exit_program(); 
    });

    MenuRenderSettings render_settings;
    render_settings.bg_color_hex = "#1a1b26";
    render_settings.fg_color_hex = "#f7768e";
    render_settings.bg_color_highlighted_hex = "#414868";
    render_settings.fg_color_highlighted_hex = "#9ece6a";
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

std::vector<long long> find_factors(long long num) {
    std::vector<long long> factors;

    for (long long i = 2; i <= abs(num) / 2; i++) {
        if (num % i == 0) factors.push_back(i);
    }
    if (num != 1) factors.push_back(abs(num));
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
