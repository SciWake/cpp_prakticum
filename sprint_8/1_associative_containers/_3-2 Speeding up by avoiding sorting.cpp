#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class MoneyBox {
public:
    void PushCoin(int value) {
        assert(value >= 0 && value <= 5000);
        ++counts_[value];
    }

    void PrintCoins(ostream& out) const {
        for (int i = 0; i < counts_.size(); ++i) {
            if (counts_[i] > 0) {
                out << i << ": "s << counts_[i] << endl;
            }
        }
    }

private:
    // создаём вектор размера 5001 для того, чтобы последний
    // индекс соответствовал максимальному номиналу 5000
    vector<int> counts_ = vector<int>(5001);
};

ostream& operator<<(ostream& out, const MoneyBox& cash) {
    cash.PrintCoins(out);
    return out;
}

int main() {
    MoneyBox cash;

    int value;
    while (cin >> value) {
        cash.PushCoin(value);
    }

    cout << cash << endl;
}

/*
Input:
50 200 2000 500 50 500 2000 2000 100 10 50 50 50 200 50 200 
200 2000 200 500 5000 500 2000 50 500 2000 1000 500 2000 5000 
5000 2000 200 100 1000 10 200 200 200 2000 5000 200 100 1000 
50 10 1000 5000 1000 500 200 500 2000 1000 1000 200 200 1000 
50 100 500 200 2000 100 10 100 10 2000 10 10 2000 1000 100 
50 100 2000 2000 1000 50 500 1000 5000 500 100 500 10 2000 
10 200 500 10 5000 100 200 50 100 2000 100 50 1000

Output:
10: 10
50: 13
100: 12
200: 16
500: 13
1000: 12
2000: 17
5000: 7
*/