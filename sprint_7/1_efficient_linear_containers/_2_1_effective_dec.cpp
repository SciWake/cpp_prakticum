#include "log_duration.h"

#include <deque>
#include <vector>

using namespace std;


int main() {
    vector<int> num_vec;
    deque<int> num_deq;
    {
        LOG_DURATION("vector push_back");
        for (int i = 0; i < 100000000; ++i) {
            num_vec.push_back(i);
        }
    }
    {
        LOG_DURATION("deque push_back");
        for (int i = 0; i < 100000000; ++i) {
            num_deq.push_back(i);
        }
    }
}