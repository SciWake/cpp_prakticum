#include <iostream>
#include <string>

struct Person {
    std::string name;
    int age;
    
    // Оператор круглых скобок для хэширования объекта Person
    size_t operator()(const Person& /*person*/) const {
        // Пример простого хэширования на основе имени и возраста
        // Это просто для демонстрации, реальные хэш-функции будут более сложными
        // Этот пример иллюстрирует использование безымянного параметра
        size_t name_hash = std::hash<std::string>{}(name);
        size_t age_hash = std::hash<int>{}(age);
        return name_hash ^ (age_hash << 1); // Простой способ комбинировать хэши
    }
};

int main() {
    Person person{"Alice", 30};
    std::hash<Person> hasher; // Используем std::hash<Person> вместо Person::hash_type
    size_t hash_value = hasher(person);
    std::cout << "Hash value: " << hash_value << std::endl;
    return 0;
}
