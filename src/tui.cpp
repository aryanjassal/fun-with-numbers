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
#include "classes.hpp"

//* Create global variables
Dimension2D t_size;
std::string alignment = "left";
Align ALIGN;
std::vector<Key> BASIC_KEYS;
ColorRGB g_bg_color = {0, 0, 0};
ColorRGB g_fg_color = {255, 255, 255};
ColorRGB g_bg_color_highlighted = {255, 255, 255};
ColorRGB g_fg_color_highlighted = {0, 0, 0};
ColorRGB g_bg_color_error = {0, 0, 0};
ColorRGB g_fg_color_error = {255, 0, 0};

//* Initialise the terminal user interface by setting default parameters
void init_tui() {
    //* Setting the terminal size
    set_terminal_size();

    //* Emplacing keys in the keys array
    for (int i = 1; i < 256; i++) {
        BASIC_KEYS.emplace_back(Key {false, (char)i, std::to_string(i)});
    }
}

//* Overloading the == operator to compare Key structs
bool operator == (const Key& lhs, const Key& rhs) {
    return ((lhs.escape_sequence == rhs.escape_sequence) && (lhs.key == rhs.key) && (lhs.full_string == rhs.full_string));
}

//* Overloading the == operator to compare Location2D structs
bool operator == (const Location2D& lhs, const Location2D& rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
};


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
void fg_color(int r, int g, int b) {
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
}

//* Sets the foreground color (the text color) using a ColorRGB object
void fg_color(ColorRGB rgb) {
    fg_color(rgb.r, rgb.g, rgb.b);
}

//* Sets the foreground color (the text color) using a constant hex code
void fg_color(const char* hex) {
    fg_color(hex_to_rgb(hex));
}

//* Sets the foreground color (the text color) using a  hex code
void fg_color(std::string hex) {
    fg_color(hex_to_rgb(hex.c_str()));
}

//* Set the background color using three integers for Red, Green, and Blue values
void bg_color(int r, int g, int b) {
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
}

//* Set the background color using a ColorRGB object
void bg_color(ColorRGB rgb) {
    bg_color(rgb.r, rgb.g, rgb.b);
}

//* Sets the background color using a constant hex code
void bg_color(const char* hex) {
    bg_color(hex_to_rgb(hex));
}

//* Sets the background color using a hex code
void bg_color(std::string hex) {
    bg_color(hex_to_rgb(hex.c_str()));
}

//* Resets all the terminal formatting
void reset_formatting() {
    std::cout << "\033[0m";
}

//* Clears the entire terminal screen using ANSI Escape Codes
void clear() {
    //* Clear everything of the screen
    std::cout << "\033[2J";
    //* Set the position of the cursor to home (0, 0)
    set_cursor_position();    
}

//* Gets the current location of the cursor and assigns it to the two passed parameters
//* Credit for this function goes to zoelabbb (https://github.com/zoelabbb/conio.h)
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

//* Sets the cursor position to given x and y coordinates
void set_cursor_position(int x, int y) {
    //* Start building the ANSI Escape Sequence to move the cursor to position
    std::string out = "\033[";

    //* Append the arguments to the ANSI Escape Sequence and close it
    out.append(std::to_string(y));
    out.append(";");
    out.append(std::to_string(x));
    out.append("H");

    //* Output the full sequence
    std::cout << out;
}

//* Sets the cursor position to home (0, 0)
void set_cursor_position() {
    set_cursor_position(0, 0);
}

//* Sets the cursor position to the coordinates given in the passed Location2D object
void set_cursor_position(Location2D location) {
    set_cursor_position(location.x, location.y);
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
    //* The std::string.c_str() method converts an std::string object to const char* object 
    return hex_to_rgb(hex.c_str());
}

//* Returns a vector of std::string split by the given delimiter
std::vector<std::string> split(std::string str, char delimiter) {
    //* Create a string stream to use fancy functions such as getline() which automatically separates strings by delimiter
    std::stringstream ss(str);

    //* Initialise the output vector
    std::vector<std::string> out;

    //* While there are no errors in the string stream...
    while (ss.good()) {
        //* ...get a line separated by a given delimiter...
        std::string line;
        getline(ss, line, delimiter);
        //* ... and append it to the output vector
        out.push_back(line);
    }

    //* Return the output vector of split strings
    return out;
}

