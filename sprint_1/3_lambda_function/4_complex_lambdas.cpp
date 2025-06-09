#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> ReadNumbers() {
    int count;
    cin >> count;

    vector<int> numbers;
    for (int i = 0; i < count; ++i) {
        int number;
        cin >> number;
        numbers.push_back(number);
    }

    return numbers;
}

void PrintNumbers(const vector<int>& numbers) {
    for (auto number : numbers) {
        cout << number << " "s;
    }
}

int main() {
    vector<int> numbers = ReadNumbers();
    sort(numbers.begin(), numbers.end(), [](int n1, int n2) {
        const bool n1_is_even = n1 % 2 == 0;
        const bool n2_is_even = n2 % 2 == 0;

        return (n1_is_even && n2_is_even) ? n1 < n2 :
            (n1_is_even) ? true :
            (n2_is_even) ? false :
            n1 > n2;
    });

    PrintNumbers(numbers);
}