#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функция для подсчёта количества букв 'a'/'A' в слове
auto ComputeWeight(const string& word) {
    size_t count_a = 0, count_vowel = 0;
    
    for (const auto& ch: word) {
        int lower = tolower(ch);
        if (lower == 'a') {
            count_a++;
        }
        if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
            count_vowel++;
        }
    }
    return 3 * count_a + 2 * count_vowel + word.size();
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