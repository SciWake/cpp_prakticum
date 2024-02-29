#include <cassert>

using namespace std;

#include <iostream>

int main() {
    int value = 1;

    // Указатель value_ptr1, ссылающийся на переменную value
    int* value_ptr1 = &value;
    cout << value_ptr1 << "  "s << &value << endl;
    cout << &value_ptr1;
    // Указатель value_ptr2, копия указателя value_ptr1, также ссылается на переменную value
    int* value_ptr2 = value_ptr1;

    // Значения указателей на один и тот же объект будут равны
    assert(value_ptr1 == value_ptr2);

    // Значение объекта value, полученное напрямую и через указатель на него, будет одно и то же
    assert(*value_ptr1 == value && *value_ptr2 == value);

    // Изменение value видно через указатели на него
    value = 2;
    assert(*value_ptr1 == value && *value_ptr2 == value);

    // Изменяем значение value через указатель
    *value_ptr2 = 3;

    // Ожидаемо изменённое значение будет видно как при прямом доступе к объекту по его имени,
    // так и при косвенном обращении через указатель value_ptr1
    assert(*value_ptr1 == value && *value_ptr2 == value);
}