#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::TerminalOutput();
    std::vector<std::string> options = {
        "Check number features",
        "Plot numbers",
        "Check overall stats"
    };
    int selection = 0;

    MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    auto menu = Menu(&options, &selection, &option);
    
    screen.Loop(menu);
    
    return EXIT_SUCCESS;
}
