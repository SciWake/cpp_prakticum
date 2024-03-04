// файл wordstat.cpp

#include <iostream>
#include <map>
#include <string>
#include <tuple>

using namespace std;

int main1() {
    string word;
    map<string, int> counts_map;

    while (cin >> word) {
        ++counts_map[move(word)];
    }

    cout << "Слово - Количество упоминаний в тексте"s << endl;
    // выводим первые 10 слов
    for (auto [iter, i] = tuple(counts_map.begin(), 0); i < 10 && iter != counts_map.end(); ++i, ++iter) {
        cout << iter->first << " - "s << iter->second << endl;
    }
}
/*
Для примера возьмём книгу Джефри Чосера «Кентерберийские рассказы». 
Мы сохранили её в файл canterbury.txt. 
При запуске перенаправим содержимое этого файла в cin программы, 
используя в командной строке символ <:

> g++ wordstat.cpp -o wordstat -std=c++17 -O3
> ./wordstat < canterbury.txt
Слово - Количество упоминаний в тексте
a - 3025
aaron - 1
abak - 2
abasshed - 1
abate - 1
abated - 1
abateth - 1
abaundone - 2
abaundoneth - 2
abaysed - 1

*/

// файл wordstat.cpp

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

vector<pair<string, int>> GetSortedWordCounts(vector<string>&& words) {
    map<string, int> counts_map;

    for (auto& word : words) {
        ++counts_map[move(word)];
    }

    vector<pair<string, int>> counts_vector(move_iterator(counts_map.begin()), move_iterator(counts_map.end()));
    sort(counts_vector.begin(), counts_vector.end(), [](const auto& l, const auto& r) {
        return l.second > r.second;
    });

    return counts_vector;
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
    for (auto [iter, i] = tuple(counts_vector.begin(), 0); i < 100 && iter != counts_vector.end(); ++i, ++iter) {
        cout << iter->first << " - "s << iter->second << endl;
    }
}