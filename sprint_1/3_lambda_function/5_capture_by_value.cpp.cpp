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

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

int main() {
    const int queryCount = ReadLineWithNumber();

    vector<string> queries(queryCount);
    for (string& query : queries) {
        query = ReadLine();
    }
    const string buzzword = ReadLine();

    cout << count_if(queries.begin(), queries.end(), [buzzword](const string& query) {
        const vector<string> query_words = SplitIntoWords(query);
        return count(query_words.begin(), query_words.end(), buzzword) != 0;
    });
    cout << endl;
}