#include "log_duration.h"

#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using namespace std;

struct PositiveTemperature {
    float sum = 0.f;
    int count = 0;
};

vector<float> ComputeAvgTemp(const vector<vector<float>>& measures) {
    if (measures.empty()) {
        return {};
    }
    size_t n = measures[0].size();
    vector<PositiveTemperature> stat(n);
    for (size_t i = 0; i < measures.size(); ++i) {
        for (size_t j = 0; j < n; ++j) {
            bool isPosTemp = measures[i][j] > 0;
            stat[j].count += isPosTemp ? 1 : 0;
            stat[j].sum += isPosTemp ? measures[i][j] : 0.f;
        }
    }

    vector<float> averages;
    averages.reserve(n);
    for (const auto& [sum, count] : stat) {
        averages.push_back(count > 0 ? (sum / count) : 0);
    }

    return averages;
}

vector<float> GetRandomVector(int size) {
    static mt19937 engine;
    uniform_real_distribution<float> d(-100, 100);

    vector<float> res(size);
    for (int i = 0; i < size; ++i) {
        res[i] = d(engine);
    }

    return res;
}

void Test() {
    // 4 дня по 3 измерения
    vector<vector<float>> v = {
        {0, -1, -1},
        {1, -2, -2},
        {2, 3, -3},
        {3, 4, -4}
    };

    // среднее для 0-го измерения (1+2+3) / 3 = 2 (не учитывам 0)
    // среднее для 1-го измерения (3+4) / 2 = 3.5 (не учитывам -1, -2)
    // среднее для 2-го не определено (все температуры отрицательны), поэтому должен быть 0
    assert(ComputeAvgTemp(v) == vector<float>({2, 3.5f, 0}));
}

int main() {
    Test();
    vector<vector<float>> data;
    data.reserve(5000);

    for (int i = 0; i < 5000; ++i) {
        data.push_back(GetRandomVector(5000));
    }

    vector<float> avg;
    {
        LOG_DURATION("ComputeAvgTemp"s);
        avg = ComputeAvgTemp(data);
    }

    cout << "Total mean: "s << accumulate(avg.begin(), avg.end(), 0.f) / avg.size() << endl;
}