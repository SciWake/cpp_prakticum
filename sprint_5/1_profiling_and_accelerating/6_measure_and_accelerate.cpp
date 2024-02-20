#include "log_duration.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

vector<int> ReverseVector(const vector<int>& source_vector) {
    vector<int> res;

    for (int i : source_vector) {
        res.insert(res.begin(), i);
    }

    return res;
}

vector<int> ReverseVector2(const vector<int>& source_vector) {
    vector<int> res;

    // будем проходить source_vector задом наперёд
    // с помощью обратного итератора
    for (auto iterator = source_vector.rbegin(); iterator != source_vector.rend(); ++iterator) {
        res.push_back(*iterator);
    }

    return res;
}

vector<int> ReverseVector3(const vector<int>& source_vector) {
    return {source_vector.rbegin(), source_vector.rend()};
}

vector<int> ReverseVector4(const vector<int>& source_vector) {
    vector<int> res(source_vector.size());

    int i = static_cast<int>(res.size()) - 1;
    for (auto it = source_vector.begin(); it != source_vector.end(); ++it) {
        res[i--] = *it;
    }

    return res;
}


void Operate() {
    vector<int> rand_vector;
    int n;

    cin >> n;
    rand_vector.reserve(n);

    for (int i = 0; i < n; ++i) {
        rand_vector.push_back(rand());
    }

    {
        vector<int> reversed_bits;
        LOG_DURATION("Good"s);
        reversed_bits = ReverseVector2(rand_vector);
    }

    // код измерения тут
    if (n <= 100000) {
        vector<int> reversed_bits;
        LOG_DURATION("Naive"s);
        reversed_bits = ReverseVector(rand_vector);
    } else {
        {
            vector<int> reversed_bits;
            LOG_DURATION("Best"s);
            reversed_bits = ReverseVector3(rand_vector);
        }
        {
            vector<int> reversed_bits;
            LOG_DURATION("Your"s);
            reversed_bits = ReverseVector4(rand_vector);
        }
    }
}

int main() {
    Operate();
    return 0;
}