#include <cmath>
#include <iostream>

using namespace std;

class Greeter {
public:
    Greeter(const string& name)
        : name_(name) 
    {
        cout << "Hello, "s << name_ << "!"s << endl;
    }

    ~Greeter() {
        // Поля класса внутри деструктора еще не уничтожены, и к ним можно обращаться
        cout << "Goodbye, "s << name_ << "!"s << endl;
    }
private:
    string name_;
};


// void Fn(Greeter g) {
//     Greeter g1("function body"s);
// }


Greeter Fn(const Greeter& g) {
    return Greeter("function body"s);
}

Greeter Fn1(const Greeter& g) {
    return Greeter("function body_1"s);
}

Greeter s1 = Fn({"out1"s});   

int main() {
    Greeter s = Fn1({"function parameter"s});    
    cout << "hi"s << endl;
}

Greeter ss = Greeter{"out2"s};