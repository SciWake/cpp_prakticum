// файл wordstat.cpp

#include "log_duration.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

vector<pair<string, int>> GetSortedWordCounts(vector<string> words) {
    map<string, int> counts_map;

    {
        LOG_DURATION("Filling"s);

        for (auto& word : words) {
            ++counts_map[move(word)];
        }
    }

    {
        LOG_DURATION("Moving & sorting"s);

        vector<pair<string, int>> counts_vector(move_iterator(counts_map.begin()), move_iterator(counts_map.end()));
        sort(counts_vector.begin(), counts_vector.end(), [](const auto& l, const auto& r) {
            return l.second > r.second;
        });

        return counts_vector;
    }
}

int main() {
    vector<string> words;
    string word;

    while (cin >> word) {
        words.push_back(word);
    }

    auto counts_vector = GetSortedWordCounts(move(words));

    cout << "Слово - Количество упоминаний в тексте"s << endl;
    // выводим первые 10 слов
    for (auto [iter, i] = tuple(counts_vector.begin(), 0); i < 10 && iter != counts_vector.end(); ++i, ++iter) {
        cout << iter->first << " - "s << iter->second << endl;
    }
}
/* Output:
Filling: 59 ms
Moving & sorting: 3 ms
Слово - Количество упоминаний в тексте
and - 8877
that - 5832
the - 5623
of - 5351
to - 4002
he - 3718
in - 3544
his - 3103
for - 3027
a - 3025 */

#include <unordered_map>

vector<pair<string, int>> GetSortedWordCounts(vector<string> words) {
    unordered_map<string, int> counts_map;

    {
        LOG_DURATION("Filling"s);

        for (auto& word : words) {
            ++counts_map[move(word)];
        }
    }

    cout << "Содержимое counts_map:"s << endl;
    for (auto [iter, i] = tuple(counts_map.begin(), 0); i < 10 && iter != counts_map.end(); ++i, ++iter) {
        cout << iter->first << " - "s << iter->second << endl;
    }

    {
        LOG_DURATION("Moving & sorting"s);

        vector<pair<string, int>> counts_vector(move_iterator(counts_map.begin()), move_iterator(counts_map.end()));
        sort(counts_vector.begin(), counts_vector.end(), [](const auto& l, const auto& r) {
            return l.second > r.second;
        });

        return counts_vector;
    }
}

int main() {
    vector<string> words;
    string word;

    while (cin >> word) {
        words.push_back(word);
    }

    auto counts_vector = GetSortedWordCounts(move(words));

    cout << "Слово - Количество упоминаний в тексте"s << endl;
    // выводим первые 10 слов
    for (auto [iter, i] = tuple(counts_vector.begin(), 0); i < 10 && iter != counts_vector.end(); ++i, ++iter) {
        cout << iter->first << " - "s << iter->second << endl;
    }
}

/* Output:
Filling: 16 ms
Содержимое counts_map:
y-pilt - 1
sitthen - 1
ropes - 1
sisours - 2
assise - 2
enquered - 1
iustices - 2
ferd - 1
cheeke-boon - 1
iustise - 3
Moving & sorting: 3 ms
...
*/