#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

using namespace std;

vector<long long> get_prime_numbers(long long number, int thread_id, int thread_count) {
    vector<long long> factors;
    for (long long i = thread_id + 1; i <= (number / 2); i += thread_count) {
        if (number % i == 0) {
            factors.push_back(i);
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
    return;
}

char main_menu() {
    system("clear");
    cout << "Welcome to Fun With Numbers\n"
        << "Choose from the menu below:\n"
        << "  (A) Check number features\n"
        << "  (B) Plot numbers\n"
        << "  (C) Check overall stats\n"
        << "\n"
        << "  (X) Save and exit\n"
        << "Choice: ";
    string num_str;
    getline(cin, num_str);
    
    return tolower((char)num_str[0]);
}

int main() {
    for(;;) {
        char choice = main_menu();
        if (choice == 'a') {
            check_number_features();
        } else if (choice == 'b') {
            plot_numbers();
        } else if (choice == 'c') {
            check_overall_stats();
        } else if (choice == 'x') {
            return 0;
        }
    }

    system("clear");
    cout << "Enter a number to be checked over: ";
    string num_str;
    getline(cin, num_str);
    long long num = stoll(num_str);

    vector<long long> factors = find_prime_factors(num, 8);
    for (auto i : factors) {
        cout << i << " ";
    }
    cout << "\n";
    return 0;
}
