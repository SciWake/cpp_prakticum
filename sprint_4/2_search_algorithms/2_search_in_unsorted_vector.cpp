#include <algorithm>
#include <iostream>
#include <string>

using namespace std;


void PrintSpacesPositions(string& str) {
    for (auto it = find(str.begin(), str.end(), ' '); 
         it != str.end(); it = find(next(it), 
         str.end(), ' ')) {
        cout << distance(str.begin(), it) << endl;
    }
}

int main() {
    string str = "He said: one and one and one is three"s;
    PrintSpacesPositions(str);
    return 0;
}