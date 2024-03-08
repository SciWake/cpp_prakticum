#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <random>

using namespace std;

class VehiclePlate {
private:
    auto AsTuple() const {
        return tie(letters_, digits_, region_);
    }

public:
    bool operator==(const VehiclePlate& other) const {
        return AsTuple() == other.AsTuple();
    }

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

private:
    array<char, 3> letters_;
    int digits_;
    int region_;
};

ostream& operator<<(ostream& out, VehiclePlate plate) {
    out << plate.ToString();
    return out;
}

class PlateGenerator {
    char GenerateChar() {
        uniform_int_distribution<short> char_gen{0, static_cast<short>(possible_chars_.size() - 1)};
        return possible_chars_[char_gen(engine_)];
    }

    int GenerateNumber() {
        uniform_int_distribution<short> num_gen{0, 999};
        return num_gen(engine_);
    }

    int GenerateRegion() {
        uniform_int_distribution<short> region_gen{0, static_cast<short>(possible_regions_.size() - 1)};
        return possible_regions_[region_gen(engine_)];
    }

public:
    VehiclePlate Generate() {
        return VehiclePlate(GenerateChar(), GenerateChar(), GenerateNumber(), GenerateChar(), GenerateRegion());
    }

private:
    mt19937 engine_;

    // допустимые значения сохраним в static переменных
    // они объявлены inline, чтобы их определение не надо было выносить вне класса
    inline static const array possible_regions_
        = {1,  2,  102, 3,   4,   5,   6,   7,   8,  9,   10,  11,  12, 13,  113, 14,  15, 16,  116, 17, 18,
           19, 20, 21,  121, 22,  23,  93,  123, 24, 84,  88,  124, 25, 125, 26,  27,  28, 29,  30,  31, 32,
           33, 34, 35,  36,  136, 37,  38,  85,  39, 91,  40,  41,  82, 42,  142, 43,  44, 45,  46,  47, 48,
           49, 50, 90,  150, 190, 51,  52,  152, 53, 54,  154, 55,  56, 57,  58,  59,  81, 159, 60,  61, 161,
           62, 63, 163, 64,  164, 65,  66,  96,  67, 68,  69,  70,  71, 72,  73,  173, 74, 174, 75,  80, 76,
           77, 97, 99,  177, 199, 197, 777, 78,  98, 178, 79,  83,  86, 87,  89,  94,  95};

    // постфикс s у литерала тут недопустим, он приведёт к неопределённому поведению
    inline static const string_view possible_chars_ = "ABCEHKMNOPTXY"sv;
};


int main() {
    static const int N = 10;
    PlateGenerator plate_gen;

    for (int i = 0; i < N; ++i) {
        cout << plate_gen.Generate() << endl;
    }
}