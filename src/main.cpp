#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>
#include <string>

using namespace ftxui;

void example_1() {
    //Define colours
    auto tn_storm_black_bg = Color::RGB(36, 40, 59);
    auto tn_storm_white_text = Color::RGB(207, 201, 194);

    // Define the document
    Element document = window(text("Example Window"), hbox({
        text("left") | border,
        text("middle") | border | flex,
        text("right") | border,

        separator(),

        hbox({
            text("separated text") | border,
        }),

        separator(),

        hbox({
            text("I love tokyo night color theme") | border | bgcolor(tn_storm_black_bg) | color(tn_storm_white_text)
        }),
    })) /*| bgcolor(tn_storm_black_bg) | color(tn_storm_white_text)*/;

    auto screen = Screen::Create(
        Dimension::Full(),          // width
        Dimension::Fit(document)    // height
    );

    Render(screen, document);
    screen.Print();
}

int main() {
    // example_1();

    // Initialise the input strings
    std::string first_name;
    std::string last_name;
    std::string password;

    // Create a custom component for first and last name
    Component input_first_name = Input(&first_name, "First name");
    Component input_last_name = Input(&last_name, "Last name");

    // Set password to true within the input options, then create the custom component for password
    InputOption password_option;
    password_option.password = true;
    Component input_password = Input(&password, "Password", password_option);

    // Stack all the components in a vertical container
    auto component = Container::Vertical({
        input_first_name,
        input_last_name,
        input_password
    });

    // Create a custom renderer to render the components
    auto renderer = Renderer(component, [&] {
        return vbox({
            // Greets you as per input
            text("Hello, " + first_name + " " + last_name),
            // Vertical separator
            separator(),
            // Rendering out the form fields
            hbox(text(" First name: "), input_first_name -> Render()),
            hbox(text(" Last name: "), input_last_name -> Render()),
            hbox(text(" Password: "), input_password -> Render()),
        }) | border; // Add border to the entire vertical box
    });

    // Create an interactive screen... or something...
    // idk how it works, man. This is just pure black magic to me.
    auto screen = ScreenInteractive::TerminalOutput();
    // Loop the screen to keep on rendering the form
    screen.Loop(renderer);
    
    // This is redundant, basically.
    return EXIT_SUCCESS;
}
