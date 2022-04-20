//* Including required modules
#include <sys/ioctl.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <fcntl.h>

#include "tui.hpp"
#include "utils.hpp"

//* Create global variables
Dimension2D t_size;
std::string alignment = "left";
Align ALIGN;

//* Initialise the terminal user interface by setting default parameters
void init_tui() {
    //* Setting the terminal size
    set_terminal_size();
}

//* Get the dimensions of the terminal
void get_terminal_size(int& width, int& height) {
    //* Winsize struct is a special struct which stores all the terminal information returned by the following command
    struct winsize w;
    //* This is the magic command which returns the terminal information for linux systems
    ioctl(fileno(stdout), TIOCGWINSZ, &w);

    //* Assign the number of columns and rows to the width and height
    width = (int)(w.ws_col);
    height = (int)(w.ws_row);
}

//* Get the dimensions of the terminal and store it in the global variables
void set_terminal_size() {
    //* Get the terminal size and assign it to the t_size global variable
    get_terminal_size(t_size.width, t_size.height);
}

//* Returns the size of the terminal in a Dimension2D object
Dimension2D get_terminal_size() {
    Dimension2D dim;
    get_terminal_size(dim.width, dim.height);
    return dim;
}

//* Set the foreground color (the text color) using three integers for Red, Green, and Blue values
std::string fg_color(int r, int g, int b) {
    //* Start building the ANSI Escape code
    std::string out = "\033[38;2;";

    //* Append the RGB values and end the ANSI Escape Code
    out.append(std::to_string(r));
    out.append(";");
    out.append(std::to_string(g));
    out.append(";");
    out.append(std::to_string(b));
    out.append("m");

    //* Print it out to the screen to apply the formatting
    std::cout << out;
    //! May be redundant. More testing needed.
    return out;
}

//* Sets the foreground color (the text color) using a ColorRGB object
std::string fg_color(ColorRGB rgb) {
    return fg_color(rgb.r, rgb.g, rgb.b);
}

//* Sets the foreground color (the text color) using a constant hex code
std::string fg_color(const char* hex) {
    ColorRGB rgb = hex_to_rgb(hex);
    return fg_color(rgb);
}

//* Sets the foreground color (the text color) using a changeable hex code
//! DANGEROUS TO USE THIS
std::string fg_color(std::string hex) {
    ColorRGB rgb = hex_to_rgb(hex);
    return fg_color(rgb);
}

//* Set the background color using three integers for Red, Green, and Blue values
std::string bg_color(int r, int g, int b) {
    //* Start building the ANSI Escape code
    std::string out = "\033[48;2;";

    //* Append the RGB values and end the ANSI Escape Code
    out.append(std::to_string(r));
    out.append(";");
    out.append(std::to_string(g));
    out.append(";");
    out.append(std::to_string(b));
    out.append("m");

    //* Print it out to the screen to apply the formatting
    std::cout << out;
    //! May be redundant. More testing needed.
    return out;
}

//* Set the background color using a ColorRGB object
std::string bg_color(ColorRGB rgb) {
    return bg_color(rgb.r, rgb.g, rgb.b);
}

//* Sets the background color using a constant hex code
std::string bg_color(const char* hex) {
    ColorRGB rgb = hex_to_rgb(hex);
    return bg_color(rgb);
}

//* Sets the background color using a changeable string as hex code
//! DANGEROUS TO USE THIS
std::string bg_color(std::string hex) {
    ColorRGB rgb = hex_to_rgb(hex);
    return bg_color(rgb);
}

//* Resets all the terminal formatting
std::string reset_formatting() {
    std::string out = "\033[0m";
    std::cout << out;
    return out;
}

//* Clears the entire terminal screen using ANSI Escape Codes
std::string clear() {
    //* Clear everything of the screen
    std::string out = "\033[2J";
    //* Set the position of the cursor to home (0, 0)
    out.append(set_cursor_position());
    
    std::cout << out;
    return out;
}

//* Gets the current location of the cursor and assigns it to the two passed parameters 
void wherexy(int &x, int &y) {
    std::cout << "\033[6n";

    if(getch() != '\x1B') return;
    if(getch() != '\x5B') return;

    int in;
    int ly = 0;

    while((in = getch()) != ';')
    ly = ly * 10 + in - '0';	

    int lx = 0;
    while((in = getch()) != 'R')
    lx = lx * 10 + in - '0';

    x = lx;
    y = ly;
}

