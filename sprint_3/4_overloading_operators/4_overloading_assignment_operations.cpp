#include <iostream>
#include <numeric>

using namespace std;

class Rational {
public:
    Rational() = default;

    Rational(int numerator)
        : numerator_(numerator)
        , denominator_(1)
    {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator)
    {
        Normalize();
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

private:
    void Normalize() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        int n = gcd(numerator_, denominator_);
        numerator_ /= n;
        denominator_ /= n;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

ostream& operator<<(ostream& output, Rational rational) {
    return output << rational.Numerator() << '/' << rational.Denominator();
}

istream& operator>>(istream& input, Rational& rational) {
    int numerator;
    int denominator;
    char slash;
    if ((input >> numerator) && (input >> slash) && (slash == '/') && (input >> denominator)) {
        rational = Rational{numerator, denominator};
    }
    return input;
}

Rational operator+(Rational left, Rational right) {
    const int numerator = left.Numerator() * right.Denominator() + right.Numerator() * left.Denominator();
    const int denominator = left.Denominator() * right.Denominator();

    return {numerator, denominator};
}

// Rational operator-(Rational left, Rational right) {
//     const int numerator = left.Numerator() * right.Denominator() - right.Numerator() * left.Denominator();
//     const int denominator = left.Denominator() * right.Denominator();

//     return {numerator, denominator};
// }

Rational operator+(Rational value) {
    return value;
}

Rational operator-(Rational value) {
    return {-value.Numerator(), value.Denominator()};
}

Rational operator-(Rational left, Rational right) {
    return left + (-right);
}

int main() {
    Rational zero;     // Дробь 0/1 = 0
    const Rational seven(-7); // Дробь 7/1 = 7
    cout << seven << endl;
    // cin >> zero;
    // cout << zero << endl;
    const Rational one_third(5, 3); // Дробь 1/3
    Rational sum = Rational{4, 7} - one_third;
    // Выведет 1/2
    cout << sum.Numerator() << "/" << sum.Denominator();
}