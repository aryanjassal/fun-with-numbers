#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

using namespace ftxui;

int main() {
    //* Define the document
    Element document = hbox({
        text("left") | border,
        text("middle") | border,
        text("right") | border
    });

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));

    Render(screen, document);
    screen.Print();
    
    return EXIT_SUCCESS;
}
