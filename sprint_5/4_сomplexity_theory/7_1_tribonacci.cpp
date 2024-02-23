#include <cstdint>
#include <iostream>

using namespace std;

// упростите эту экспоненциальную функцию,
// реализовав линейный алгоритм
int64_t T(int i) {
    if (i == 0) {
        return 0;
    }

    int64_t a = 0, b = 0, c = 1;

    for (int t = 1; t < i; ++t) {
        int64_t next = a + b + c;
        a = b;
        b = c;
        c = next;
    }

    return b;
}

int main() {
    int i;

    while (true) {
        cout << "Enter index: "s;
        if (!(cin >> i)) {
            break;
        }

        cout << "Ti = "s << T(i) << endl;
    }
}