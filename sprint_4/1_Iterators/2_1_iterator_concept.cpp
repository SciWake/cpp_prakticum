#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    auto result = find_if(langs.begin(), langs.end(), [](const string &lang) {
        return lang[0] == 'C';
    });
    cout << *result << endl;
    return 0;
}