//* Return a vector of strings split by newline (\n) delimiter
std::vector<std::string> split(std::string str) {
    return split(str, '\n');
}

//* Sets the global alignment to the left
void align_left() {
    alignment = ALIGN.LEFT;
}

//* Sets the global alignment to the center
void align_center() {
    alignment = ALIGN.CENTER;
}

//* Sets the global alignment to the right
void align_right() {
    alignment = ALIGN.RIGHT;
}

//* Sets the alignment variable depending on what alignment state was passed in
//* If no existing states match, throw an error
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

//* Calculate left padding of a string to fit in width w
//* Typically used in tandem with its complementary method: calculate_padding_right()
int calculate_padding_left(std::string str, int w) {
    //* This complicated looking code basically counts the number of characters in the given string
    //* Unicode characters are long codes which get interpreted as multiple characters even though they output one character
    //* This code counts each unicode character as one instead of counting the number of characters
    int l = (str.length() - count_if(str.begin(), str.end(), [](char c) -> bool { return (c & 0xc0) == 0x80; }));

    //* Return the left padding using some basic math. Loss of fraction happens which is later rectified by the calculate_padding_right() complementary method
    return (int)((w - l) / 2);
}

//* Calculate left padding of a string to fit in the width of the terminal
//* Typically used in tandem with its complementary method: calculate_padding_right()
int calculate_padding_left(std::string str) {
    return calculate_padding_left(str, t_size.width);
}

//* Calculate right padding of a string to fit in width w
//* Typically used in tandem with its complementary method: calculate_padding_left()
int calculate_padding_right(std::string str, int w) {
    //* This complicated looking code basically counts the number of characters in the given string
    //* Unicode characters are long codes which get interpreted as multiple characters even though they output one character
    //* This code counts each unicode character as one instead of counting the number of characters
    //TODO: [REQU] Use the function unicode_len() instead of this redundant piece of code
    int l = (str.length() - count_if(str.begin(), str.end(), [](char c) -> bool { return (c & 0xc0) == 0x80; }));

    //* Return the right padding using some basic math
    //* Complementary method of calculate_padding_left()
    if ((w - l) % 2 == 0) { //* If the resultant width is even, then there is no loss of fraction, so return it as it is
        return (int)((w - l) / 2);
    } else { //* Otherwise, loss of fraction is likely. Use this slightly different formula to rectify the problem.
        return (((w - l) + 1) / 2);
    }
}

//* Calculate left padding of a string to fit in the width of the terminal
//* Typically used in tandem with its complementary method: calculate_padding_left()
int calculate_padding_right(std::string str) {
    return calculate_padding_right(str, t_size.width);
}

//* Returns the string which is padded to the width <w>, aligned to the global alignment, and ending in the character <end>, while being padded with the character <filler>
std::string padded_str(std::string str, std::string filler, int w, std::string end) {
    //* If string is empty (""), make the string at least one character wide by assigning it a white space, then rerunning this method to properly pad empty strings
    if (!str.length()) {
        str = filler;
        return padded_str(str, filler, w, end);
    }
    
    //* Add spaces to the output string corresponding with the padding required for left and right sides of the string
    std::string pl = extend_string(filler, calculate_padding_left(str, w));
    std::string pr = extend_string(filler, calculate_padding_right(str, w));

    //* Create an output string
    std::string out;

    if (alignment == ALIGN.LEFT) { //* If the global alignment is set to left, then first output the string, then output both the left and right padding, then output the end character
        out.append(str);
        out.append(pl);
        out.append(pr);
        out.append(end);
    } else if (alignment == ALIGN.CENTER) { //* If the global alignment is set to center, then first output the left padding, then output the string, then output the right padding, then output the end character
        out.append(pl);
        out.append(str);
        out.append(pr);
        out.append(end);
    } else if (alignment == ALIGN.RIGHT) { //* If the global alignment is set to right, then first output both the left and right padding, then output the string, then output the end character
        out.append(pl);
        out.append(pr);
        out.append(str);
        out.append(end);
    } else { //* Otherwise, the alignment state is set to be in an invalid state. Throw an error message.
        throw "Alignment state invalid";
    }

    //* Return the padded string
    return out;
}

