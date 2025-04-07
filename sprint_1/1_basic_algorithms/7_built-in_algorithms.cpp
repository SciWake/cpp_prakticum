#include <algorithm>
#include <chrono>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int SAMPLE_COUNT = 5;

/**
 * Определяет, какие имена из вектора candidates содержатся внутри множества storage.
 * Возвращает вектор, где каждому элементу из candidates соответствует одно из чисел:
 *  0 - элемент из candidates отсутствует в storage
 *  1 - элемент из candidates присутствует внутри storage
 */
vector<int> CountNamesLong(const set<string>& storage, const vector<string>& candidates) {
    // Эта функция работает правильно, но недостаточно быстро.
    // Не удаляйте и не изменяйте код этой функции.
    
    vector<int> output;
    for (auto& name : candidates) {
        // Подсчитываем количество вхождений name в storage стандартным алгоритмом count
        output.push_back(static_cast<int>(count(storage.begin(), storage.end(), name)));
    }
    return output;
}

// Напишите тело функции CountNames, которая выдаёт результат, аналогичный CountNamesLong,
// но выполняется быстрее за счёт использования встроенного алгоритма count вместо общего
vector<int> CountNames(const set<string>& storage, const vector<string>& candidates) {
    vector<int> output;
    for (auto& name: candidates) {
        output.push_back(static_cast<int>(storage.count(name)));
    }
    return output;
}

int main() {
    set<string> s;
    vector<string> v;
    string stra;
    string strb;

    for (int j = 0; j < 10000; ++j) {
        s.insert(stra);
        stra += "a"s;
        if (j % 2 == 0) {
            v.push_back(strb);
            strb += "b"s;
        } else {
            v.push_back(stra);
        }
    }

    cout << "Testing slow version" << endl;
    // Замеряем время работы несколько раз, так как оно может отличаться от запуска к запуску
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        // Засекаем время запуска функции
        auto begin = chrono::steady_clock::now();
        CountNamesLong(s, v);
        // Засекаем время завершения функции
        auto end = chrono::steady_clock::now();

        // Выводим время работы в микросекундах
        cout << "Time difference Long = "s
             << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]"s << endl;
    }

    // Вы можете замерить время работы функции CountNames и сравнить её с временем
    // работы CountNamesLong
    cout << "Testing fast version" << endl;
    // Замеряем время работы несколько раз, так как оно может отличаться от запуска к запуску
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        // Засекаем время запуска функции
        auto begin = chrono::steady_clock::now();
        CountNames(s, v);
        // Засекаем время завершения функции
        auto end = chrono::steady_clock::now();

        // Выводим время работы в микросекундах
        cout << "Time difference Long = "s
             << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]"s << endl;
    }
}


// Testing slow version
// Time difference Long = 1816191[µs]
// Time difference Long = 1804298[µs]
// Time difference Long = 1806497[µs]
// Time difference Long = 1808299[µs]
// Time difference Long = 1809536[µs]
// Testing fast version
// Time difference Long = 28336[µs]
// Time difference Long = 28218[µs]
// Time difference Long = 28200[µs]
// Time difference Long = 28095[µs]
// Time difference Long = 27811[µs]