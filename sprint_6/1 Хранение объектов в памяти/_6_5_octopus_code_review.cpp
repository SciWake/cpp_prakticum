#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
// Щупальце
class Tentacle {
public:
    explicit Tentacle(int id)
        : id_(id) {
    }

    int GetId() const {
        return id_;
    }

private:
    int id_ = 0;
};

// Осьминог
class Octopus {
public:
    Octopus() {
        for (int i = 1; i <= 8; ++i) {
            tentacles_.push_back(new Tentacle(i));
        }
    }

private:
    vector<Tentacle*> tentacles_;
};

int main() {
    Octopus octopus;
}

*/

// Щупальце
class Tentacle {
public:
    explicit Tentacle(int id)
        : id_(id) {
    }

    int GetId() const {
        return id_;
    }

private:
    int id_ = 0;
};

// Осьминог
class Octopus {
public:
    Octopus() {
        // <--- Тело конструктора обновлено
        Tentacle* t = nullptr;
        try {
            for (int i = 1; i <= 8; ++i) {
                t = new Tentacle(i);
                tentacles_.push_back(t);
                t = nullptr;
            }
        } catch (const bad_alloc&) {
            Cleanup();
            delete t;
            throw bad_alloc();
        }
        // --->
    }

    // <--- Добавлен деструктор
    ~Octopus() {
        Cleanup();
    }
    // --->

private:
    // <--- Добавлен метод Cleanup
    void Cleanup() {
        for (Tentacle* t : tentacles_) {
            delete t;
        }
        tentacles_.clear();
    }
    // --->

    vector<Tentacle*> tentacles_;
};

int main() {
    Octopus octopus;
}