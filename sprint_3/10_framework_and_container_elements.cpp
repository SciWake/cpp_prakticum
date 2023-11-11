#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file,
                     const string& func, unsigned line, const string& hint) {
    if (t != u) {
        cout << boolalpha;
        cout << file << "("s << line << "): "s << func << ": "s;
        cout << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        cout << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cout << " Hint: "s << hint;
        }
        cout << endl;
        abort();
    }
}

#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

vector<int> TakeEvens(const vector<int>& numbers) {
    vector<int> evens;
    for (int x : numbers) {
        if (x % 2 == 0) {
            evens.push_back(x);
        }
    }
    return evens;
}

vector<int> TakePositives(const vector<int>& numbers) {
    vector<int> positives;
    for (int x : numbers) {
        // Ошибка допущена намеренно, чтобы продемонстрировать вывод при несработавшем AssertEqual
        if (x >= 0) {
            positives.push_back(x);
        }
    }
    return positives;
}

int main() {
    const vector<int> numbers = {1, 0, 2, -3, 6, 2, 4, 3};
    const vector<int> expected_evens = {0, 2, 6, 2, 4};
    ASSERT_EQUAL(TakeEvens(numbers), expected_evens);

    const vector<int> expected_positives = {1, 2, 6, 2, 4, 3};
    ASSERT_EQUAL(TakePositives(numbers), expected_positives);
}