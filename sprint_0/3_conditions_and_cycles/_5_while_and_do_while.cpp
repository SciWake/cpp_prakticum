#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    // Числа a и b должны быть натуральными
    while (b != 0) {
        int c = b;
        b = a % b;
        a = c; 
    }
    cout << a << endl;
}