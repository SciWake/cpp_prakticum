#include <iostream>

using namespace std;

int Fibonacci(int i) {
    if (0 == i) {
        return 0;
    }
    if (1 == i) {
        return 1;
    }
    return Fibonacci(i - 1) + Fibonacci(i - 2);
}

int main() {
    cout << Fibonacci(6) << endl;
    return 0;
}
