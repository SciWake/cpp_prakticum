#include <iostream>

using namespace std;

bool IsPowOfTwo(int num) {
    if (0 == num) {
        return false;
    }
    if (1 == num) {
        return true;
    }
    if (0 == num % 2) {
        return IsPowOfTwo(num / 2);
    }
    return false;
}

int main() {
    int result = IsPowOfTwo(1024);
    cout << result << endl;
    return 0;
}
