#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, const char** argv) {
    // открываем файл, указанный в первом аргументе командной строки
    ifstream input(argv[1]);

    while (input) {
        int times;
        string action;

        if (input >> times >> action) {
            for (int i = 0; i < times; ++i) {
                cout << action << "! "s;
            }
            cout << endl;
        } else {
            cout << "muer"s << endl;
            string action2;
            if (input >> action2) {
                cout << action2 << "!"s << endl;
            }
        }
    }
}