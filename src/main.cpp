#include <iostream>  //* for std::string
#include <chrono>  //* for std::chrono::steady_clock::time_point, std::chrono::duration_cast<>, std::chrono::seconds

#include "utils.hpp"  //* init_program(), find_factors(), StatsID, exit_program()
#include "ascii.hpp" //* for print_number_features(), print_memory_test(), print_think_fast(), print_usage_stats(), print_are_you_sure()
#include "classes.hpp"  //* for Menu, MenuRenderSettings, CheckNumberFeatures, CNFRenderSettings, PointPlotter, GraphRenderSettings, MemoryBenchmark, MBRenderSettings, BrainSpeedTest, BSTRenderSettings, Statistics, StatsRenderSettings

//? Ideal if a font with ligatures enabled is used.
//! Windows Terminal (the new terminal for Windows 11) breaks whenever print statements cause a scrolling, making the colors look weird. Use legacy Windows Console Host (aka cmd.exe) to run the application, or just use some other linux terminal (tested on Kitty) because most of the terminals work fine. Note that there is a high chance that tmux terminal will break this code.
//* Superior highly composite numbers = 367567200 or -720720
//TODO: [NORM] Some pages scroll the terminal for some reason
//TODO: [NORM] Comment code everywhere

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    init_program();

    CNFRenderSettings cnf_render_settings;
    cnf_render_settings.prompt = "enter number > ";
    cnf_render_settings.invalid_input_feedback = "Seriously? I asked you to do ONE thing: enter a WHOLE number.";
    cnf_render_settings.features_display_text = ">--------------------< NUMBER FEATURES OF |num| >--------------------<";
    cnf_render_settings.input_prompt_text = "Please enter a whole number that will be checked. Press ESC to go back to the menu.";
    cnf_render_settings.max_width = 80;
    cnf_render_settings.title_renderer = [] (std::string style) { print_number_features(style); };
    cnf_render_settings.title_style = "ansi";

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
    cnf.add_attribute("Number of factors", [&fac] (long long num) -> std::string { return std::to_string(fac.size()); }, true);
    cnf.add_attribute("PrimeOrNot", [&fac] (long long num) -> std::string { return fac.size() > 2 ? "Composite number" : fac.size() == 1 || (fac.at(0) == -1 && fac.at(1) == 1) ? "Unique number" : "Prime number"; } , false);

    Statistics stats;
    stats.add_stat("Numbers entered", "check number features");
    stats.add_stat("Total of numbers", "check number features");
    stats.add_stat("Average of numbers", "check number features");
    stats.add_stat("Smallest number entered", "check number features");
    stats.add_stat("Largest number entered", "check number features");
    stats.add_stat("Coordinates plotted", "plot numbers");
    stats.add_stat("Max digits memorised", "memory benchmark");
    stats.add_stat("Fastest test completion", "brain speed test", (std::string)"time|seconds");
    stats.add_stat("Total questions asked", "brain speed test", false);
    stats.add_stat("Total questions correct", "brain speed test", false);
    stats.add_stat("Accuracy", "brain speed test", (std::string)"unit|percentage");
    stats.add_stat("Time spent in application", "general", (std::string)"time|seconds");
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
    bst_render_settings.test_finished.push_back("Well done!");
    bst_render_settings.test_finished.push_back("The test was finished in |time|.");
    bst_render_settings.test_finished.push_back("Press any key to return to the main menu.");

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
    mb_render_settings.test_failed.push_back("Incorrect!");
    mb_render_settings.test_failed.push_back("Your answer was |input|.");
    mb_render_settings.test_failed.push_back("The correct answer is |answer|.");
    mb_render_settings.test_failed.push_back("Your score is |score|.");
    mb_render_settings.test_finished.push_back("Correct!");
    mb_render_settings.test_finished.push_back("Your score is |score|.");
    mb_render_settings.test_finished.push_back("You have reached the end of the test.");
    mb_render_settings.test_finished.push_back("Press any key to return to the main menu.");

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
    menu.add_option("Check overall stats", [&stats, &s_render_settings, &begin] {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        long long time_till_now = std::chrono::duration_cast<std::chrono::seconds> (end - begin).count();

        long long duration = stats.get_stat(TIME_IN_APPLICATION).val;
        duration += time_till_now;
        stats.set_stat(TIME_IN_APPLICATION, duration);

        begin = std::chrono::steady_clock::now();

        int quit = 0;
        stats.load_stats();

        while(!quit) {
            quit = stats.render(s_render_settings);
        }
        return;
    });
    menu.add_option("Clear Statistics", [&stats] {
        align_center();
        for (;;) {
            set_cursor_position();
            print_loop("", 4);
            print_are_you_sure("ansi");
            print_loop("", 4);
            align_center();
            print("Are you sure you want to reset all statistics? Press ENTER to reset all statistics or press ESC to return to main menu.");
            fill_screen();
            Key k = get_key();
            if (k == KEY_ESCAPE) {
                return;
            } else if (k == KEY_ENTER) {
                stats.reset();
                return;
            }
        }
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
