#include <array>
#include <algorithm>
#include <iomanip>
#include <tuple>
#include <optional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class VehiclePlate {
// private:
//     auto AsTuple() const {
//         return tie(letters_, digits_, region_);
//     }
// https://habr.com/ru/articles/478124/
// https://learn.microsoft.com/ru-ru/cpp/cpp/auto-cpp?view=msvc-170
// error: use of 'sum' before deduction of 'auto'
public:
    VehiclePlate(char l0, char l1, int digits, char l2, int region)
        : letters_{l0, l1, l2}
        , digits_(digits)
        , region_(region) {
    }

    string ToString() const {
        ostringstream out;
        out << letters_[0] << letters_[1];
        // чтобы дополнить цифровую часть номера слева нулями
        // до трёх цифр, используем подобные манипуляторы:
        // setfill задаёт символ для заполнения,
        // right задаёт выравнивание по правому краю,
        // setw задаёт минимальное желаемое количество знаков
        out << setfill('0') << right << setw(3) << digits_;
        out << letters_[2] << setw(2) << region_;

        return out.str();
    }

    int Hash() const {
        return digits_;
    }

    // bool operator==(const VehiclePlate& plate) {
    //     return letters_ == plate.letters_ && digits_ == plate.digits_ 
    //            && region_ == plate.region_;
    // }

    bool operator==(const VehiclePlate& other) const {
        return AsTuple() == other.AsTuple();
    }

private:
    std::tuple<array<char, 3>, int, int> AsTuple() const {
        return std::tie(letters_, digits_, region_);
    }
    array<char, 3> letters_;
    int digits_;
    int region_;
};

ostream& operator<<(ostream& out, VehiclePlate plate) {
    out << plate.ToString();
    return out;
}

template <typename T>
class HashableContainer {
public:
    void Insert(T elem) {
        int index = elem.Hash();

        // если вектор недостаточно велик для этого индекса,
        // то увеличим его, выделив место с запасом
        if (index >= int(elements_.size())) {
            elements_.resize(index * 2 + 1);
        }

        auto& batch = elements_[index];
        if (find(begin(batch), end(batch), elem) == end(batch)) {
            batch.push_back(move(elem));
        }
    }

    void PrintAll(ostream& out) const {
        for (auto& bag : elements_) {
            for (auto& e : bag) {
                out << e << endl;
            }
        }
    }

    const auto& GetVector() const {
        return elements_;
    }

private:
    vector<vector<T>> elements_;
};

int main() {
    HashableContainer<VehiclePlate> plate_base;
    plate_base.Insert({'B', 'H', 840, 'E', 99});
    plate_base.Insert({'O', 'K', 942, 'K', 78});
    plate_base.Insert({'O', 'K', 942, 'K', 78});
    plate_base.Insert({'O', 'K', 942, 'K', 78});
    plate_base.Insert({'O', 'K', 942, 'K', 78});
    plate_base.Insert({'H', 'E', 968, 'C', 79});
    plate_base.Insert({'T', 'A', 326, 'X', 83});
    plate_base.Insert({'H', 'H', 831, 'P', 116});
    plate_base.Insert({'P', 'M', 884, 'K', 23});
    plate_base.Insert({'O', 'C', 34, 'P', 24});
    plate_base.Insert({'M', 'Y', 831, 'M', 43});
    plate_base.Insert({'K', 'T', 478, 'P', 49});
    plate_base.Insert({'X', 'P', 850, 'A', 50});

    plate_base.PrintAll(cout);
}