#include <stack>

using namespace std;

template <typename Type>
class SortedSack {
public:
    void Push(const Type& element) {
        if (elements_.empty()) {
            elements_.push(element);
            return;
        }

        Type last_elem = elements_.top();
        if (last_elem < element) {
            elements_.pop();
            Push(element);

            elements_.push(last_elem);
        } else {
            elements_.push(element);
        }
    }

    // остальные функции не понадобятся
private:
    stack<Type> elements_;
};