#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

// Если немного изменить функцию свёртки, чтобы она накапливала не только расстояние, 
// но и время, можно вычислить полный путь и время движения. 
// Зная их, вы можете найти среднюю скорость на всём пути. 
// Для этого первым параметром функции свёртки будет пара pair<double, double> — накопленное время и расстояние:


// Функция принимает:
// - информация о пути (общее время и расстояние)
// - информация о текущем отрезке (время и скорость движения)
// Функция возвращает обновлённую информацию о пути (время и расстояние)
pair<double, double> FoldTimeAndDistance(pair<double, double> time_and_distance, 
    pair<double, double> section) {
// Находим расстояние, пройденное на отрезке
double section_distance = section.first * section.second;
// Возвращаем время и расстояние
return {time_and_distance.first + section.first, 
time_and_distance.second + section_distance};
}

int main() {
// Информация о пройденных отрезках пути.
// Каждая пара чисел содержит время (ч) и скорость движения на отрезке (км/ч)
vector<pair<double, double>> sections{
{1.0, 5}, {0.5, 8}, {2, 3.5}
};

// С использованием accumulate вычисляется суммарное время и расстояние
pair<double, double> time_and_distance = accumulate(
sections.begin(), sections.end(), pair{0.0, 0.0}, FoldTimeAndDistance);

cout << "Total time: "s << time_and_distance.first << " hours"s << endl;
cout << "Total distance: "s << time_and_distance.second << " km"s << endl;
// Зная суммарные время и расстояние, вычислим среднюю скорость
cout << "Average speed: "s << time_and_distance.second / time_and_distance.first << " km/h"s << endl;
}

// Total time: 3.5 hours
// Total distance: 16 km
// Average speed: 4.57143 km/h