#include <iostream>

using namespace std;

class Cat {
public:
    Cat(const string& name)
        // задаём значение поля name_, копируя в него аргумент конструктора
        : name_(name) 
    {
    }
    string GetName() const {
        return name_;
    }
private:
    string name_;
};

class Witch {
public:
    Witch(const string& catName)
        // Передаём параметр конструктору поля cat_
        : cat_(catName) 
    {
        cout << "Моего кота зовут "s << cat_.GetName() << endl;
    }
private:
    Cat cat_;
};


int main() {
    Witch hermione{"Живоглот"s};
} 