//* Return a padded string which is <w> characters wide and ends with a newline (\n) character and is padded with " " (spaces)
std::string padded_str(std::string str, int w) {
    return padded_str(str, " ", w, "\n");
}

//* Return a padded string which is as wide as the current terminal width and ends with a newline (\n) character and is padded with " " (spaces)
std::string padded_str(std::string str) {
    return padded_str(str, " ", t_size.width, "\n");
}

//* Return a padded string which is as wide as <w> and ends with <end> and is padded with " " (spaces)
std::string padded_str(std::string str, int w, std::string end) {
    return padded_str(str, " ", w, end);
}

//* Return a padded string which is as wide as the current terminal width and ends with a newline (\n) and is padded with <filler>
std::string padded_str(std::string str, std::string filler) {
    return padded_str(str, filler, t_size.width, "\n");
}

//* Return a padded string with a width of <w> and is padded with the character <filler> and ends with a newline (\n)
std::string padded_str(std::string str, std::string filler, int w) {
    return padded_str(str, filler, w, "\n");
}

//* Returns a padded string as wide as the terminal and padded with <filler> and ends with <end>
std::string padded_str(std::string str, std::string filler, std::string end) {
    return padded_str(str, filler, t_size.width, end);
}

//* Prints a string <str> with the ending character(s) <end> and the width of <w>
void print(std::string str, std::string end, int w) {
    //* Print statement first splits the string by newline (\n)
    std::vector<std::string> lines = split(str, '\n');

    //* If the given width is less than or equal to zero, then instead use the current terminal width
    //? This behaviour may change in the future
    int width = (w <= 0) ? t_size.width : w;

    //* Loop over each line in the vector of split strings
    for (auto line : lines) {
        //* Output the padded line which is padded to the given width and the end character
        std::cout << padded_str(line, width, end);
    }
}

//* Prints a new line
void print() {
    print("", "\n", 0);
}

//* Prints a string <str> with the last character being newline (\n) using the entire width of the terminal
void print(std::string str) {
    print(str, "\n", 0);
}

//* Prints a string <str> with the given width <w> and the last character being newline (\n)
void print(std::string str, int w) {
    print(str, "\n", w);
}

//* Prints a string <str> with the given last character using the entire width of the terminal
void print(std::string str, std::string end) {
    print(str, end, 0);
}

//* Prints a string <str> <times> amount of times with the given end character
//* Ideal to print multiple blank lines but make the code look elegant
void print_loop(std::string str, int times, std::string end) {
    for (int i = 0; i < times; i++) {
        print(str, end);
    }
}

//* Prints out <str> <times> amount of times with the end character of newline (\n)
void print_loop(std::string str, int times) {
    print_loop(str, times, "");
}

//* Get the next character waiting in the keyboard input buffer
//* Credit for this code goes to zoelabbb (https://github.com/zoelabbb/conio.h)
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

//* Parses key presses into understandable return object
Key get_key() {
    //* Get a character from the input buffer
    char c = getch();
    switch(c) {
        case 27: //* If the first character is an escape character
            //* If there are no other characters in keyboard input buffer, then return escape as the character
            if (!kbhit()) return KEY_ESCAPE;
            
            //* Get the next character from the keyboard input buffer and check for states
            switch(getch()) {
                case 91: //* If the next character is 91 (opened-square-bracket), then check for character states 
                    switch(getch()) {
                        case 65: //* If the next character is 65 and no other inputs are in the keyboard input buffer, then the up arrow has been pressed
                            if (!kbhit()) return KEY_UP_ARROW;
                            //* Otherwise, clear the keyboard input buffer and break out of the loop
                            while (kbhit()) getch();
                            break;
                        case 66: //* If the next character is 66 and no other inputs are in the keyboard input buffer, then the down arrow has been pressed
                            if (!kbhit()) return KEY_DOWN_ARROW;
                            //* Otherwise, clear the keyboard input buffer and break out of the loop
                            while (kbhit()) getch();
                            break;
                        case 67: //* If the next character is 67 and no other inputs are in the keyboard input buffer, then the right arrow has been pressed
                            if (!kbhit()) return KEY_RIGHT_ARROW;
                            //* Otherwise, clear the keyboard input buffer and break out of the loop
                            while (kbhit()) getch();
                            break;
                        case 68: //* If the next character is 68 and no other inputs are in the keyboard input buffer, then the left arrow has been pressed
                            if (!kbhit()) return KEY_LEFT_ARROW;
                            //* Otherwise, clear the keyboard input buffer and break out of the loop
                            while (kbhit()) getch();
                            break;
                        default: //* By default, disregard all the other inputs kept in the keyboard input buffer and return KEY_NULL
                            while (kbhit()) getch();
                            return KEY_NULL;
                    }
                    //* Just do this in case there is anything still left in the keyboard input buffer
                    while (kbhit()) getch();
                default: //* If the key is not 91 (opened-square-bracket), then disregard all the other inputs kept in the keyboard input buffer and return KEY_NULL
                    while(kbhit()) getch();
                    return KEY_NULL;
            }
            //* Just do this in case there is anything still left in the keyboard input buffer
            while (kbhit()) getch();
        default: //* If the key is not 27 (escape), then do this
            //* If the key is in BASIC_KEYS, then return that object
            for(auto k : BASIC_KEYS) {
                if (k.key == c) return k;
            }

            //* Otherwise, disregard all the other inputs kept in the keyboard input buffer and return KEY_NULL
            while(kbhit()) getch();
            return KEY_NULL;
    }
}

