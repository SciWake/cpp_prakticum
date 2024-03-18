/*
Следующая программа выводит размеры и величину выравнивания для 
некоторых стандартных и пользовательских типов на целевой платформе:
*/

#include <cstddef>  // cstddef необходим для использования std::byte
#include <cstdint>  // cstdint необходим для использования uint32_t и int64_t
#include <iostream>

using namespace std;

struct Sportsman {
    int id;
    double height;
};

int main() {
    cout << "char: size="s << sizeof(char) << ", alignment="s << alignof(char) << endl;
    cout << "int: size="s << sizeof(int) << ", alignment="s << alignof(int) << endl;
    cout << "double: size="s << sizeof(double) << ", alignment="s << alignof(double) << endl;
    cout << "Sportsman: size="s << sizeof(Sportsman) << ", alignment="s << alignof(Sportsman) << endl;

    return 0;
}

/* Output:
char: size=1, alignment=1
int: size=4, alignment=4
double: size=8, alignment=8
Sportsman: size=16, alignment=8
*/