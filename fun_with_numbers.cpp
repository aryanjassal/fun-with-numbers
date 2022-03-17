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

int main() {
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
