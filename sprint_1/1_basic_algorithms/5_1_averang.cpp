#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

double Average(const vector<int>& xs) {
    if (xs.empty()) {
        return 0;
    }
    return accumulate(xs.begin(), xs.end(), 0.0) / xs.size();
}

int main() {
    cout << Average({}) << endl;        // Результат: 0.
    cout << Average({2, 3}) << endl;    // Результат: 2.5.
    cout << Average({7, 2, 6}) << endl; // Результат: 5.
}