#include <iostream>

using namespace std;

// Функция для рекурсивного вычисления факториала:
// 0! = 1
// n! = n*(n-1)!
int Factorial(int n) {
    cout << "  Factorial("s << n << "): &n="s << &n << endl;
    return n > 0 ? n * Factorial(n - 1) : 1;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        cout << "=== Calculating factorial of "s << i << " ==="s << endl;
        int f = Factorial(i);
        cout << "Result is: "s << f << endl << endl;
    }
}

/*
=== Calculating factorial of 0 ===
  Factorial(0): &n=0x7fffffffdbac
Result is: 1

=== Calculating factorial of 1 ===
  Factorial(1): &n=0x7fffffffdbac
  Factorial(0): &n=0x7fffffffdb2c
Result is: 1

=== Calculating factorial of 2 ===
  Factorial(2): &n=0x7fffffffdbac
  Factorial(1): &n=0x7fffffffdb2c
  Factorial(0): &n=0x7fffffffdaac
Result is: 2

=== Calculating factorial of 3 ===
  Factorial(3): &n=0x7fffffffdbac
  Factorial(2): &n=0x7fffffffdb2c
  Factorial(1): &n=0x7fffffffdaac
  Factorial(0): &n=0x7fffffffda2c
Result is: 6
*/