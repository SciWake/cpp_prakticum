#include <iostream>
#include <string>

using namespace std;

void hanoi(int n, int i, int k) {
    if (n == 1) {
        cout << "Move "s << n << " from pin "s << i << " to "s << k << endl;
    } else {
        int tmp = 6 - i - k;
        hanoi(n-1, i, tmp);
        cout << "Move "s << n << " from pin "s << i << " to "s << k << endl;
        hanoi(n-1, tmp, k);
    }
}
// Stack:
// [1]hanoi(3, 1, 2)
//     [8]Move 3 from pin 1 to 2
//     [2]hanoi(2, 1, 3)
//         [5]Move 2 from pin 1 to 3
//         [3]hanoi(1, 1, 2)
//         [4]Move 1 from pin 1 to 2
//         [6]hanoi(1, 2, 3)
//         [7]Move 1 from pin 2 to 3
//     [9]hanoi(2, 3, 2)
//         [12]Move 2 from pin 3 to 2
//         [10]hanoi(1, 3, 1)
//         [11]Move 1 from pin 3 to 1
//         [13]hanoi(1, 1, 2)
//         [14]Move 1 from pin 1 to 2


int main() {
    hanoi(3, 1, 2);
}