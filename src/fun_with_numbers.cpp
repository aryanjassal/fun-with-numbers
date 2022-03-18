#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <math.h>

#define N_THREADS 8

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
        for (long long i = thread_id + 1; i <= (number / 2); i += thread_count) {
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
    //* Create a vector which stores all the factors returned by all the threads
    vector<long long> all_factors;
    //* Create a vector which stores a thread and its future value
    vector<future<vector<long long>>> ts(thread_count);
    //* The ID of each thread is passed to the function, which is used to properly delegate calculations to each thread equally.
    //! The ID of threads needs to be at least 1, otherwise it breaks the function to find factors
    int thread_id = 1;

    //* For each thread (t) in the vector of threads (ts)...
    for (auto& t : ts) {
        //* Launch a new async function (thread) and pass it the required parameters
        t = async(launch::async, get_prime_numbers, number, thread_id, thread_count);
        //* Increment the thread ID by one.
        thread_id++;
    }

    //* For each thread (t) in the vector of threads (ts)...
    for (auto& t : ts) {
        //* Wait for the thread to return a value. The program will pause here until all the threads have returned something.
        vector<long long> thread_factors = t.get();
        /*
        * Insert the numbers from the start of the resultant vector to the end of the resultant vector into the vector which 
        * contains all the factors. Append the factors at the end of the vector.
        */ 
        all_factors.insert(all_factors.end(), thread_factors.begin(), thread_factors.end());
    }
    
    //* Manually add in 1 and the original number as factors as optimisations made to the algorithm do not check for 1 or the number itself
    all_factors.insert(all_factors.begin(), 1);
    all_factors.insert(all_factors.end(), number);
    //* Sort all the factors in increasing order
    sort(all_factors.begin(), all_factors.end());

    //* Return all factors
    return all_factors;
}

void check_number_features() {
    //* Clear the screen to notify the user that we are in a different section of the program
    system("clear");

    //* Request a whole number from the user and convert it into a long long integer.
    cout << "Please enter a whole number that will be checked over: ";
    string num_str;
    getline(cin, num_str);
    long long num = stoll(num_str);

    //* Display the features of the given number
    cout << "\n"
        << "The features of " << num << " are...";
    
    //* Define variables to be used later on
    //TODO: Try making the variable definition and initialisation in the same line.
    string positive_negative, prime_not;
    string even_odd;
    positive_negative = (num > 0) ? "Positive" : (num < 0) ? "Negative" : "Zero";
    even_odd = (num % 2 == 0) ? "Even" : "Odd";

    //* Print if the number is positive, negative, or zero
    cout << "\n  " << positive_negative;

    //* Print if the number is even or odd
    cout << "\n  " << even_odd;

    //* Print the factors of the number using multithreading
    cout << "\n  Factors are ";

    //* Vectors are dynamic lists of values. The function find_prime_factors returns a vector of factors.
    vector<long long> factors = find_prime_factors(num, N_THREADS);
    //* This for loop prints each factor and appends space just behind it.
    for (auto i : factors) {
        cout << " " << i;
    }

    //* If the number of factors are 2 (1 and the number itself), then the number is a prime number.
    prime_not = (factors.size() == 2) ? "Is a prime number" : "Is not a prime number";
    cout << "\n"
        << "  " << prime_not
        << "\n";

    //* Pause and wait until a key is pressed
    cin.ignore();

    //* Return back to the main menu loop
    return;
}

void plot_numbers() {
    return;
}

void check_overall_stats() {
    //* Display the statistics of overall usage
    cout << "Here are your statistics of overall use:"
        << "\n Numbers entered: " << numbers_entered
        << "\n Total of numbers: " << total_of_numbers
        << "\n Average of numbers: " << (unsigned long long)(total_of_numbers / numbers_entered)
        << "\n Smallest number entered: " << smallest_number_entered
        << "\n Largest number entered: " << largest_number_entered
        << "\n Coordinates plotted: " << coordinates_plotted
        << "\n";

    //* Pause and wait until a key is pressed
    cin.ignore();

    //* Return back to the main menu loop
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
            //* Actually exit
            return 0;
        }
    }
}
