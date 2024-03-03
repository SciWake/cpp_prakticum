#include "log_duration.h"

#include <algorithm>
#include <deque>
#include <vector>
#include <random>

using namespace std;


int main() {
    vector<int> num_vec;
    deque<int> num_deq;
    int generate_number;

    // Генратор случайных чисел
    static mt19937 engine;
    uniform_int_distribution<int> d(0, 100);
    for (int i = 0; i < 1000000; ++i) {
        generate_number = d(engine);
        num_vec.push_back(generate_number);
        num_deq.push_back(generate_number);
    }

    {
        LOG_DURATION("vector sort");
        sort(num_vec.begin(), num_vec.end());
    }
    {
        LOG_DURATION("deque sort");
        sort(num_deq.begin(), num_deq.end());
    }
    
}