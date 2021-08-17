#include <iostream>
#include <cmath>

class Complex {
private:
    double real_;
    double imag_;

public:
    auto& Re() const {
        return real_;
    }

    auto& Im() const {
        return imag_;
    }

    Complex(double real, double imag = 0.0)
    : real_(real)
    , imag_(imag)
    {}

    Complex operator-() const {
        return Complex(-real_, -imag_);
    }

    Complex operator+() const {
        return Complex(real_, imag_);
    }

    Complex operator+(const Complex& rhs) const {
        return Complex(real_ + rhs.real_, imag_ + rhs.imag_);
    }

    Complex operator+(const double& rhs) const {
        Complex rh(rhs);
        return *this + rh;
    }

    Complex operator-(const Complex& rhs) const {
        return Complex(real_ - rhs.real_, imag_ - rhs.imag_);
    }

    Complex operator-(const double& rhs) const {
        Complex rh(rhs);
        return *this - rh;
    }

    Complex operator*(const Complex& rhs) const {
        double re, im;
        re = real_ * rhs.real_ - imag_ * rhs.imag_;
        im = real_ * rhs.imag_ + imag_ * rhs.real_;
        return Complex(re, im);
    }

    Complex operator*(const double& rhs) const {
        Complex rh(rhs);
        return *this * rh;
    }

    Complex operator/(const Complex& rhs) const {
        double re, im, de;
        re = real_ * rhs.real_ + imag_ * rhs.imag_;
        im = imag_ * rhs.real_ - real_ * rhs.imag_;
        de = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
        return Complex(re / de, im / de);
    }

    Complex operator/(const double& rhs) const {
        Complex rh(rhs);
        return *this / rh;
    }

    bool operator==(const Complex& rhs) const {
        return ((rhs.real_ == real_) && (rhs.imag_ == imag_));
    }

    bool operator!=(const Complex& rhs) const {
        return (!(*this == rhs));
    }
};

Complex operator+(const double& rhs, const Complex& x) {
    Complex rh(rhs);
    return x + rh;
}

Complex operator-(const double& rhs, const Complex& x) {
    Complex rh(rhs);
    return rh - x;
}

Complex operator*(const double& rhs, const Complex& x) {
    Complex rh(rhs);
    return x * rh;
}

Complex operator/(const double& rhs, const Complex& x) {
    Complex rh(rhs);
    return rh / x;
}

double Abs(const Complex& c) {
    double re, im;
    re = c.Re();
    im = c.Im();
    return hypot(re, im);
}

