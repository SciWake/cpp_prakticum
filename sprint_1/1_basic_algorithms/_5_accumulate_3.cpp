#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <numeric>

using namespace std;

// Помимо вектора в accumulate можно передавать любой контейнер. 
// Подойдёт, например, set. Если вы хотите использовать алгоритм с map, 
// то учтите, что элементы map — пары ключ-значение, 
// и для их правильной обработки нужно обязательно задать функцию свёртки:
    

// Эта функция будет применяться для суммирования значений map. Она берёт пару из map,
// но использует из неё только второй компонент.
double SumOnlyValues(double current_sum, pair<string, double> elem) {
    return current_sum + elem.second;
}

int main() {
    set<int> unique_numbers{10, 20, 30, 10, 15};
    //Выведет 0 + 10 + 15 + 20 + 30 = 75
    cout << accumulate(unique_numbers.begin(), unique_numbers.end(), 0) << endl;

    map<string, double> accounts = {{"Ivan", 500.}, {"Boris", 100.}, {"Alexey", 1000.}};
    //Выведет 0 + 500 + 100 + 1000 = 1600
    cout << accumulate(accounts.begin(), accounts.end(), 0., SumOnlyValues) << endl;
}
// 75
// 1600