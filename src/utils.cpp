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

#include <iostream>
#include <string>
#include <sstream>

#include "utils.hpp"

void get_terminal_size(int& width, int& height) {
    #if defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
        height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
    #elif defined(__linux__)
        struct winsize w;
        ioctl(fileno(stdout), TIOCGWINSZ, &w);
        width = (int)(w.ws_col);
        height = (int)(w.ws_row);
    #endif // Windows/Linux
}

const char* fg_color(int r, int g, int b) {
    std::string out = "\033[38;2;";

    out.append(std::to_string(r));
    out.append(";");
    out.append(std::to_string(g));
    out.append(";");
    out.append(std::to_string(b));
    out.append("m");
    std::cout.write(out.data(), out.size());
    return out.data();
}

const char* fg_color(std::vector<int> rgb) {
    std::string out = "\033[38;2;";

    out.append(std::to_string(rgb.at(0)));
    out.append(";");
    out.append(std::to_string(rgb.at(1)));
    out.append(";");
    out.append(std::to_string(rgb.at(2)));
    out.append("m");
    std::cout.write(out.data(), out.size());
    return out.data();
}

const char* fg_color(const char* hex) {
    std::string out = "\033[38;2;";
    std::vector rgb = hex_to_rgb(hex);

    out.append(std::to_string(rgb.at(0)));
    out.append(";");
    out.append(std::to_string(rgb.at(1)));
    out.append(";");
    out.append(std::to_string(rgb.at(2)));
    out.append("m");
    std::cout.write(out.data(), out.size());
    return out.data();
}

const char* bg_color(int r, int g, int b) {
    std::string out = "\033[48;2;";

    out.append(std::to_string(r));
    out.append(";");
    out.append(std::to_string(g));
    out.append(";");
    out.append(std::to_string(b));
    out.append("m");
    std::cout.write(out.data(), out.size());
    return out.data();
}

const char* bg_color(std::vector<int> rgb) {
    std::string out = "\033[48;2;";

    out.append(std::to_string(rgb.at(0)));
    out.append(";");
    out.append(std::to_string(rgb.at(1)));
    out.append(";");
    out.append(std::to_string(rgb.at(2)));
    out.append("m");
    std::cout.write(out.data(), out.size());
    return out.data();
}

const char* bg_color(const char* hex) {
    std::string out = "\033[48;2;";
    std::vector rgb = hex_to_rgb(hex);

    out.append(std::to_string(rgb.at(0)));
    out.append(";");
    out.append(std::to_string(rgb.at(1)));
    out.append(";");
    out.append(std::to_string(rgb.at(2)));
    out.append("m");
    std::cout.write(out.data(), out.size());
    return out.data();
}

const char* reset_formatting() {
    std::string out = "\033[0m";
    std::cout.write(out.data(), out.size());
    return out.data();
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

std::vector<std::string> split(std::string str, char delimiter='\n') {
    std::stringstream ss(str);
    std::vector<std::string> out;

    while (ss.good()) {
        std::string line;
        getline(ss, line, delimiter);
        out.push_back(line);
    }
    return out;
}

void print_centered(std::string str, int w) {
    std::vector<std::string> lines = split(str);

    for (auto line : lines) {
        int l = line.size();
        int pos = (int)((w - l) / 2);
        
        std::string padding;
        for (int i = 0; i < pos; i++) {
            padding.append(" ");
        }
        std::cout.write(padding.data(), padding.size());
        std::cout.write(line.data(), line.size());
        std::cout.write(padding.data(), padding.size());

        std::cout.write("\n", 2);
    }
}

void print_centered(std::string str) {
    std::vector<std::string> lines = split(str);
    int w, h;
    get_terminal_size(w, h);

    for (auto line : lines) {
        int l = line.size();
        int pos = (int)((w - l) / 2);
        
        std::string padding;
        for (int i = 0; i < pos; i++) {
            padding.append(" ");
        }
        std::cout.write(padding.data(), padding.size());
        std::cout.write(line.data(), line.size());
        std::cout.write(padding.data(), padding.size());

        std::cout.write("\n", 2);
    }
}
