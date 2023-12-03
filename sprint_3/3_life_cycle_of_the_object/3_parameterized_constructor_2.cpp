#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

class Rational {
public:
    Rational() = default;
    
    Rational(int numerator) {
        numerator_ = numerator;
        denominator_ = 1;
    }
    
    Rational(int numerator, int denominator) {
        numerator_ = numerator;
        denominator_ = denominator;
        if (denominator_ < 0) {
            denominator_ *= -1;
            numerator_ *= -1;
        }
        int gcd_num = gcd(numerator_, denominator_);
        if (gcd_num != 0) {
            numerator_ /= gcd_num;
            denominator_ /= gcd_num;
        }
    }
    
    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};


Rational Add(Rational r1, Rational r2) {
    int numerator = r1.Numerator() * r2.Denominator() + r2.Numerator() * r1.Denominator();
    int denominator = r1.Denominator() * r2.Denominator();
    // Создаём и возвращаем дробь с заданным числителем и знаменателем
    return Rational{numerator, denominator};
}
int main() {
    Rational zero;     // Дробь 0/1 = 0
    const Rational seven(7); // Дробь 7/1 = 7
    const Rational one_third(1, 3); // Дробь 1/3
    vector<Rational> numbers;
    numbers.push_back(Rational{7, 8});
    // Следующие 2 строки эквивалентны - добавляют в numbers дробь 3/1
    numbers.push_back(Rational{3});
    numbers.push_back(3);
    Rational sum = Add(Rational{1,6}, one_third);
    // Выведет 1/2
    cout << sum.Numerator() << "/" << sum.Denominator();
}