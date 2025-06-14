#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}

/* VERSION 1*/
// vector<string> SplitIntoWords(const string& text) {
//     vector<string> words;
//     string word;
//     for (const char c : text) {
//         if (c == ' ') {
//             if (!word.empty()) {
//                 words.push_back(word);
//                 word.clear();
//             }
//         } else {
//             word += c;
//         }
//     }
//     if (!word.empty()) {
//         words.push_back(word);
//     }

//     return words;
// }

bool ContainsWord(const string& query, const string& buzzword) {
    size_t pos = 0;
    while ((pos = query.find(buzzword, pos)) != string::npos) {
        bool left_ok = (pos == 0 || query[pos - 1] == ' ');
        bool right_ok = (pos + buzzword.size() == query.size() || query[pos + buzzword.size()] == ' ');
        if (left_ok && right_ok) {
            return true;
        }
        pos += buzzword.size();
    }
    return false;
}

int main() {
    const int queryCount = ReadLineWithNumber();

    vector<string> queries(queryCount);
    for (string& query : queries) {
        query = ReadLine();
    }
    const string buzzword = ReadLine();

    /* VERSION 1*/
    // cout << count_if(queries.begin(), queries.end(), [buzzword](const string& query) {
    //     for (const string& word : SplitIntoWords(query)) {
    //         if (word == buzzword) return true;
    //     }
    //     return false;

    // });

    int result = count_if(queries.begin(), queries.end(), 
        [&buzzword](const string& query) {
            return ContainsWord(query, buzzword);
        });
    cout << result << endl;
}