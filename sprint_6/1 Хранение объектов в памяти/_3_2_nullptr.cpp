#include <cassert>
#include <iostream>

int main() {
    using namespace std;

    int* p = nullptr;

    //------
    // Пример кода, который может записать в p адрес существующего объекта
    // или оставить указатель равным nullptr
    int value = 0;
    cin >> value;
    if (value >= 0) {
        p = &value;
    }
    //------

    cout << "p: "s << p << endl;

    if (p != nullptr) {
        assert(p == &value);
        cout << "p is not nullptr"s << endl;
        // Можно использовать указатель p для доступа к объекту
    }

    // Аналогично условию p != nullptr
    if (p) {
        assert(p != nullptr);

        // Можно использовать указатель p для доступа к объекту
    }

    if (!p) {
        assert(p == nullptr);
        cout << "p is nullptr"s << endl;
        // Указатель p равен nullptr. Использовать его для доступа к объекту нельзя
    }
}