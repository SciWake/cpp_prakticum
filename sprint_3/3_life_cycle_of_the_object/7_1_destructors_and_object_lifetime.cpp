#include <cmath>
#include <iostream>

using namespace std;


class Greeter {
public:
    Greeter() = default;
    Greeter(const string& name_1, const string& name_2)
        : name_1(name_1)
        , name_2(name_2) {
        cout << "Hello, "s << name_1 << " and "s << name_2 << "!"s << endl;
    }

    Greeter(const string& name_1)
        : name_1(name_1) {
        cout << "Hello, "s << name_1 << "!"s << endl;
    }

    ~Greeter() {
        // Поля класса внутри деструктора еще не уничтожены, и к ним можно обращаться
        cout << "Goodbye, "s << name_1 << " and "s << name_2 << "!"s << endl;
    }
private:
    string name_1 = "name_1";
    string name_2 = "name_2";
};


class Cat {
public:
    Cat() = default;
    Cat(const string& catName) 
        : cat_(catName) {
        Greeter cat_("Felex", "Murka");
    }
private:
    Greeter cat_ = "Tom"s;
    Greeter cat1_{"Felex_1", "Murka_1"};
};

Cat hermione("Murzik");

int main() {
    // Cat hermione{"Живоглот"s};
    // Cat hermione;
    cout << "hi"s << endl;
} 

// Расширить идею до трёх классов и понять как работает инициализация объектов