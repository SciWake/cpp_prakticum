#include <iostream>
#include <new>
#include <string>

using namespace std;

int main() {
    size_t n = 0;
    try {
        for (; n != 300; ++n) {
            string* p = new string(100'000'000, ' ');
            // Утечка памяти исправлена - объект в куче своевременно удаляется
            delete p;
        }
        cout << "Program completed successfully"s;
    } catch (const bad_alloc&) {
        // Сюда программа, скорее всего, не попадёт,
        // если объём свободной памяти в куче будет больше 100 мегабайт
        cout << "bad_alloc after "s << n << " allocations"s << endl;
    }
}