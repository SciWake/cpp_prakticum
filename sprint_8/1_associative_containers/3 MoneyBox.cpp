#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class MoneyBox {
public:
    explicit MoneyBox(vector<int64_t> nominals)
        : nominals_(move(nominals))
        , counts_(nominals_.size()) {
    }

    const vector<int>& GetCounts() const {
        return counts_;
    }

    void PushCoin(int64_t value) {
        auto it = lower_bound(nominals_.begin(), nominals_.end(), value);
        ++counts_[distance(nominals_.begin(), it)];
    }

    void PrintCoins(ostream& out) const {
        for (size_t i = 0; i < nominals_.size(); ++i) {
            if (counts_[i]) {
                out << nominals_[i] << ": " << counts_[i] << endl;
            }
        }
    }

private:
    const vector<int64_t> nominals_;
    vector<int> counts_;
};

ostream& operator<<(ostream& out, const MoneyBox& cash) {
    cash.PrintCoins(out);
    return out;
}


int TestOne() {
    MoneyBox cash({1, 500, 10000});
    cash.PushCoin(500);
    cash.PushCoin(500);
    cash.PushCoin(10000);
    assert((cash.GetCounts() == vector<int>{0,2,1}));
    cout << cash << endl;
}


int main() {
    TestOne();

    MoneyBox cash({10, 50, 100, 200, 500, 1000, 2000, 5000});

    int times;
    cout << "Enter number of coins you have:"s << endl;
    cin >> times;

    cout << "Enter all nominals:"s << endl;
    for (int i = 0; i < times; ++i) {
        int64_t value;
        cin >> value;
        cash.PushCoin(value);
    }

    cout << cash << endl;
}