//* Gets the current location of the cursor in a Location2D object
struct Location2D wherexy() {
    Location2D xy;
    wherexy(xy.x, xy.y);
    return xy;
}

//! NOT FUNCTIONAL
const char* hide_cursor() {
    return "\033[?25l";
}

//! NOT FUNCTIONAL
const char* show_cursor() {
    return "\033[?25h";
}

std::string set_cursor_position() {
    return set_cursor_position(0, 0);
}

std::string set_cursor_position(int x, int y) {
    std::string out = "\033[";
    out.append(std::to_string(y));
    out.append(";");
    out.append(std::to_string(x));
    out.append("H");

    std::cout << out;
    return out;
}

//* Convert a hex color code into RGB values and return them in a ColorRGB struct
struct ColorRGB hex_to_rgb(const char* hex) {
    //* Define the color struct which will be returned
    ColorRGB color;

    //* Use sscanf to decode the values of the hex to RGB values and assign them to corresponding color value
    std::sscanf(hex, "#%02x%02x%02x", &color.r, &color.g, &color.b);
    
    //* Return the color
    return color;
}

//* Convert a hex color code into RGB values and return them in a ColorRGB struct
struct ColorRGB hex_to_rgb(std::string hex) {
    return hex_to_rgb(hex.c_str());
}

std::vector<std::string> split(std::string str) {
    return split(str, '\n');
}

std::vector<std::string> split(std::string str, const char delimiter) {
    std::stringstream ss(str);
    std::vector<std::string> out;

    while (ss.good()) {
        std::string line;
        getline(ss, line, delimiter);
        out.push_back(line);
    }
    return out;
}

void align_left() {
    alignment = ALIGN.LEFT;
}

void align_center() {
    alignment = ALIGN.CENTER;
}

void align_right() {
    alignment = ALIGN.RIGHT;
}

void align(std::string align) {
    if (align == ALIGN.LEFT) {
        align_left();
    } else if (align == ALIGN.CENTER) {
        align_center();
    } else if (align == ALIGN.RIGHT) {
        align_right();
    } else {
        throw std::invalid_argument("received invalid alignment state");
    }
}

int calculate_padding_left(std::string str, int w) {
    int l = (str.length() - count_if(str.begin(), str.end(), [](char c) -> bool { return (c & 0xc0) == 0x80; }));
    return (int)((w - l) / 2);
}

int calculate_padding_left(std::string str) {
    return calculate_padding_left(str, t_size.width);
}

int calculate_padding_right(std::string str, int w) {
    int l = (str.length() - count_if(str.begin(), str.end(), [](char c) -> bool { return (c & 0xc0) == 0x80; }));
    if ((w - l) % 2 == 0) {
        return (int)((w - l) / 2);
    } else {
        return (((w - l) + 1) / 2);
    }
}

int calculate_padding_right(std::string str) {
    return calculate_padding_right(str, t_size.width);
}

std::string padded_str(std::string str, int w, const char* end) {
    if (!str.length()) {
        str.append(" ");
        return padded_str(str, w, end);
    }

    int plc = calculate_padding_left(str, w);
    int prc = calculate_padding_right(str, w);
    
    std::string pl;
    std::string pr;
    for (int i = 0; i < plc; i++) {
        pl.append(" ");
    }
    for (int i = 0; i < prc; i++) {
        pr.append(" ");
    }

    std::string out;

    if (alignment == ALIGN.LEFT) {
        out.append(str);
        out.append(pl);
        out.append(pr);
        out.append(end);
    } else if (alignment == ALIGN.CENTER) {
        out.append(pl);
        out.append(str);
        out.append(pr);
        out.append(end);
    } else if (alignment == ALIGN.RIGHT) {
        out.append(pl);
        out.append(pr);
        out.append(str);
        out.append(end);
    } else {
        std::cout << "Alignment state not valid";
        exit_program();
    }

    while (out.length() < w) {
        out.append(" ");
    }

    return out;
}

std::string padded_str(std::string str, int w) {
    return padded_str(str, w, "\n");
}

std::string padded_str(std::string str) {
    return padded_str(str, t_size.width, "\n");
}

