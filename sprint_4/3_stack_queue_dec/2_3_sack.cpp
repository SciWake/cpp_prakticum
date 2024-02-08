#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Type>
class Stack {
   public:
    void Push(const Type& element) {
        elements_.push_back(element);
    }
    void Pop() {
        elements_.pop_back();
    }
    const Type& Peek() const {
        return elements_.back();
    }
    Type& Peek() {
        return elements_.back();
    }
    void Print() const {
        PrintRange(elements_.begin(), elements_.end());
    }
    uint64_t Size() const {
        return elements_.size();
    }
    bool IsEmpty() const {
        return elements_.empty();
    }

   private:
    vector<Type> elements_;
};

// используем струкруту из элемента
// и минимума в стеке до дна стека до текущего элемента включительно
template <typename Type>
struct PairWithMin {
    Type element;
    Type minimum;
};

template <typename Type>
ostream& operator<<(ostream& out, const PairWithMin<Type>& pair_to_print) {
    // будем выводить только сам элемент, выводить минимум не будем
    out << pair_to_print.element;
    return out;
}

template <typename Type>
class SortedSack {
public:
    void Push(const Type& element) {
    // напишите реализацию метода
    }
    void Pop() {
    // напишите реализацию метода
    }
    const Type& Peek() const {
    return elements_.Peek();
    }
    Type& Peek() {
    return elements_.Peek();
    }
    void Print() const {
    elements_.Print();
    }
    uint64_t Size() const {
    return elements_.Size();
    }
    bool IsEmpty() const {
    return elements_.IsEmpty();
    }
private:
    Stack<Type> elements_;
};

int main() {
    SortedSack<int> sack;
    vector<int> values(5);
    // заполняем вектор для тестирования нашего класса
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    shuffle(values.begin(), values.end());

    // заполняем класс и проверяем, что сортировка сохраняется после каждой вставки
    for (int i = 0; i < 5; ++i) {
        cout << "Вставляемый элемент = "s << values[i] << endl;
        sack.Push(values[i]);
        sack.Print();
    }
}