#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

#include "utils.hpp"
#include "ascii.hpp"
#include "tui.hpp"
#include "classes.hpp"

//TODO: Find factors of a number FAST
//TODO: Add max character limit to basic_text_wrapping() and append ... once a word breaches the limit (if word.len + "..." > max_chars) { out.append("...") }

//TODO: Get string based values in Stats
//TODO: Brain Speed will not have levels; only one level with a clock. The questions will become harder and harder as they go by.

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    init_program();

    CNFRenderSettings cnf_render_settings;
    cnf_render_settings.prompt = "enter number > ";
    cnf_render_settings.invalid_input_feedback = "Seriously? I asked you to do ONE thing: enter a WHOLE number.";
    cnf_render_settings.features_display_text = ">--------------------< NUMBER FEATURES OF |num| >--------------------<";
    cnf_render_settings.input_prompt_text = "Please enter a whole number that will be checked. Press ESC to go back to the menu.";
    cnf_render_settings.max_width = 80;

    CheckNumberFeatures cnf;
    cnf.add_attribute("Positive/Negative/Zero", [] (long long num) -> std::string { return num > 0 ? "Positive" : num < 0 ? "Negative" : "Zero"; }  , false);
    cnf.add_attribute("Even/Odd", [] (long long num) -> std::string { return num % 2 == 0 ? "Even" : "Odd"; } , false);
    cnf.add_attribute("Factors", [&cnf_render_settings] (long long num) -> std::string { 
        std::vector <long long> factors = find_factors(num);

        std::string factors_out = "Factors are: ";

        if (factors.at(0) == 0) {
            factors_out = "Infinite factors";
        } else {
            for (long long factor : factors) {
                factors_out.append(std::to_string(factor));
                factors_out.append(" ");
            }
            factors_out.pop_back();
        }

        return basic_text_wrapping(factors_out, cnf_render_settings.max_width);
    } , false);
    cnf.add_attribute("PrimeOrNot", [] (long long num) -> std::string { auto n = find_factors(num); return n.size() > 2 ? "Composite number" : n.size() == 1 || (n.at(0) == -1 && n.at(1) == 1) ? "Unique number" : "Prime number"; } , false);

    Statistics stats;
    stats.add_stat("Numbers entered");
    stats.add_stat("Total of numbers");
    stats.add_stat("Average of numbers");
    stats.add_stat("Smallest number entered");
    stats.add_stat("Largest number entered");
    stats.add_stat("Coordinates plotted");
    stats.add_stat("Time spent in application", 0, "seconds");
    stats.load_stats();

    StatsRenderSettings s_render_settings;
    s_render_settings.title_renderer = [&s_render_settings] (std::string style) { print_usage_stats(style); };

    PointPlotter graph;
    GraphRenderSettings graph_render_settings;

    Menu menu;
    menu.set_entry_loop(true);
    menu.add_option("Check number features", [&cnf, &cnf_render_settings, &stats] {
        int quit = 0;
        cnf.reset();

        while(!quit) {
            set_terminal_size();
            quit = cnf.render(cnf_render_settings, stats);
        }
        return;
    });
    menu.add_option("Plot numbers", [&graph, &graph_render_settings, &stats] { 
        int quit = 0;
        graph.reset_graph();

        while(!quit) {
            set_terminal_size();
            graph_render_settings.graph_height = (int)(t_size.height / 2);
            quit = graph.render(graph_render_settings, stats);
        }
        return;
    });
    menu.add_option("Check overall stats", [&stats, &s_render_settings] { 
        int quit = 0;

        while(!quit) {
            set_terminal_size();
            quit = stats.render(s_render_settings);
        }
        return;
    });
    menu.add_option("Memory benchmark", [] { return 0; });
    menu.add_option("Brain speed test", [] { return 0; });
    menu.add_line();
    menu.add_option("Settings", [] { return 0; });
    menu.add_option("Quit", [&stats, &begin] {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto new_dur = std::chrono::duration_cast<std::chrono::seconds> (end - begin).count();

        auto duration = stats.get_stat(7).val;
        duration += new_dur;
        stats.set_stat(7, duration);

        exit_program(stats); 
    });

    MenuRenderSettings render_settings;
    render_settings.title_renderer = [&render_settings] (std::string style) { print_title(style); };
    render_settings.title_style = "ansi";

    g_fg_color = hex_to_rgb("#f7768e");
    g_bg_color = hex_to_rgb("#1a1b26");
    g_fg_color_highlighted = hex_to_rgb("#9ece6a");
    g_bg_color_highlighted = hex_to_rgb("#414868");
    g_fg_color_error = hex_to_rgb("#9ece6a");
    g_bg_color_error = hex_to_rgb("#1a1b26");

    for(;;) {
        set_terminal_size();

        menu.render(render_settings);
        menu.handle_input();
    }

    exit_program(stats);
}
