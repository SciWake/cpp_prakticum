#include <set>
#include <string>
#include <numeric>

using namespace std;


string FoldWithMinus(string left, string right) {
    return left + " -"s + right;
}


string AddStopWords(const string& query, const set<string>& stop_words) {
    return std::accumulate(stop_words.begin(), stop_words.end(), query, FoldWithMinus);
}