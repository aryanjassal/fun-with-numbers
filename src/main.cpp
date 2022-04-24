#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

#include "utils.hpp"
#include "ascii.hpp"
#include "tui.hpp"
#include "classes.hpp"

//TODO: [NORM] Find factors of a number FAST
//TODO: [LOW] Add max character limit to basic_text_wrapping() and append ... once a word breaches the limit (if word.len + "..." > max_chars) { out.append("...") }

//TODO: [LOW] Get string based values in Stats
//TODO: [LOW] Time in program converted to appropriate units while rendering
//TODO: [LOW] Get function-based stat rendering
//TODO: [NORM] Stats scrolls for some reason
//TODO: [HIGH] Confirmation prompt before actually clearing stats

//TODO: [HIGH] Fix many factors error with numbers like 367567200 or -720720
//TODO: [HIGH] Keep the bottom copyright text right there even if the height exceeds the terminal size. ISSUE SEEMS TO BE IN PRINT - PRINT BUGS OUT WHILE PRINTING MORE THAN THE HEIGHT OF THE TERMINAL

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    init_program();

    CNFRenderSettings cnf_render_settings;
    cnf_render_settings.prompt = "enter number > ";
    cnf_render_settings.invalid_input_feedback = "Seriously? I asked you to do ONE thing: enter a WHOLE number.";
    cnf_render_settings.features_display_text = ">--------------------< NUMBER FEATURES OF |num| >--------------------<";
    cnf_render_settings.input_prompt_text = "Please enter a whole number that will be checked. Press ESC to go back to the menu.";
    cnf_render_settings.max_width = 80;

    std::vector<long long> fac;
    CheckNumberFeatures cnf;
    cnf.add_attribute("Positive/Negative/Zero", [] (long long num) -> std::string { return num > 0 ? "Positive" : num < 0 ? "Negative" : "Zero"; }  , false);
    cnf.add_attribute("Even/Odd", [] (long long num) -> std::string { return num % 2 == 0 ? "Even" : "Odd"; } , false);
    cnf.add_attribute("Factors", [&cnf_render_settings, &fac] (long long num) -> std::string { 
        std::vector <long long> factors = find_factors(num);
        fac = factors;

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
    cnf.add_attribute("PrimeOrNot", [&fac] (long long num) -> std::string { return fac.size() > 2 ? "Composite number" : fac.size() == 1 || (fac.at(0) == -1 && fac.at(1) == 1) ? "Unique number" : "Prime number"; } , false);

    Statistics stats;
    stats.add_stat("Numbers entered");
    stats.add_stat("Total of numbers");
    stats.add_stat("Average of numbers");
    stats.add_stat("Smallest number entered");
    stats.add_stat("Largest number entered");
    stats.add_stat("Coordinates plotted");
    stats.add_stat("Max digits in memory benchark");
    stats.add_stat("Brain speed test score", "seconds");
    stats.add_stat("Time spent in application", "seconds");
    stats.load_stats();

    StatsRenderSettings s_render_settings;
    s_render_settings.title_renderer = [] (std::string style) { print_usage_stats(style); };

    PointPlotter graph;
    GraphRenderSettings graph_render_settings;

    BrainSpeedTest bst;
    BSTRenderSettings bst_render_settings;
    bst_render_settings.title_renderer = [] (std::string style) { print_think_fast(style); };
    bst_render_settings.title_style = "ansi";
    bst_render_settings.explanation.push_back("There will be |num| questions asked.");
    bst_render_settings.explanation.push_back("The questions are simple addition and subtraction.");
    bst_render_settings.explanation.push_back("You need to answer the questions as fast as possible as you are timed.");
    bst_render_settings.explanation.push_back("There is no need to press enter; the correct answer will automatically advance to the next question.");
    bst_render_settings.explanation.push_back("Only numeric values and the minus (-) sign will be accepted as valid input, no other key will be registered.");
    bst_render_settings.explanation.push_back("Press ESC to go back to the main menu.");
    bst_render_settings.explanation.push_back("Press any other key to continue.");

    MemoryBenchmark mb;
    MBRenderSettings mb_render_settings;
    mb_render_settings.title_renderer = [] (std::string style) { print_memory_test(style); };
    mb_render_settings.title_style = "ansi";
    mb_render_settings.explanation.push_back("Random number with increasing digits will be displayed.");
    mb_render_settings.explanation.push_back("You need to memorise them before they disappear.");
    mb_render_settings.explanation.push_back("Only number keys will be accepted as valid input; no alphabetical key would be read.");
    mb_render_settings.explanation.push_back("Press ESC to go back to the main menu anytime.");
    mb_render_settings.explanation.push_back("Your progress is not saved.");
    mb_render_settings.explanation.push_back("Press any other key to start the game.");

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
        stats.load_stats();

        while(!quit) {
            // set_terminal_size();
            quit = stats.render(s_render_settings);
        }
        return;
    });
    menu.add_option("Memory benchmark", [&mb, &mb_render_settings, &stats] {
        mb.reset();
        mb.render(mb_render_settings, stats);
    });
    menu.add_option("Brain speed test", [&bst, &bst_render_settings, &stats] {
        bst.reset();
        bst.render(bst_render_settings, stats);
        return;
    });
    menu.add_line();
    menu.add_option("Clear Statistics", [&stats] {
        stats.reset();
    });
    menu.add_option("Quit", [&stats, &begin] {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto new_dur = std::chrono::duration_cast<std::chrono::seconds> (end - begin).count();

        auto duration = stats.get_stat(TIME_IN_APPLICATION).val;
        duration += new_dur;
        stats.set_stat(TIME_IN_APPLICATION, duration);

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

    set_cursor_position();

    Dimension2D size = get_terminal_size();
    if (size.width < 127 || size.height < 43) {
        std::string prompt_string = "Your terminal size is too small and may result in poor rendering of the user interface and bad user experience. Press any key to continue or ESC to exit right away.";
        fill_screen(false);
        print(basic_text_wrapping(prompt_string));

        Key k = get_key();
        if (k == KEY_ESCAPE) {
            reset_formatting();
            print();
            exit(0);
        }
    }
    set_cursor_position();

    for(;;) {
        set_terminal_size();

        menu.render(render_settings);
        menu.handle_input();
    }

    exit_program(stats);
}
