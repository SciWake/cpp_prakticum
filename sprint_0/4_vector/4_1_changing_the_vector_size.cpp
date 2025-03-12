#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int q;
    cin >> q;

    vector<bool> queue;
  
    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;
    
        if (operation_code == "WORRY"s) {
            int index;
            cin >> index;

            queue[index] = true;
        } else if (operation_code == "HAPPY"s) {
            int index;
            cin >> index;

            queue[index] = false;
        } else if (operation_code == "COME"s) {
            int count;
            cin >> count;

            queue.resize(queue.size() + count, false);
        } else if (operation_code == "LAST_WORRY"s)  {
            if (queue.back()) {
                cout << "worry"s << endl;
            } else {
                cout << "happy"s << endl;
            }
        }
    }
}