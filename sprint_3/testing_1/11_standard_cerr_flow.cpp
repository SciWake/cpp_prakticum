#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;


template <typename T>
ostream& operator<<(ostream& output, const vector<T>& items) {
    output << "["s;
    bool first_item = true;
    for (const T& item : items) {
        if (!first_item) {
            output << ", "s;
        }
        output << item;
        first_item = false;
    }
    output << "]"s;
    return output;
}

template <typename T>
ostream& operator<<(ostream& output, const set<T>& items) {
    output << "{"s;
    bool first_item = true;
    for (const T& item : items) {
        if (!first_item) {
            output << ", "s;
        }
        output << item;
        first_item = false;
    }
    output << "}"s;
    return output;
}

template <typename K, typename V>
ostream& operator<<(ostream& output, const map<K, V>& items) {
    output << "{"s;
    bool first_item = true;
    for (const auto& [key, value] : items) {
        if (!first_item) {
            output << ", "s;
        }
        output << key << ": "s << value;
        first_item = false;
    }
    output << "}"s;
    return output;
}

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file,
                     const string& func, unsigned line, const string& hint) {
    if (t != u) {
        cerr << boolalpha;
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        cerr << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
}

void AssertImpl(bool value, const string& expr_str, const string& file, const string& func, unsigned line,
                const string& hint) {
    if (!value) {
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "Assert("s << expr_str << ") failed."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
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


// Пример запуска теста

void TestAddingSynonymsIncreasesTheirCount() {
    // ...

    cerr << "TestAddingSynonymsIncreasesTheirCount OK"s << endl;
}

void TestAreSynonyms() {
    // ...

    cerr << "TestAreSynonyms OK"s << endl;
}

void TestAddingTakePositives() {
    const vector<int> numbers = {1, 0, 2, -3, 6, 2, 4, 3};
    const vector<int> expected_evens = {0, 2, 6, 2, 4};
    ASSERT_EQUAL(TakeEvens(numbers), expected_evens);
    cerr << "TestAddingTakePositives OK"s << endl;

    const vector<int> expected_positives = {1, 2, 6, 2, 4, 3};
    ASSERT_EQUAL(TakePositives(numbers), expected_positives);
}


template <typename TestFunc>
void RunTestImpl(const TestFunc& func, const string& test_name) {
    func();
    cerr << test_name << " OK"s << endl;
}


#define RUN_TEST(func) RunTestImpl(func, #func)


int main() {
    RUN_TEST(TestAddingSynonymsIncreasesTheirCount);
    RUN_TEST(TestAreSynonyms);
    RUN_TEST(TestAddingTakePositives);
}