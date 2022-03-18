#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <math.h>

using namespace std;

unsigned long long total_of_numbers;
long long smallest_number_entered, largest_number_entered;
int numbers_entered, coordinates_plotted;

vector<long long> get_prime_numbers(long long number, int thread_id, int thread_count) {
    //* Create a vector of factors returned from this thread
    vector<long long> factors;

    /*
    * If a number is even, then the factors can be either even or odd. For example, the factors of 14 are 1, 7, 14.
    * An even number has both odd and even factors. However, an odd number will always have odd factors. For example, 
    * the factors of 81 are 1, 3, 9, 27, 81. Notice how none of the factors are even. That is how every even number 
    * can be skipped to check the factors of a given number if the number is odd.
    */

    //* If number is even, use the slower loop
    if (number % 2 == 0) {
        for (long long i = thread_id + 2; i <= (number / 2); i += thread_count) {
            if (number % i == 0) {
                factors.push_back(i);
            }
        }
    //* Otherwise (if the number is odd), use the faster loop
    } else {
        /*
        * This loop uses the thread ID to get the corresponding odd number of the index. For example, a thread ID of
        * 5 gives us 9 as a result. If you count 1, then 9 is the fifth odd number (1 -> 3 -> 5 -> 7 -> 9). If it is
        * put forth as is, the repeated numbers will be observed. To get rid of the duplicates, it is required to 
        * multiply the offset by 2 to ignore the duplicates.
        */
        for (long long i = thread_id + 2 + (thread_id - 1); i <= (number / 2); i += (thread_count) * 2) {
            if (number % i == 0) {
                factors.push_back(i);
            }
        }
    }
    return factors;
}

vector<long long> find_prime_factors(long long number, int thread_count = 1) {
    vector<long long> all_factors;
    vector<future<vector<long long>>> ts(thread_count);
    int thread_id = 1;

    for (auto& t : ts) {
        t = async(launch::async, get_prime_numbers, number, thread_id, thread_count);
        thread_id++;
    }

    for (auto& t : ts) {
        vector<long long> thread_factors = t.get();
        all_factors.insert(all_factors.end(), thread_factors.begin(), thread_factors.end());
    }

    all_factors.insert(all_factors.begin(), 1);
    all_factors.insert(all_factors.end(), number);
    sort(all_factors.begin(), all_factors.end());

    return all_factors;
}

void check_number_features() {
    system("clear");
    cout << "Please enter a whole number that will be checked over: ";
    string num_str;
    getline(cin, num_str);
    long long num = stoll(num_str);

    cout << "\n"
        << "The features of " << num << " are...";
    
    string positive_negative, prime_not;
    string even_odd;
    positive_negative = (num > 0) ? "Positive" : (num < 0) ? "Negative" : "Zero";
    even_odd = (num % 2 == 0) ? "Even" : "Odd";

    cout << "\n  " << positive_negative;
    cout << "\n  " << even_odd;

    cout << "\n  Factors are ";
    vector<long long> factors = find_prime_factors(num, 8);
    for (auto i : factors) {
        cout << " " << i;
    }

    prime_not = (factors.size() == 2) ? "Is a prime number" : "Is not a prime number";
    cout << "\n"
        << "  " << prime_not
        << "\n";

    cin.ignore();
    return;
}

void plot_numbers() {
    return;
}

void check_overall_stats() {
    cout << "Here are your statistics of overall use:"
        << "\n Numbers entered: " << numbers_entered
        << "\n Total of numbers: " << total_of_numbers
        << "\n Average of numbers: " << (unsigned long long)(total_of_numbers / numbers_entered)
        << "\n Smallest number entered: " << smallest_number_entered
        << "\n Largest number entered: " << largest_number_entered
        << "\n Coordinates plotted: " << coordinates_plotted
        << "\n";

    cin.ignore();
    return;
}

char main_menu() {
    /*
    * This is the main menu. Whenever this method is called, the console is cleared and the options are shown.
    * This function returns the input if it only contained one character, otherwise the main menu function is
    * called again until a valid input is entered. The output is the input character in lower case.
    */

   //* Clear the console screen
    system("clear");

    //* Actually display the main menu using multiline cout method.
    cout << "Welcome to Fun With Numbers\n"
        << "Choose from the menu below:\n"
        << "  (A) Check number features\n"
        << "  (B) Plot numbers\n"
        << "  (C) Check overall stats\n"
        << "\n"
        << "  (X) Save and exit\n"
        << "Choice: ";

    //* Create a temporary variable which stores the user input as a string.
    string num_str;
    getline(cin, num_str);

    //* If the number of characters are more than one, then loop back into the main menu.
    if (num_str.length() > 1) {
        main_menu();
    }
    //* Otherwise, return the character in lower case.
    return tolower((char)num_str[0]);
}

int main() {
    //* for(;;) is basically a while(true) loop written using less characters.
    for(;;) {
        //* Get the user choice from the main_menu function.
        char choice = main_menu();

        //* This code handles various cases of user input
        if (choice == 'a') {
            check_number_features();
        } else if (choice == 'b') {
            plot_numbers();
        } else if (choice == 'c') {
            check_overall_stats();
        } else if (choice == 'x') {
            //* Shut down the audio playback library
            ao_shutdown();

            //* Actually exit
            return 0;
        }
    }
}
