#include <iostream>  //* for std::string
#include <chrono>  //* for std::chrono::steady_clock::time_point, std::chrono::duration_cast<>, std::chrono::seconds
#include <string.h> //* for std::to_string()

#include "utils.hpp"  //* init_program(), find_factors(), StatsID, exit_program()
#include "ascii.hpp"  //* for print_number_features(), print_memory_test(), print_think_fast(), print_usage_stats(), print_are_you_sure()
#include "classes.hpp"  //* for Menu, MenuRenderSettings, CheckNumberFeatures, CNFRenderSettings, PointPlotter, GraphRenderSettings, MemoryBenchmark, MBRenderSettings, BrainSpeedTest, BSTRenderSettings, Statistics, StatsRenderSettings


//? Ideal if a font with ligatures enabled is used.
//! Windows Terminal (the new terminal for Windows 11) breaks whenever print statements cause a scrolling, making the colors look weird. Use legacy Windows Console Host (aka cmd.exe) to run the application, or just use some other linux terminal (tested on Kitty) because most of the terminals work fine. Note that there is a high chance that tmux terminal will break this code.
//! Works under Windows too, but sacrifices needed to me made on printing unicode characters; only ASCII characters which fit inside a char work under Windows.

#if defined(_WIN32)
    //* set title style for Windows
    std::string TITLE_STYLE = "doom";

    //* set thick ASCII style for Windows
    std::string THICK_HORIZONTAL_BAR = "-";
    std::string THICK_VERTICAL_BAR = "|";
    std::string THICK_TOP_LEFT_CORNER = "+";
    std::string THICK_TOP_RIGHT_CORNER = "+";
    std::string THICK_BOTTOM_LEFT_CORNER = "+";
    std::string THICK_BOTTOM_RIGHT_CORNER = "+";

    //* set thin ASCII style for Windows
    std::string THIN_HORIZONTAL_BAR = "-";
    std::string THIN_VERTICAL_BAR = "|";
    std::string THIN_TOP_LEFT_CORNER = "+";
    std::string THIN_TOP_RIGHT_CORNER = "+";
    std::string THIN_BOTTOM_LEFT_CORNER = "+";
    std::string THIN_BOTTOM_RIGHT_CORNER = "+";

    //* set bullet point ASCII style for Windows
    std::string BULLET_POINT = ">";
#elif defined(__linux__)
    //* set title style for linux
    std::string TITLE_STYLE = "ansi";

    //* set thick ASCII style for linux
    std::string THICK_HORIZONTAL_BAR = "═";
    std::string THICK_VERTICAL_BAR = "║";
    std::string THICK_TOP_LEFT_CORNER = "╔";
    std::string THICK_TOP_RIGHT_CORNER = "╗";
    std::string THICK_BOTTOM_LEFT_CORNER = "╚";
    std::string THICK_BOTTOM_RIGHT_CORNER = "╝";

    //* set thin ASCII style for linux
    std::string THIN_HORIZONTAL_BAR = "─";
    std::string THIN_VERTICAL_BAR = "│";
    std::string THIN_TOP_LEFT_CORNER = "╭";
    std::string THIN_TOP_RIGHT_CORNER = "╮";
    std::string THIN_BOTTOM_LEFT_CORNER = "╰";
    std::string THIN_BOTTOM_RIGHT_CORNER = "╯";

    //* set bullet point ASCII style for linux
    std::string BULLET_POINT = "•";
#endif

