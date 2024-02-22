#include <stack>
#include <iostream>

using namespace std;

template <typename Type>
class SortedSack {
public:
    void Push(const Type& element) {
        if (elements_.empty()) {
            elements_.push(element);
            insertions_++;
            return;
        }

        Type last_elem = elements_.top();
        if (last_elem < element) {
            comparisons_++;
            elements_.pop();
            Push(element);
            elements_.push(last_elem);
            insertions_++;
        } else {
            elements_.push(element);
            insertions_++;
        }
    }

    // остальные функции не понадобятся

    // Добавляем функции для получения результатов
    int GetInsertions() const {
        return insertions_;
    }

    int GetComparisons() const {
        return comparisons_;
    }

private:
    stack<Type> elements_;
    int insertions_ = 0;
    int comparisons_ = 0;
};

// Пример использования:
int main() {
    SortedSack<int> sortedSack;

    for (int i = 1; i <= 100; ++i) {
        sortedSack.Push(i);
    }
    cout << sortedSack.GetComparisons() << sortedSack.GetInsertions() << endl;
    cout << sortedSack.GetInsertions() << sortedSack.GetComparisons() << endl;

    return 0;
}
