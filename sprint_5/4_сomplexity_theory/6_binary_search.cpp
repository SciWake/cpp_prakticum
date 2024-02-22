#include <iostream>

using namespace std;

template <typename F>
int FindFloor(int n, F drop) {
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (drop(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}


int main() {
    int n,t;
    cout << "Enter n and target floor number: "s << endl;
    cin >> n >> t;

    int count = 0;
    int found = FindFloor(n, [t, &count](int f) {
        ++count;
        return f >= t;
    });

    cout << "Found floor "s << found << " after "s << count << " drops"s;

    return 0;
}