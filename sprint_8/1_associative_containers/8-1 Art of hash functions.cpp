#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;


template <typename Hash>
int FindCollisions(const Hash& hasher, istream& text) {
    unordered_set<string> seen_words;
    unordered_set<size_t> seen_hashes;

    int cur_collisions = 0;

    string word;
    while (text >> word) {
        if (seen_words.count(word) > 0) {
            continue;
        }
        seen_words.insert(word);

        size_t hash = hasher(word);
        if (seen_hashes.count(hash) > 0) {
            ++cur_collisions;
            continue;
        }

        seen_hashes.insert(hash);
    }

    return cur_collisions;
}

// template <typename Hash>
// int FindCollisions(const Hash& hasher, istream& text) {
//     unordered_map<size_t, unordered_set<string>> hash_words;
    
//     string word;
//     int collision_count = 0;
    
//     while(text >> word) {
//         size_t word_hash = hasher(word);
//         //when hash is repeated, check if the word was already encountered
//         // - gives a smaller unordered_set to search in
//         if(hash_words.count(word_hash) > 0 && hash_words.at(word_hash).count(word) == 0) {
//             //same hash different word
//             ++collision_count;
//         }
//         //insert new words
//         hash_words[word_hash].insert(word);
//     }
//     return collision_count;
// }

// Это плохой хешер. Его можно использовать для тестирования.
// Подумайте, в чём его недостаток
struct HasherDummy {
    size_t operator() (const string& str) const {
        size_t res = 0;
        for (char c : str) {
            res += static_cast<size_t>(c);
        }
        return res;
    }
};

int main() {
    hash<string> str_hasher;
    int collisions = FindCollisions(str_hasher, cin);
    cout << "Found collisions: "s << collisions << endl;
}