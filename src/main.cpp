#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::TerminalOutput();
    int selection = 0;

    auto renderer = Renderer([&] {
        return hbox(text(std::to_string(selection)));
    });
    
    auto component = CatchEvent(renderer, [&] (Event event) {
        if (event == Event::Character('d')) {
            selection++;
            return false;
        } else if (event == Event::Character('a')) {
            selection--;
            return false;
        } else if (event == Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    });

    screen.Loop(component);
    
    return EXIT_SUCCESS;
}
