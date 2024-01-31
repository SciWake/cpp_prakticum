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

    bool operator> (const Rational& var){
        return ConvertToDouble(*this) > ConvertToDouble(var);
    }

    bool operator< (const Rational& var){
        return ConvertToDouble(*this) < ConvertToDouble(var);
    }

    bool operator<= (const Rational& var){
        return ConvertToDouble(*this) <= ConvertToDouble(var);
    }

    bool operator>= (const Rational& var){
        return ConvertToDouble(*this) >= ConvertToDouble(var);
    }

    bool operator== (const Rational& var){
        return ConvertToDouble(*this) == ConvertToDouble(var);
    }

    bool operator!= (const Rational& var){
        return ConvertToDouble(*this) != ConvertToDouble(var);
    }

    Rational operator+=(const Rational& val){
        *this = *this + val;
        return *this;
    }

    Rational operator-=(const Rational& val){
        *this = *this - val;
        return *this;
    }

    Rational operator*=(const Rational& val){
        *this = *this * val;
        return *this;
    }

    Rational operator/=(const Rational& val){
        *this = *this / val;
        return *this;
    }

    Rational operator+(const Rational& val) const{
        return {this->numerator_ * val.denominator_ + val.numerator_ * this->denominator_, this->denominator_ * val.denominator_};
    }

    Rational operator+() const{
        return *this;
    }

    Rational operator-(const Rational& val) const{
        return {this->numerator_ * val.denominator_ - val.numerator_ * this->denominator_, this->denominator_ * val.denominator_};
    }

    Rational operator-() const{
        return {-this->numerator_ , this->denominator_};
    }

    Rational operator*(const Rational& val) const{
        return {this->numerator_ * val.numerator_, this->denominator_ * val.denominator_};
    }

    Rational operator/(const Rational& val) const{
        return {this->numerator_ * val.denominator_, this->denominator_ * val.numerator_};
    }

private:
    
    double ConvertToDouble(const Rational& var){
        return (static_cast<double>(var.numerator_) / var.denominator_);
    }
    
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
    output << rational.Numerator() << '/' << rational.Denominator();
    return output;
}

istream& operator>>(istream& input, Rational& rational) {
    int numerator, denominator;
    char slash;
    input >> numerator >> slash >> denominator;
    rational = Rational{numerator, denominator};
    return input;
}

int main(){
    Rational r(2,5);
    r = r + r;
    r += r;
}