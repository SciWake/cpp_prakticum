#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main() {
    // считайте входные данные и сформируйте вывод программы
    // ...

    size_t count_words = 0;
    cin >> count_words;
    vector<string> words(count_words);

    for (auto& word: words) {
        cin >> word; 
    }

    sort(begin(words), end(words), [](const string& l, const string& r) {
            return lexicographical_compare(
                begin(l), end(l),
                begin(r), end(r),
                
                [](char cl, char cr) { return tolower(cl) < tolower(cr); }
            );
        }
    );

    for (const auto& word: words) {
        cout << word << " "s; 
    }
}