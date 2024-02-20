#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


size_t GetFileSize(string file) {
    ifstream inp(file);
    if (!inp) {
        return string::npos;
    }

    inp.seekg(0, ios::end);

    size_t res = static_cast<size_t>(inp.tellg());

    return res;
}

int main() {
    ofstream("test.txt"s) << "123456789"s;
    assert(GetFileSize("test.txt"s) == 9);

    ofstream test2("test2.txt"s);
    test2.seekp(1000);
    test2 << "abc"s;
    test2.flush();

    assert(GetFileSize("test2.txt"s) == 1003);
    assert(GetFileSize("missing file name"s) == string::npos);
}