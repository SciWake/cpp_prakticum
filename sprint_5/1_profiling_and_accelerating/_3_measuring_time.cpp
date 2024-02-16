#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

int main() {
    cout << "Ожидание 5s..."s << endl;
    const chrono::steady_clock::time_point start_time = chrono::steady_clock::now();

    // операция - ожидание 5 секунд
    this_thread::sleep_for(chrono::seconds(5));
    const chrono::steady_clock::time_point end_time = chrono::steady_clock::now();

    const chrono::steady_clock::duration dur = end_time - start_time;
    cout << "Ожидание завершено"s << endl;
}