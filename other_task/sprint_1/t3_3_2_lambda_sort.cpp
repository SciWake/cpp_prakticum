#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


size_t ComputeWeight(const string& word) {
    size_t weight = word.size();
    for (const char ch : word) {
        int lower = tolower(ch);
        if (lower == 'a') weight += 5;
        else if (lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') weight += 2;
    }
    return weight;
}

int main() {
    size_t n;
    cin >> n;

    vector<string> words(n);
    for (auto& word : words) {
        cin >> word;
    }

    sort(begin(words), end(words), [](const string& l, const string& r) {
        auto w_l = ComputeWeight(l);
        auto w_r = ComputeWeight(r);

        if (w_l != w_r) return w_l > w_r;

        return lexicographical_compare(
            begin(l), end(l), begin(r), end(r),
            [](char cl, char cr) {
                return tolower(cl) < tolower(cr);
            }
        );
    });

    cout << "Output: ";
    for (const auto& word : words) {
        cout << word << " ";
    }

    cout << endl;
}
// 7
// banana
// Apple
// abacus
// kiwi
// Orange
// cab
// Avocado
// Output: Avocado banana abacus Orange Apple cab kiwi 