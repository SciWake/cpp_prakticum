#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Animal {
    string name;
    int age;
    double weight;
};

enum class AnimalSortKey {
    AGE,     // по полю age
    WEIGHT,  // по полю weight
    RELATIVE_WEIGHT  // по weight / age
};

// template <typename Container, typename KeyMapper>
// void SortBy(Container& container, KeyMapper key_mapper, bool reverse = false) {
//     // теперь можно сортировать контейнер
//     // с компаратором key_mapper(lhs) < key_mapper(rhs)
//     sort(begin(container), end(container), [key_mapper, reverse](const auto& lhs, const auto& rhs){
//         return reverse ? key_mapper(lhs) > key_mapper(rhs) : key_mapper(lhs) < key_mapper(rhs);
//     });
// }

// Предпочтительный варинт 
// template <typename Container>
// void SortBy(Container& animals, AnimalSortKey sort_key, bool reverse = false) {
//     switch (sort_key) {
//         case AnimalSortKey::AGE:
//             return SortBy(animals, [](const auto& x) { return x.age; }, reverse);
//         case AnimalSortKey::WEIGHT:
//             return SortBy(animals, [](const auto& x) { return x.weight; }, reverse);
//         case AnimalSortKey::RELATIVE_WEIGHT:
//             return SortBy(animals, [](const auto& x) { return x.weight / x.age; }, reverse);
//     }
// }


// "Python Style"
template <typename Container, typename KeyMapper>
void SortBy(Container& container, KeyMapper key_mapper, bool reverse = false) {
        // если KeyMapper — это AnimalSortKey...
    if (is_same_v<KeyMapper, AnimalSortKey>) {
        switch (key_mapper) {
            case AnimalSortKey::AGE:
                return SortBy(container, [](const auto& x) { return x.age; }, reverse);
            case AnimalSortKey::WEIGHT:
                return SortBy(container, [](const auto& x) { return x.weight; }, reverse);
            case AnimalSortKey::RELATIVE_WEIGHT:
                return SortBy(container, [](const auto& x) { return x.weight / x.age; }, reverse);
        }
                // вышли из функции, остальное снаружи if
    }
    if (reverse) {
        sort(container.begin(), container.end(),
             [key_mapper](const auto& lhs, const auto& rhs) {
                return key_mapper(lhs) > key_mapper(rhs);
             });
    } else {
        sort(container.begin(), container.end(),
             [key_mapper](const auto& lhs, const auto& rhs) {
                return key_mapper(lhs) < key_mapper(rhs);
             });
    }
}

void PrintNames(const vector<Animal>& animals) {
    for (const Animal& animal : animals) {
        cout << animal.name << ' ';
    }
    cout << endl;
}

int main() {
    vector<Animal> animals = {
        {"Мурка"s,   10, 5},
        {"Белка"s,   5,  1.5},
        {"Георгий"s, 2,  4.5},
        {"Рюрик"s,   12, 3.1},
    };
    PrintNames(animals);
    SortBy(animals, [](const Animal& animal) { return animal.name; }, true);
    PrintNames(animals);
    SortBy(animals, [](const Animal& animal) { return animal.weight; });
    PrintNames(animals);
    SortBy(animals, AnimalSortKey::RELATIVE_WEIGHT);
    PrintNames(animals);
    return 0;
}