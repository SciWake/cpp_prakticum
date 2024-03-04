#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <set>

using namespace std;

struct Cat {
    string breed;
    string name;
    int age;
};

ostream& operator<<(ostream& os, const Cat& cat) {
    return os <<'{' << cat.breed << ", "s << cat.name << ", "s << cat.age << '}';
}

// Компаратор, сравнивающий породы кошек
struct CatBreedComparator {
    // Помечаем компаратор как «прозрачный», чтобы с его помощью можно было сравнивать
    // не только кошек с кошками, но и со строками, задающими породу кошек
    using is_transparent = std::true_type;
    
    bool operator()(const Cat& lhs, const Cat& rhs) const {
        return lhs.breed < rhs.breed;
    }
    bool operator()(const Cat& lhs, const string& rhs_breed) const {
        return lhs.breed < rhs_breed; 
    }
    bool operator()(const string& lhs_breed, const Cat& rhs) const {
        return lhs_breed < rhs.breed;
    }
};

int main() {
    // Множество кошек. Кошки считаются эквивалентными, если их породы совпадают.
    // В такой контейнер не получится поместить двух кошек одинаковой породы.
    set<Cat, CatBreedComparator> cats;
    
    cats.insert({"siamese"s, "Tom"s, 3});
    cats.insert({"bengal"s, "Leo"s, 2});
    cats.insert({"birman"s, "Tiger"s, 5});
    // Ginger вставлен не будет, так как множество уже содержит кошку сиамской породы
    cats.insert({"siamese"s, "Ginger"s, 2});
    
    // Выводим кошек в стандартный вывод, по одной на каждой строке
    copy(cats.begin(), cats.end(), ostream_iterator<Cat>(cout, "\n"));
    
    // Кошка, эквивалентная Мурке бенгальской породы, во множестве cats есть - это Leo
    assert(cats.count({"bengal"s, "Murka"s, 6}) == 1);
    
    // Компаратор CatBreedComparator позволяет искать кошек, указывая их породу
    if (auto it = cats.find("siamese"s); it != cats.end()) {
        cout << "Found cat: "s << *it << endl; // Выведет {siamese, Tom, 3}
    }
}