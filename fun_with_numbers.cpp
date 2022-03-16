#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>

using namespace std;

vector<long long> factors;
mutex m;

void get_prime_numbers(long long n, int thread_id, int offset) {
    for (long long i = thread_id; i <= n; i += offset) {
        if (n % i == 0) {
            // cout << " " << i << " ";
            m.lock();
            factors.push_back(i);
            m.unlock();
        }
    }
    return;
}

void find_prime_factors(long long number, int thread_count = 1) {
    vector<thread> ts;

    for (int i = 1; i <= thread_count; i++) {
        ts.emplace_back(get_prime_numbers, number, i, thread_count);
    }

    for (auto& thread : ts) {
        thread.join();
    }
    return;
}

int main() {
    system("clear");
    cout << "Enter a number to be checked over: ";
    string num_str;
    getline(cin, num_str);
    long long num = stoll(num_str);

    find_prime_factors(num, 6);
    sort(factors.begin(), factors.end());
    for (auto i : factors) {
        cout << i << " ";
    }
    cout << "\n";
    return 0;
}
