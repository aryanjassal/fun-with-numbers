//* If operating system is Windows, then...
#if defined(_WIN32)
//* ...set some flags for Windows features and tools to work properly
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
//* Include the Windows.h header file which includes Windows-specific tools
#include <Windows.h>
//* Otherwise, if the operating system is linux-based, then...
#elif defined(__linux__)
//* ...include the linux-specific library and tools
#include <sys/ioctl.h>
#endif

//* Including required modules
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iomanip>

#include "tui.hpp"

//* Create global variables
Dimension2D t_size;
std::string alignment = "left";

void init_tui() {
    get_terminal_size();
    // hide_cursor();
}

//* Get the dimensions of the terminal. This method works for both Windows based machines and Linux based machines (MacOS is, in fact, built upon linux)
void get_terminal_size(int& width, int& height) {
    //* If the system is Windows-based, then do the following
    #if defined(_WIN32)
        //* Create a screen buffer (the terminal) information object
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        //* Ask the terminal to get screen information, and store it in the previously defined variable
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        //* Get the width and height of the terminal and assign it to the corresponding variable
        width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
        height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
    //* Otherwise, do this instead
    #elif defined(__linux__)
        //* Winsize struct is a special struct which stores all the terminal information returned by the following command
        struct winsize w;
        //* This is the magic command which returns the terminal information for linux systems
        ioctl(fileno(stdout), TIOCGWINSZ, &w);

        //* Assign the number of columns and rows to the width and height
        width = (int)(w.ws_col);
        height = (int)(w.ws_row);
    #endif
}

//* Get the dimensions of the terminal and store it in the global variables. Works the same as the previous function.
void get_terminal_size() {
    //* If the system is Windows-based, then do the following
    #if defined(_WIN32)
        //* Create a screen buffer (the terminal) information object
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        //* Ask the terminal to get screen information, and store it in the previously defined variable
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        //* Get the width and height of the terminal and assign it to the corresponding variable
        t_size.width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
        t_size.height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
    //* Otherwise, do this instead
    #elif defined(__linux__)
        //* Winsize struct is a special struct which stores all the terminal information returned by the following command
        struct winsize w;
        //* This is the magic command which returns the terminal information for linux systems
        ioctl(fileno(stdout), TIOCGWINSZ, &w);

        //* Assign the number of columns and rows to the width and height
        t_size.width = (int)(w.ws_col);
        t_size.height = (int)(w.ws_row);
    #endif
}

//* Set the foreground color (the text color) using three integers for Red, Green, and Blue values
std::string fg_color(int r, int g, int b) {
    std::string out = "\033[38;2;";

    out.append(std::to_string(r));
    out.append(";");
    out.append(std::to_string(g));
    out.append(";");
    out.append(std::to_string(b));
    out.append("m");

    std::cout << out;
    return out;
}

std::string fg_color(std::vector<int> rgb) {
    return fg_color(rgb.at(0), rgb.at(1), rgb.at(2));
}

std::string fg_color(const char* hex) {
    std::vector rgb = hex_to_rgb(hex);
    return fg_color(rgb);
}

std::string bg_color(int r, int g, int b) {
    std::string out = "\033[48;2;";

    out.append(std::to_string(r));
    out.append(";");
    out.append(std::to_string(g));
    out.append(";");
    out.append(std::to_string(b));
    out.append("m");

    std::cout << out;
    return out;
}

std::string bg_color(std::vector<int> rgb) {
    return bg_color(rgb.at(0), rgb.at(1), rgb.at(2));
}

std::string bg_color(const char* hex) {
    std::vector rgb = hex_to_rgb(hex);
    return bg_color(rgb);
}

std::string reset_formatting() {
    std::string out = "\033[0m";
    std::cout << out;
    return out;
}

std::string clear() {
    std::string out = "\033[2J";
    out.append(set_cursor_position());
    
    std::cout << out;
    return out;
}

//! NOT FUNCTIONAL
const char* hide_cursor() {
    return "\033[8m";
}

//! NOT FUNCTIONAL
const char* show_cursor() {
    return "\033[28m";
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

std::string move_cursor_up() {
    return move_cursor_up(1);
}

std::string move_cursor_up(int lines) {
    std::string out = "\033[";
    out.append(std::to_string(lines));
    out.append("A");

    std::cout << out;
    return out;
}

void hex_to_rgb(const char* hex, int r, int g, int b) {
    std::sscanf(hex, "#%02x%02x%02x", &r, &g, &b);
}

std::vector<int> hex_to_rgb(const char* hex) {
    int r, g, b;
    std::vector<int> out;
    std::sscanf(hex, "#%02x%02x%02x", &r, &g, &b);
    
    out.push_back(r);
    out.push_back(g);
    out.push_back(b);
    return out;
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
    alignment = "left";
}

void align_center() {
    alignment = "center";
}

void align_right() {
    alignment = "right";
}

void align(std::string align) {
    if (align == "left") {
        align_left();
    } else if (align == "center") {
        align_center();
    } else if (align == "right") {
        align_right();
    } else {
        throw std::invalid_argument("received invalid alignment state");
    }
}

int calculate_padding(std::string str, int w) {
    int l = (str.length() - count_if(str.begin(), str.end(), [](char c)->bool { return (c & 0xC0) == 0x80; }));
    return (int)((w - l) / 2);
}

int calculate_padding(std::string str) {
    return calculate_padding(str, t_size.width);
}

std::string padded_str(std::string str, int w, const char* end) {
    int l = (str.length() - count_if(str.begin(), str.end(), [](char c)->bool { return (c & 0xC0) == 0x80; }));

    if (!l) {
        str.append(" ");
        return padded_str(str, w, end);
    }

    int pos = (int)((w - l) / 2);
    
    std::string padding;
    for (int i = 0; i < pos; i++) {
        padding.append(" ");
    }

    std::string out;

    if (alignment == "left") {
        out.append(str);
        out.append(padding);
        out.append(padding);
        out.append(end);
    } else if (alignment == "center") {
        out.append(padding);
        out.append(str);
        out.append(padding);
        out.append(end);
    } else if (alignment == "right") {
        out.append(padding);
        out.append(padding);
        out.append(str);
        out.append(end);
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

void print(std::string str="") {
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

void print_raw(std::string str) {
    std::cout << str;
}

void print_loop(int times, std::string str) {
    for (int i = times; i > 0; i--) {
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

char get_key() {
    char c = getch();
    if (c == 27) {
        char d = getch();
        if (d == 91) {
            return getch();
        }
        return c;
    }
    return c;
}
