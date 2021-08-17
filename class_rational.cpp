#include <utility>
#include <iostream>
#include <numeric>

class Rational {
private:
    int numerator_;
    int denominator_;

public:
    Rational(int numerator = 0, int denominator = 1)
            : numerator_(numerator)
            , denominator_(denominator) {
        int common = std::gcd(numerator_, denominator_);
        numerator_ /= common;
        denominator_ /= common;
        if (denominator_ < 0) {
            numerator_ *= (-1);
            denominator_ *= (-1);
        }
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

    Rational operator++(int) {
        Rational frac(*this);
        *this += Rational(1, 1);
        return frac;
    }

    Rational& operator++() {
        *this += Rational(1, 1);
        return *this;
    }

    Rational operator--(int) {
        Rational frac(*this);
        *this -= Rational(1, 1);
        return frac;
    }

    Rational& operator--() {
        *this -= Rational(1, 1);
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    Rational operator+() const {
        return Rational(numerator_, denominator_);
    }

    bool operator==(const Rational& rhs) const {
        return ((rhs.numerator_ == numerator_)
                && (rhs.denominator_ == denominator_));
    }

    bool operator!=(const Rational& rhs) const {
        return (!(*this == rhs));
    }

    Rational operator+=(const Rational& rhs) {
        Rational frac(numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_,
        denominator_ * rhs.denominator_);
        std::swap(*this, frac);
        return *this;
    }

    Rational operator+=(const int rhs) {
        Rational rh(rhs);
        return *this += rh;
    }

    Rational operator+(const Rational& rhs) const {
        return Rational(numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_,
                             denominator_ * rhs.denominator_);
    }

    Rational operator+(const int rhs) const {
        Rational rh(rhs);
        return *this + rh;
    }

    Rational operator-=(const Rational& rhs) {
        Rational frac(numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_,
                      denominator_ * rhs.denominator_);
        std::swap(*this, frac);
        return *this;
    }

    Rational operator-=(const int rhs) {
        Rational rh(rhs);
        return *this -= rh;
    }

    Rational operator-(const Rational& rhs) const {
        return Rational(numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_,
                        denominator_ * rhs.denominator_);
    }

    Rational operator-(const int rhs) const {
        Rational rh(rhs);
        return *this - rh;
    }

    Rational operator*(const Rational& rhs) const {
        return Rational(numerator_ * rhs.numerator_, denominator_ * rhs.denominator_);
    }

    Rational operator*(const int rhs) const {
        Rational rh(rhs);
        return *this * rh;
    }

    Rational operator*=(const Rational& rhs) {
        Rational frac(numerator_ * rhs.numerator_, denominator_ * rhs.denominator_);
        std::swap(*this, frac);
        return *this;
    }

    Rational operator*=(const int rhs) {
        Rational rh(rhs);
        return *this *= rh;
    }

    Rational operator/(const Rational& rhs) const {
        return Rational(numerator_ * rhs.denominator_, denominator_ * rhs.numerator_);
    }

    Rational operator/(const int rhs) const {
        Rational rh(rhs);
        return *this / rh;
    }

    Rational operator/=(const Rational& rhs) {
        Rational frac(numerator_ * rhs.denominator_, denominator_ * rhs.numerator_);
        std::swap(*this, frac);
        return *this;
    }

    Rational operator/=(const int rhs) {
        Rational rh(rhs);
        return *this /= rh;
    }
};

Rational operator/(const int rhs, const Rational& x) {
    Rational rh(rhs);
    return rh / x;
}

Rational operator/=(const int rhs, const Rational& x) {
    Rational rh(rhs);
    return rh /= x;
}

Rational operator*(const int rhs, const Rational& x) {
    Rational rh(rhs);
    return rh * x;
}

Rational operator*=(const int rhs, const Rational& x) {
    Rational rh(rhs);
    return rh *= x;
}

Rational operator+(const int rhs, const Rational& x) {
    Rational rh(rhs);
    return rh + x;
}

Rational operator+=(const int rhs, const Rational& x) {
    Rational rh(rhs);
    return rh += x;
}

Rational operator-(const int rhs, const Rational& x) {
    Rational rh(rhs);
    return rh - x;
}

Rational operator-=(const int rhs, const Rational& x) {
    Rational rh(rhs);
    return rh -= x;
}

