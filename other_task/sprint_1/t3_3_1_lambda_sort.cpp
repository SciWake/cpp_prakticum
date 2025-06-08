#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функция для подсчёта количества букв 'a'/'A' в слове
auto count_a(const string& word) {
    return count_if(begin(word), end(word), [](char c) {
        return tolower(c) == 'a';
    });
}

int main() {
    size_t n;
    cin >> n;

    vector<string> words(n);
    for (auto& word : words) {
        cin >> word;
    }

    sort(begin(words), end(words), [](const string& l, const string& r) {
        auto count_l = count_a(l);
        auto count_r = count_a(r);

        if (count_l != count_r)
            return count_l > count_r;
        else
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

// 10
// banana
// Apple
// avalanche
// Cab
// Aardvark
// boat
// Alpha
// area
// arcade
// abacus
// Output: Aardvark avalanche banana abacus Alpha arcade area Apple boat Cab 