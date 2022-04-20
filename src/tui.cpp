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
std::vector<Key> BASIC_KEYS;

//* Initialise the terminal user interface by setting default parameters
void init_tui() {
    //* Setting the terminal size
    set_terminal_size();

    //* Emplacing keys in the keys array
    for (int i = 0; i < 256; i++) {
        BASIC_KEYS.emplace_back(Key {false, i, std::to_string(i)});
    }
}

//* Overloading the == operator to compare Key structs
bool operator == (const Key& lhs, const Key& rhs) {
    return ((lhs.escape_sequence == rhs.escape_sequence) && (lhs.key == rhs.key) && (lhs.full_string == rhs.full_string));
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
std::vector<std::string> split(std::string str, const char delimiter) {
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

//* Returns the string which sits in the middle of the width <w>, ending in the character <end>
std::string padded_str(std::string str, int w, const char* end) {
    //* If string is empty (""), make the string at least one character wide by assigning it a white space, then rerunning this method to properly pad empty strings
    if (!str.length()) {
        str = " ";
        return padded_str(str, w, end);
    }
    
    //* Add spaces to the output string corresponding with the padding required for left and right sides of the string
    std::string pl = extend_string(" ", calculate_padding_left(str, w));;
    std::string pr = extend_string(" ", calculate_padding_right(str, w));;

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
    } else { //* Otherwise, the alignment state is set to be in an invalid state. Warn the user about it and then exit the program gracefully.
        std::cout << "Alignment state not valid";
        exit_program();
    }

    //* Failsafe to append extra spaces if the resultant string is not quite as wide as the width. May happen when the width is an odd number
    while (out.length() < w) {
        out.append(" ");
    }

    //* Return the padded string
    return out;
}

//* Return a padded string which is <w> characters wide and ends with a newline (\n) character
std::string padded_str(std::string str, int w) {
    return padded_str(str, w, "\n");
}

//* Return a padded string which is as wide as the current terminal width and ends with a newline (\n) character
std::string padded_str(std::string str) {
    return padded_str(str, t_size.width, "\n");
}

//* Prints a string <str> with the ending character(s) <end> and the width of <w>
void print(std::string str, std::string end, int w) {
    //* Print statement first splits the string by newline (\n)
    std::vector<std::string> lines = split(str);

    //* If the given width is less than or equal to zero, then instead use the current terminal width
    //? This behaviour may change in the future
    int width = (w <= 0) ? t_size.width : w;

    //* Loop over each line in the vector of split strings
    for (auto line : lines) {
        //* Output the padded line which is padded to the given width and the end character
        std::cout << padded_str(line, width, end.c_str());
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

//* Prints a string <str> <times> amount of times.
//* Ideal to print multiple blank lines but make the code look elegant
void print_loop(std::string str, int times) {
    for (int i = 0; i < times; i++) {
        print(str);
    }
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

//TODO: get a KEY struct

//* Parses key presses into understandable return object
Key get_key() {
    char c = getch();
    switch(c) {
        case 27:
            if (!kbhit()) return KEY_ESCAPE;
            
            switch(getch()) {
                case 91:
                    switch(getch()) {
                        case 65:
                            if (!kbhit()) return KEY_UP_ARROW;
                            break;
                        case 66:
                            if (!kbhit()) return KEY_DOWN_ARROW;
                            break;
                        case 67:
                            if (!kbhit()) return KEY_RIGHT_ARROW;
                            break;
                        case 68:
                            if (!kbhit()) return KEY_LEFT_ARROW;
                            break;
                        default:
                            while (kbhit()) getch();
                            return KEY_NULL;
                    }
                default:
                    while(kbhit()) getch();
                    return KEY_NULL;
            }
        default:
            for(auto k : BASIC_KEYS) {
                if (k.key == c) return k;
            }

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



//* Defining methods used by the Menu class

//* Add a new option to the menu with the label <str> and with the action <func>
void Menu::add_option(std::string str, std::function<void()> func) {
    //* Create a new entry object and set all its parameters
    Entry entry;
    entry.id = next_id;
    entry.label = str;
    entry.func = func;
    entry.interactable = true;

    //* Append the new option to the menu
    entries.emplace_back(entry);

    //* Append the next_id variable to prepare for the next interactable option
    next_id++;
}

//* Add a new Entry object to the menu
//! CAUTION: It is easy to mess up the settings and get difficult to debug results. Only use this if you know what you are doing!
void Menu::add_entry(Entry entry) {
    //* Append the entry to the inbuilt list of entries
    entries.emplace_back(entry);

    //* If the entry is interactable, then append the next_id to prepare for the next interactable entry
    if (entry.interactable) {
        next_id++;
    }
}

//* Adds a non-interactable line to the menu which displays <str>
void Menu::add_line(std::string str) {
    //* Create a new entry object and set its parameters to make the line non-interactable
    Entry entry;
    entry.label = str;
    entry.interactable = false;

    //* Append the entry to the list of menu entries
    entries.emplace_back(entry);
}

//* Add a blank line to the menu for padding.
void Menu::add_line() {
    Menu::add_line("");
}

//* Moves the selection up by <by> amount
void Menu::move_selection_up(int by) {
    if (!loop_menu_options) { //* If we are not looping through menu options, then use the simple clamp method to restrict the maximum and minimum values of the selection
        selection = std::clamp(selection - by, 0, next_id - 1);
    } else { //* Otherwise, if loop_menu_options is set, then use this more complex method to navigate the menu
        selection = ((selection - by) < 0) ? next_id - 1 : selection - by;
    }
}

//* Moves the selection up by one
void Menu::move_selection_up() {
    Menu::move_selection_up(1);
}

//* Moves the selection down by <by> amount
void Menu::move_selection_down(int by) {
    if (!loop_menu_options) { //* If we are not looping through menu options, then use the simple clamp method to restrict the maximum and minimum values of the selection
        selection = std::clamp(selection + by, 0, next_id - 1);
    } else { //* Otherwise, if loop_menu_options is set, then use this more complex method to navigate the menu
        selection = ((selection + by) > next_id - 1) ? 0 : selection + by;
    }
}

//* Moves the selection down by one
void Menu::move_selection_down() {
    Menu::move_selection_down(1);
}

//* Set the state of the loop_menu_options variable
void Menu::set_entry_loop(bool val) {
    loop_menu_options = val;
}

//* Render the menu using given render settings 
void Menu::render(MenuRenderSettings render_settings) {
    for (auto& e : entries) {
        //* Align the output to the alignment as specified by the alignment setting
        align(render_settings.alignment);

        //* Create a label to be displayed for this menu entry and pad it according to the selection size as specified in the settings
        std::string label;
        label.append(padded_str(e.label, render_settings.selection_size, ""));

        //* Set the normal foreground and background color
        fg_color(render_settings.fg_color_hex.c_str());
        bg_color(render_settings.bg_color_hex.c_str());

        if (selection == e.id) { //* If selection matches the choice ID of the option, then draw the entry using highlighted foreground and background settings
            //* Calculate the left and right padding required
            std::string pl = extend_string(" ", calculate_padding_left(label));
            std::string pr = extend_string(" ", calculate_padding_right(label));

            if (render_settings.alignment == ALIGN.LEFT) { //* If the menu is left-aligned
                //* Change the foreground and background color to highlighted colors because this entry is highlighted
                fg_color(render_settings.fg_color_highlighted_hex.c_str());
                bg_color(render_settings.bg_color_highlighted_hex.c_str());

                //* Output the label
                std::cout << label;

                //* Revert the colors to normal foreground and background colors
                fg_color(render_settings.fg_color_hex.c_str());
                bg_color(render_settings.bg_color_hex.c_str());

                //* Print the left padding, right padding, and theending string
                std::cout << pl << pr << render_settings.end;
            } else if (render_settings.alignment == ALIGN.CENTER) { //* If the menu is center-aligned
                //* Print out the left padding
                std::cout << pl;

                //* Change the foreground and background color to highlighted colors because this entry is highlighted
                fg_color(render_settings.fg_color_highlighted_hex.c_str());
                bg_color(render_settings.bg_color_highlighted_hex.c_str());

                //* Output the label
                std::cout << label;

                //* Revert the colors to normal foreground and background colors
                fg_color(render_settings.fg_color_hex.c_str());
                bg_color(render_settings.bg_color_hex.c_str());

                //* Print the right padding then print out the ending string
                std::cout << pr << render_settings.end;
            } else if (render_settings.alignment == ALIGN.RIGHT) { //* If the menu is right-aligned
                //* Print out the left and right padding
                std::cout << pl << pr;

                //* Change the foreground and background color to highlighted colors because this entry is highlighted
                fg_color(render_settings.fg_color_highlighted_hex.c_str());
                bg_color(render_settings.bg_color_highlighted_hex.c_str());

                //* Output the label
                std::cout << label;

                //* Revert the colors to normal foreground and background colors
                fg_color(render_settings.fg_color_hex.c_str());
                bg_color(render_settings.bg_color_hex.c_str());

                //* Print the ending string
                std::cout << render_settings.end;
            } else { //* Otherwise, the alignment is in an invalid state
                std::cout << "Invalid alignment state";
                exit(0);
            }
        } else { //* The entry is not selected. Use the normal method to padded-print this option
            print(label);
        }

        for (int i = 0; i < render_settings.line_padding; i++) { //* Print <line_padding> lines to act as a buffer between menu entries
            //* Print <line_padding_string> out between the menu entries as padding
            print(render_settings.line_padding_string);
        }
    }

    if (render_settings.fill_screen) { //* If fill_screen setting is set, then fill the screen with blank prints
        Location2D xy = wherexy();
        while (xy.y < t_size.height - 1) {
            xy = wherexy();
            print();
        }
    }
}

//* Renders menu with default settings
void Menu::render() {
    MenuRenderSettings render_settings;
    Menu::render(render_settings);
}

//* Handles the keyboard inputs
//* Typically used after rendering menu
void Menu::handle_input() {
    Key k = get_key();
    if (k == KEY_UP_ARROW) {
        move_selection_up();
    } else if (k == KEY_DOWN_ARROW) {
        move_selection_down();
    } else if (k == KEY_ENTER) {
        for (auto& e : entries) {
            if (e.id == selection) {
                e.func();
            }
        }
    } else if (k == KEY_Q) {
        exit_program();
    }
}
