#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

using namespace ftxui;

int main() {
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
    
    return EXIT_SUCCESS;
}
