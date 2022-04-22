#include <iostream>
#include <string>
#include <sstream>

#include "utils.hpp"
#include "ascii.hpp"
#include "tui.hpp"
#include "classes.hpp"

//TODO: Credit zoelabbb at the bottom of the screen for the kbhit() and getch() functions.
//TODO: Find factors of a number FAST
//TODO: Add enums for alignment and other stuff
//TODO: Move title rendering code inside Menu.render()

int main() {
    init_program();

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

    for(;;) {
        set_terminal_size();
        set_cursor_position();
        fg_color("#f7768e");
        bg_color("#1a1b26");

        print_loop("\n", 3);
        print_title("ansi");
        print_loop("\n", 3);

        menu.render(render_settings);
        menu.handle_input();
    }
    // for (;;) std::cout << std::to_string(getch()) << " " << std::to_string(getch()) << " " << std::to_string(getch()) << " " << std::to_string(getch()) << " " << std::to_string(getch()) << " " << std::to_string(getch()) << " ";

    exit_program();
}

/*
    if (kbhit()) { getch(); }
    // this may work for no blocking getch
    // untested, but it may work
*/