void print() {
    print("", "\n", 0);
}

void print(std::string str) {
    print(str, "\n", 0);
}

void print(std::string str, int w) {
    print(str, "\n", w);
}

void print(std::string str, std::string end) {
    print(str, end, 0);
}

void print(std::string str, std::string end, int w) {
    std::vector<std::string> lines = split(str);
    int width = (w <= 0) ? t_size.width : w;

    for (auto line : lines) {
        std::string padded = padded_str(line, width, end.c_str());
        std::cout << padded;
    }
}

void print_loop(std::string str, int times) {
    for (int i = 0; i < times; i++) {
        print(str);
    }
}

char getch() {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

//TODO: get a KEY struct

char get_key() {
    char c = getch();
    if (c == 27) {
        if (!kbhit()) return c;

        char d = getch();
        if (d == 91) {
            char e = getch();
            if (e == 49) {
                getch();
                getch();
                return getch();
            } else if (e == 50) {
                while (kbhit()) getch();
                return 0; // INSERT or a F<x> key
            } else if (e == 51) {
                while (kbhit()) getch();
                return 0; // DELETE
            } else if (e == 53) {
                while (kbhit()) getch();
                return 0; // PAGE UP
            } else if (e == 54) {
                while (kbhit()) getch();
                return 0; // PAGE DOWN
            } else {
                return e;
            }
            throw std::invalid_argument("KEY NOT SUPPORTED");
        } else if (d == 79) {
            while (kbhit()) getch();
            return 0; // FUNCTION KEYS
        }
        return c;
    }
    return c;
}

bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return true;
    }

    return false;
}

//* Defining menu functions
void Menu::add_option(std::string str, std::function<void()> func) {
    Line line;
    line.id = next_id;
    line.label = str;
    line.func = func;
    line.interactable = true;
    lines.emplace_back(line);
    next_id++;
}

void Menu::add_line() {
    Menu::add_line("");
}

void Menu::add_line(std::string str) {
    Line line;
    line.label = str;
    line.interactable = false;
    lines.emplace_back(line);
}

void Menu::move_selection_up() {
    Menu::move_selection_up(1);
}

void Menu::move_selection_up(int by) {
    if (!loop_menu_options) {
        selection = std::clamp(selection - by, 0, next_id - 1);
    } else {
        selection = ((selection - by) < 0) ? next_id - 1 : selection - by;
    }
}

void Menu::move_selection_down() {
    Menu::move_selection_down(1);
}

void Menu::move_selection_down(int by) {
    if (!loop_menu_options) {
        selection = std::clamp(selection + by, 0, next_id - 1);
    } else {
        selection = ((selection + by) > next_id - 1) ? 0 : selection + by;
    }
}

void Menu::set_entry_loop(bool val) {
    loop_menu_options = val;
}

void Menu::render() {
    MenuRenderSettings render_settings;
    render_settings.selection_size = 40;

    Menu::render(render_settings);
}

void Menu::render(MenuRenderSettings render_settings) {
    for (auto& l : lines) {
        align(render_settings.alignment);

        std::string text;
        text.append(padded_str(l.label, render_settings.selection_size, ""));

        fg_color(render_settings.fg_color_hex.c_str());
        bg_color(render_settings.bg_color_hex.c_str());

        if (selection == l.id) {
            std::string pl = extend_string(" ", calculate_padding_left(text));
            std::string pr = extend_string(" ", calculate_padding_right(text));

            std::cout << pl;

            fg_color(render_settings.fg_color_highlighted_hex.c_str());
            bg_color(render_settings.bg_color_highlighted_hex.c_str());

            std::cout << text;

            fg_color(render_settings.fg_color_hex.c_str());
            bg_color(render_settings.bg_color_hex.c_str());

            std::cout << pr << "\n";
        } else {
            print(text);
        }
        print();
    }

    Location2D xy = wherexy();
    while (xy.y < t_size.height - 1) {
        xy = wherexy();
        print();
    }
}

void Menu::handle_input() {
    switch(get_key()) {
        case UP_ARROW:
            move_selection_up();
            break;
        case DOWN_ARROW:
            move_selection_down();
            break;
        case RETURN:
            for (auto& l : lines) {
                if (l.id == selection) {
                    l.func();
                }
            }
        case KEY_Q:
            exit_program();
    }
}
