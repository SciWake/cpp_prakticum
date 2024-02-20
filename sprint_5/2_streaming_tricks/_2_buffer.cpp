#include "log_duration.h"

#include <fstream>
#include <string>

using namespace std;

// Ничего не запишется
// int main() {
//     ofstream out_file("ballad.txt"s);
//     for (int i = 0; i < 10; ++i) {
//         out_file << "С любимыми не расставайтесь\n"s;
//     }

//     throw;
// }


int main() {
    {
        ofstream out_file("one.txt"s);
        LOG_DURATION("ofstream \\n"s);
        for (int i = 0; i < 50000; ++i) {
            out_file << "С любимыми не расставайтесь\n"s;
        }
    }
    {
        LOG_DURATION("ofstream endl"s);
        ofstream out_file("two.txt"s);
        for (int i = 0; i < 50000; ++i) {
            out_file << "С любимыми не расставайтесь"s << endl;
        }
    }
}