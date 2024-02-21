#include <iostream>
#include <string>

#include "log_duration.h"

using namespace std;

int main(int argc, const char** argv) {
    // не забываем, что один аргумент — это название программы,
    // поэтому argc должно быть как минимум 2
    if (argc < 2) {
        cerr << "Пожалуйста, задайте как минимум 1 аргумент"s << endl;
        return 1;
    }

    int arg = std::stoi(argv[1]);

    if (arg == 1) {
        LOG_DURATION("endl"s);
        int i;
        while (cin >> i) {
            cout << i * i << endl;
        }
    }

    if (arg == 2) {
        LOG_DURATION("\\n"s);
        int i;
        while (cin >> i) {
            cout << i * i << "\n"s;
        }
    }

    if (arg == 3) {
        LOG_DURATION("\\n with tie"s);
        auto tied_before = cin.tie(nullptr);
        // ios_base::sync_with_stdio(false);
        int i;
        while (cin >> i) {
            cout << i * i << "\n"s;
        }
        cin.tie(tied_before);
    }
}