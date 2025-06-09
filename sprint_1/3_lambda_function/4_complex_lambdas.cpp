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

    sort(numbers.begin(), numbers.end(),
         [] (int n1, int n2) {
             const bool n1_is_even = n1 % 2 == 0;
             const bool n2_is_even = n2 % 2 == 0;
             if (n1_is_even && n2_is_even) {  // n1 и n2 - чётные
                 // Чётные числа сортируются по возрастанию
                 return n1 < n2;
             }
             if (n1_is_even) {  // n1 - чётное, n2 - нечётное
                 return true;   // чётные числа должны предшествовать нечётным
             }
             if (n2_is_even) {  // n1 - нечётное, n2 - чётное
                 return false;  // нечётные числа следуют за чётными
             }
             // n1 и n2 - нечётные
             return n1 > n2; // Нечётные числа сортируются по убыванию
         });

    PrintNumbers(numbers);
}