#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int CountAndAddNewDogs(const vector<string>& new_dogs, const map<string, int>& max_amount,
                       map<string, int>& shelter) {
    return count_if(begin(new_dogs), end(new_dogs), [&](const string& dog){
        if (shelter[dog] < max_amount.at(dog)) {
            ++shelter[dog];
            return true;
        } 
        return false;
    });
}

int main() {
    map<string, int> shelter {
        {"shepard"s, 1},
        {"corgie"s, 3},
    };

    map<string, int> max_amount {
        {"shepard"s, 2},
        {"corgie"s, 3},
        {"shiba inu"s, 1},
    };

    cout << CountAndAddNewDogs({"shepard"s, "shiba inu"s, "shiba inu"s, "corgie"s}, max_amount, shelter) << endl;
}