//* Check if a key is present in the input buffer
//* Credit for this code goes to zoelabbb (https://github.com/zoelabbb/conio.h)
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

//* Works like (string * num) in python, appending a string <times> amount of times and returning the string
std::string extend_string(std::string str, int times) {
    //* Create the output string
    std::string out;
    
    //* Append the string str to the output string out as many times as specified by the user
    for (int i = 0; i < times; i++) {
        out.append(str);
    }

    //* Return the extended string
    return out;
}

//* Append a character to a string <times> amount of times and return the string
std::string extend_string(char str, int times) {
    return extend_string(std::string(1, str), times);
}

//* Append a character to a string <times> amount of times and return the string
std::string extend_string(const char* str, int times) {
    return extend_string(std::string(str), times);
}

//* Fills the screen with blank prints
Location2D fill_screen(bool c_text) {
    std::string credit = "Credit to zoelabbb (https://github.com/zoelabbb/) for providing inspiration and some parts of the code from their project \"conio.h for linux\" (https://github.com/zoelabbb/conio.h/blob/master/conio.h). Credit to brynblack (https://github.com/brynblack) for providing the integer factorisation method used in this project.";
    
    std::vector<std::string> lines = split(basic_text_wrapping(credit));

    Location2D xy = wherexy();
    int h = xy.y;
    int ht = t_size.height - lines.size();
    if (c_text) {
        while (h < ht) {
            h++;
            print();
        }
        print(basic_text_wrapping(credit));
        print("", "");
    } else {
        while (h < t_size.height - 1) {
            h++;
            print();
        }
        print("", "");
    }
    return xy;
}

Location2D fill_screen() {
    return fill_screen(true);
}

//* Wraps the string to fit in the width
//TODO: Long words break this. Need to add hypenation.
//? Testing unicode characters
std::string basic_text_wrapping(std::string str, int width) {
    std::vector<std::string> words = split(str, ' ');
    std::string temp;
    std::string out;
    int new_lines = 0;

    for(auto word : words) {
        if (unicode_len(temp) + unicode_len(word) < width) {
            temp.append(word);
            temp.append(" ");
            new_lines = 0;
        } else {
            temp.pop_back();
            temp.append("\n");
            out.append(temp);
            temp = "";
            temp.append(word);
            temp.append(" ");
        }
    }

    if (unicode_len(temp) > 0) {
        temp.pop_back();
        out.append(temp);
    }

    return out;
}

//* Wraps the text by given width with const char*
//* Works the same as print()
std::string basic_text_wrapping(const char* str, int width) {
    return basic_text_wrapping((std::string)str, t_size.width);
}

//* Wraps the text by the terminal width
//* Works the same as print()
std::string basic_text_wrapping(std::string str) {
    return basic_text_wrapping(str, t_size.width);
}

//* Wraps the text by the terminal width
//* Works the same as print()
std::string basic_text_wrapping(const char* str) {
    return basic_text_wrapping((std::string)str, t_size.width);
}