int main() {
    //* create a time point to mark as the beginning of the program to measure time spent in the application
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    //* initialise the program
    init_program();

    //* create a Check Number Features Render Settings (CNFRenderSettings) object and set the variables
    CNFRenderSettings cnf_render_settings;
    cnf_render_settings.prompt = "enter number > ";
    cnf_render_settings.invalid_input_feedback = "Seriously? I asked you to do ONE thing: enter a WHOLE number.";
    cnf_render_settings.features_display_text = ">--------------------< NUMBER FEATURES OF |num| >--------------------<";
    cnf_render_settings.input_prompt_text = "Please enter a whole number that will be checked. Press ESC to go back to the menu.";
    cnf_render_settings.max_width = 80;
    cnf_render_settings.title_renderer = [] (std::string style) { print_number_features(style); };
    cnf_render_settings.title_style = TITLE_STYLE;
    cnf_render_settings.horizontal_bar = THICK_HORIZONTAL_BAR;
    cnf_render_settings.vertical_bar = THICK_VERTICAL_BAR;
    cnf_render_settings.top_left_corner = THICK_TOP_LEFT_CORNER;
    cnf_render_settings.top_right_corner = THICK_TOP_RIGHT_CORNER;
    cnf_render_settings.bottom_left_corner = THICK_BOTTOM_LEFT_CORNER;
    cnf_render_settings.bottom_right_corner = THICK_BOTTOM_RIGHT_CORNER;

    //* create a vector of all factors to be used for later calculations
    std::vector<long long> factors;

    //* create a Check Number Factors object
    CheckNumberFeatures cnf;

    //* add a number attribute that checks whether a number is positive, negative, or zero
    cnf.add_attribute("Positive/Negative/Zero", [] (long long num) -> std::string { return num > 0 ? "Positive" : num < 0 ? "Negative" : "Zero"; }, false);

    //* add a number attribute that checks whether a number is even or odd
    cnf.add_attribute("Even/Odd", [] (long long num) -> std::string { return num % 2 == 0 ? "Even" : "Odd"; } , false);

    //* add a number attribute that lists all its factors
    cnf.add_attribute("Factors", [&cnf_render_settings, &factors] (long long num) -> std::string {
        //* find factors and store them in a vector of previously-declared long-long-type integers
        factors = find_factors(num);

        //* initialise the output string the term "Factors are: "
        std::string factors_out = "Factors are: ";

        //* if the factor at the first position is 0, then there are infinite factors, as every number is a factor of zero.
        if (factors.at(0) == 0) {
            //* simply print "Infinite factors"
            factors_out = "Infinite factors";
        } else {
            //* otherwise, loop over each factor in the vector of factors
            for (long long factor : factors) {
                //* append the number to the list of factors, then append a space after it.
                factors_out.append(std::to_string(factor) + " ");
            }
            //* remove the last added space from the list of factors
            factors_out.pop_back();
        }

        //* return the string with all the spaced factors word-wrapped by the width given by the render settings
        return basic_text_wrapping(factors_out, cnf_render_settings.max_width);
    } , false);

    //* add a number attribute that counts the number of factors, and if the factor at the first index is zero, then there are infinite factors
    cnf.add_attribute("Number of factors", [&factors] (long long num) -> std::string { return (factors.at(0) == 0) ? "Infinite" : std::to_string(factors.size()); }, true);

    //* add a number attribute that prints whether the number is a prime number, a composite number, or a unique number
    cnf.add_attribute("PrimeOrNot", [&factors] (long long num) -> std::string { return factors.size() > 2 ? "Composite number" : factors.size() == 1 || (factors.at(0) == -1 && factors.at(1) == 1) ? "Unique number" : "Prime number"; } , false);

    //* create a Statistics object
    Statistics stats;

    //* add the tracked statistics, their section (for section-based grouping), the units of the data, and whether to render the statistic or hide them from the user
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

    //* load all the aforementioned statistics from the stats file
    //* if it doesn't exist, then the values are initialised by zeroes
    stats.load_stats();

    //* create a StatsRenderSettings object to store the render settings for rendering statistics, and modify the settings as required
    StatsRenderSettings s_render_settings;
    s_render_settings.title_renderer = [] (std::string style) { print_usage_stats(style); };
    s_render_settings.title_rendering_style = TITLE_STYLE;
    s_render_settings.horizontal_bar = THIN_HORIZONTAL_BAR;
    s_render_settings.vertical_bar = THIN_VERTICAL_BAR;
    s_render_settings.top_left_corner = THIN_TOP_LEFT_CORNER;
    s_render_settings.top_right_corner = THIN_TOP_RIGHT_CORNER;
    s_render_settings.bottom_left_corner = THIN_BOTTOM_LEFT_CORNER;
    s_render_settings.bottom_right_corner = THIN_BOTTOM_RIGHT_CORNER;

    //* create a PointPlotter object, which will be used to display the graph and all its features
    PointPlotter graph;
    //* create a GraphRenderSettings object to store the render settings for rendering the graph, and modify the settings as required
    GraphRenderSettings graph_render_settings;
    graph_render_settings.horizontal_bar = THICK_HORIZONTAL_BAR;
    graph_render_settings.vertical_bar = THICK_VERTICAL_BAR;
    graph_render_settings.top_left_corner = THICK_TOP_LEFT_CORNER;
    graph_render_settings.top_right_corner = THICK_TOP_RIGHT_CORNER;
    graph_render_settings.bottom_left_corner = THICK_BOTTOM_LEFT_CORNER;
    graph_render_settings.bottom_right_corner = THICK_BOTTOM_RIGHT_CORNER;

    //* create a BrainSpeedTest object, which will be used to display the Brain Speed Test and all its features
    BrainSpeedTest bst;
    //* create a BSTRenderSettings object to store the render settings for rendering the Brain Speed Test, and modify the settings as required
    BSTRenderSettings bst_render_settings;
    bst_render_settings.title_renderer = [] (std::string style) { print_think_fast(style); };
    bst_render_settings.title_style = TITLE_STYLE;
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
    bst_render_settings.horizontal_bar = THICK_HORIZONTAL_BAR;
    bst_render_settings.vertical_bar = THICK_VERTICAL_BAR;
    bst_render_settings.top_left_corner = THICK_TOP_LEFT_CORNER;
    bst_render_settings.top_right_corner = THICK_TOP_RIGHT_CORNER;
    bst_render_settings.bottom_left_corner = THICK_BOTTOM_LEFT_CORNER;
    bst_render_settings.bottom_right_corner = THICK_BOTTOM_RIGHT_CORNER;
    bst_render_settings.bullet_point = BULLET_POINT;
    
    //* create a MemoryBenchmark object, which will be used to display the Memory Benchmark and all its features
    MemoryBenchmark mb;
    //* create a MBRenderSettings object to store the render settings for rendering the Memory Benchmark, and modify the settings as required
    MBRenderSettings mb_render_settings;
    mb_render_settings.title_renderer = [] (std::string style) { print_memory_test(style); };
    mb_render_settings.title_style = TITLE_STYLE;
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
    mb_render_settings.horizontal_bar = THICK_HORIZONTAL_BAR;
    mb_render_settings.vertical_bar = THICK_VERTICAL_BAR;
    mb_render_settings.top_left_corner = THICK_TOP_LEFT_CORNER;
    mb_render_settings.top_right_corner = THICK_TOP_RIGHT_CORNER;
    mb_render_settings.bottom_left_corner = THICK_BOTTOM_LEFT_CORNER;
    mb_render_settings.bottom_right_corner = THICK_BOTTOM_RIGHT_CORNER;
    mb_render_settings.bullet_point = BULLET_POINT;

    //* create a Menu object, which will be use to display the Menu and all its features
    Menu menu;

    //* enable menu looping: after pressing down on the last menu entry, it will loop around back to the top
    menu.set_entry_loop(true);

    //* add an option to the menu, which will render the CheckNumberFeatures object with the given render settings, and update the statistics as required
    menu.add_option("Check number features", [&cnf, &cnf_render_settings, &stats] {
        //* assign 0 to quit variable
        int quit = 0;

        //* reset the CheckNumberFeatures menu option
        cnf.reset();

        //* while quit is not true (0), then keep looping through the following
        while(!quit) {
            //* update the global termial size
            set_terminal_size();

            //* render the CheckNumberFeatures module using the corresponding render settings and passing the Statistics object to update it accordingly
            quit = cnf.render(cnf_render_settings, stats);
        }
        return;
    });

    //* add an option to the menu, which will render the PointPlotter object with the given render settings, and update the statistics as required
    menu.add_option("Plot numbers", [&graph, &graph_render_settings, &stats] { 
        //* assign 0 to quit variable
        int quit = 0;

        //* reset the PointPlotter object
        graph.reset_graph();

        //* while quit is not true (0), then keeping looping through the following
        while(!quit) {
            //* update the global terminal size
            set_terminal_size();

            //* update the height of the graph according to current terminal dimensions
            graph_render_settings.graph_height = (int)(t_size.height / 2);

            //* render the PointPlotter module using the corresponding render settings and passing the Statistics object to update it accordingly
            quit = graph.render(graph_render_settings, stats);
        }
        return;
    });

    //* add an option to the menu, which will render the MemoryBenchmark object with the given render settings, and update the statistics as required
    menu.add_option("Memory benchmark", [&mb, &mb_render_settings, &stats] {
        //* reset the MemoryBenchmark object
        mb.reset();

        //* hand over control of the program to the MemoryBenchmark for rendering and handling input
        mb.render(mb_render_settings, stats);
    });

    //* add an option to the menu, which will render the BrainSpeedTest object with the given render settings, and update the statistics as required
    menu.add_option("Brain speed test", [&bst, &bst_render_settings, &stats] {
        //* reset the BrainSpeedTest object
        bst.reset();

        //* hand over control of the program to the BrainSpeedTest for rendering and handling input
        bst.render(bst_render_settings, stats);
    });

    //* add an empty line in the menu for padding
    menu.add_line();

    //* add an option to the menu, which will render the Statistics object with the given render settings, and pass the program start and end time
    menu.add_option("Check overall stats", [&stats, &s_render_settings, &begin] {
        //* create an end time point to track the usage of the application until now
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        //* get the number of seconds since the start of the application, or the previous execution of this command
        long long time_till_now = std::chrono::duration_cast<std::chrono::seconds> (end - begin).count();

        //* get the duration of time spent in the application so far as per the statistics save file
        long long duration = stats.get_stat(TIME_IN_APPLICATION).val;

        //* add the time spent in the application to the TIME_IN_APPLICATION variable in the statistics save file
        duration += time_till_now;

        //* update the save file to reflect this statistic
        stats.set_stat(TIME_IN_APPLICATION, duration);

        //* assign a new start point to count time from in the application
        begin = std::chrono::steady_clock::now();
        

        //* create a variable to keep track if the program wants to quit or not
        int quit = 0;

        //* refresh the stats by reloading them from the save file
        stats.load_stats();

        //* run the rendering loop while the user does not want to exit the application
        //? could be without the loop and the return value, and just wait for a key to be pressed before exiting this menu option
        while(!quit) {
            quit = stats.render(s_render_settings);
        }
    });

    //* add an option to the menu, which will let user reset all of their statistics to zeroes (0)
    menu.add_option("Clear Statistics", [&stats] {
        //* set the alignment to center to render the title
        align_center();

        //* main rendering loop
        for (;;) {
            //* set the position of the cursor to home (0, 0)
            set_cursor_position();

            //* print 4 blank lines to act as padding before the title
            print_loop("", 4);

            //* print "ARE YOU SURE" in big text to confirm if the user really wants to clear all their statistics
            print_are_you_sure(TITLE_STYLE);

            //* print 4 more blank lines to act as padding
            print_loop("", 4);

            //* se the alignment to center again as rendering title resets the alignment to the left
            align_center();

            //* ask a secondary prompt with more informtion and instructions to abort if the user wishes to do so
            print("Are you sure you want to reset all statistics? Press ENTER to reset all statistics or press ESC to return to main menu.");

            //* fill the screen with blank lines and add the copyright information at the bottom
            fill_screen();

            //* get a key from the user
            Key k = get_key();

            if (k == KEY_ESCAPE) {  //* if the key is ESC, then return without clearing the stats
                return;
            } else if (k == KEY_ENTER) {   //* otherwise, if the key is ENTER, then clear the stats and return
                stats.reset();
                return;
            }
        }
    });

    //* adds an option to the menu to allow the user to gracefully quit the application.
    //! CTRL-C does not work in Windows because of Operating system differences
    menu.add_option("Quit", [&stats, &begin] {
        //* create an end time point to track how long was spent in the program
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        //* convert the total time spent since the last start point till now into seconds
        auto new_dur = std::chrono::duration_cast<std::chrono::seconds> (end - begin).count();

        //* get the current time spent in the program
        auto duration = stats.get_stat(TIME_IN_APPLICATION).val;

        //* add the time currently spent in the application to the total present in the statistics file
        duration += new_dur;

        //* write the new vale back to the statistics file
        stats.set_stat(TIME_IN_APPLICATION, duration);

        //* gracefully exit the program, returning the terminal to the state it was in before
        exit_program(stats); 
    });

    //* create a new MenuRenderSettings object and change the rendering settings as required
    MenuRenderSettings render_settings;
    render_settings.title_renderer = [&render_settings] (std::string style) { print_title(style); };
    render_settings.title_style = TITLE_STYLE;

    //* set global colors for normal, highlighted, and error text
    g_fg_color = hex_to_rgb("#f7768e");
    g_bg_color = hex_to_rgb("#1a1b26");
    g_fg_color_highlighted = hex_to_rgb("#9ece6a");
    g_bg_color_highlighted = hex_to_rgb("#414868");
    g_fg_color_error = hex_to_rgb("#9ece6a");
    g_bg_color_error = hex_to_rgb("#1a1b26");

    //* set the cursor back to home (0, 0) to prepare for rendering the menu
    set_cursor_position();

    //* get the dimensions of the terminal at the time of launching the application
    Dimension2D size = get_terminal_size();

    //* if the dimensions of the terminal are less than the recommended dimensions, prompt the user to change their terminal dimensions or exit the program if they so desire
    if (size.width < 127 || size.height < 43) {
        std::string prompt_string = "Your terminal size is too small and may result in poor rendering of the user interface and bad user experience. Press any key to continue or ESC to exit right away.";
        print(prompt_string);
        fill_screen(false);

        Key k = get_key();
        if (k == KEY_ESCAPE) {
            exit_program();
        }
    }

    //* set the cursor position back to home in case the warning did print
    set_cursor_position();

    //* the main rendering loop
    for(;;) {
        //* update the global terminal size
        set_terminal_size();

        //* render the menu
        menu.render(render_settings);

        //* run the menu input handler
        menu.handle_input();
    }

    //* the user should never get to this point, but if they do, exit the program safely
    exit_program(stats);
}
