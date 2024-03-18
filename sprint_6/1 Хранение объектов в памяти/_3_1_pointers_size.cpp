/*
Размер указателей равен размеру адреса на конкретной платформе 
и не зависит от размера самих объектов. Рассмотрим пример:
*/

#include <iostream>
#include <map>
#include <string>

struct Vector3D {
    double x;
    double y;
    double z;
};

int main() {
    using namespace std;

    map<string, string>* string_to_string;

    cout << "char*: size:"s << sizeof(char*) << endl;
    cout << "int*: size:"s << sizeof(int*) << endl;
    cout << "double*: size:"s << sizeof(double*) << endl;
    cout << "Vector3D*: size:"s << sizeof(Vector3D*) << endl;
    cout << "map<string, string>*: size:"s << sizeof(string_to_string) << endl;
}

/*
char*: size:8
int*: size:8
double*: size:8
Vector3D*: size:8
map<string, string>*: size:8
*/