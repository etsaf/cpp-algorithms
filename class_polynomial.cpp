/* & - function composition, () - value at point,
[] - coefficient before given degree, << - print polynomial */
#include <algorithm>
#include <iostream>
#include <vector>


template <typename T>
class Polynomial {
private:
    std::vector<T> coeffs;
    void Canonize() {
        while (coeffs.size() && coeffs.back() == T()) {
            coeffs.pop_back();
        }
    }

public:
    Polynomial(const std::vector<T>& v)
    : coeffs(v) {
        Canonize();
    }

    Polynomial(const T& n = T())
    : coeffs({n}) {
        Canonize();
    }

    template <typename Iter>
    Polynomial(Iter begin, Iter end)
    : coeffs(begin, end) {
        Canonize();
    }

    bool operator==(const Polynomial<T>& rhs) const {
        if (coeffs.size() != rhs.coeffs.size()) {
            return false;
        }
        return coeffs == rhs.coeffs;
    }

    bool operator==(const T& r) const {
        Polynomial<T> rhs(r);
        return *this == rhs;
    }

    bool operator!=(const Polynomial<T>& rhs) const {
        return !(*this == rhs);
    }

    bool operator!=(const T& r) const {
        Polynomial<T> rhs(r);
        return *this != rhs;
    }

    Polynomial<T>& operator+=(const Polynomial<T>& rhs) {
        size_t common_size = std::min(coeffs.size(), rhs.coeffs.size());
        for (size_t i = 0; i < common_size; ++i) {
            coeffs[i] += rhs.coeffs[i];
        }
        if (rhs.coeffs.size() > coeffs.size()) {
            coeffs.insert(coeffs.end(), rhs.coeffs.begin() + common_size,
                          rhs.coeffs.end());
        }
        Canonize();
        return *this;
    }

    Polynomial<T> operator+(const Polynomial<T>& rhs) const {
        Polynomial<T> temp(coeffs);
        temp += rhs;
        return temp;
    }

    Polynomial<T>& operator-=(const Polynomial<T>& rhs) {
        size_t ls, rs;
        ls = coeffs.size();
        rs = rhs.coeffs.size();
        size_t common_size = std::min(ls, rs);
        for (size_t i = 0; i < common_size; ++i) {
            coeffs[i] -= rhs.coeffs[i];
        }
        if (rhs.coeffs.size() > coeffs.size()) {
            for (size_t i = common_size; i < rhs.coeffs.size(); ++i) {
                coeffs.push_back(-rhs.coeffs[i]);
            }
        }
        Canonize();
        return *this;
    }

    Polynomial<T> operator-(const Polynomial<T>& rhs) const {
        Polynomial<T> temp(coeffs);
        temp -= rhs;
        return temp;
    }

    Polynomial<T>& operator+=(const T& r) {
        Polynomial<T> rhs(r);
        return *this += rhs;
    }

    Polynomial<T> operator+(const T& r) const {
        Polynomial<T> rhs(r);
        Polynomial<T> temp(*this);
        return temp + rhs;
    }

    Polynomial<T>& operator-=(const T& r) {
        Polynomial<T> rhs(r);
        return *this -= rhs;
    }

    Polynomial<T> operator-(const T& r) const {
        Polynomial<T> rhs(r);
        Polynomial<T> temp(*this);
        return temp - rhs;
    }

    T operator[](size_t i) const {
        if (i >= coeffs.size()) {
            return T();
        }
        return coeffs[i];
    }

    ssize_t Degree() const {
        return coeffs.size() - 1;
    }

    typename std::vector<T>::const_iterator begin() const {
        return coeffs.begin();
    }

    typename std::vector<T>::const_iterator end() const {
        return coeffs.end();
    }

    Polynomial<T>& operator*=(const Polynomial<T>& rhs) {
        ssize_t saved_size = static_cast<ssize_t>(coeffs.size());
        ssize_t other_size = static_cast<ssize_t>(rhs.coeffs.size());
        std::vector<T> temp;
        temp.resize(rhs.coeffs.size() + coeffs.size() - 1);
        for (ssize_t i = saved_size - 1; i >= 0; --i) {
            for (ssize_t j = other_size - 1; j >= 0; --j) {
                temp[i + j] += coeffs[i] * rhs.coeffs[j];
            }
        }
        coeffs = temp;
        Canonize();
        return *this;
    }

    Polynomial<T> operator*(const Polynomial<T>& rhs) const {
        Polynomial<T> temp(coeffs);
        temp *= rhs;
        return temp;
    }

    Polynomial<T> operator*(const T& r) const {
        Polynomial<T> rhs(r);
        Polynomial<T> temp(*this);
        return temp * rhs;
    }

    T operator()(T x) const {
        if (coeffs.size() == 0) {
            return T();
        }
        T res = coeffs[0];
        T deg = x;
        for (size_t i = 1; i < coeffs.size(); i++) {
            res += coeffs[i] * deg;
            deg *= x;
        }
        return res;
    }

    Polynomial<T> operator&(const Polynomial<T>& rhs) const {
        Polynomial<T> res(0);
        if (coeffs.size() == 0) {
            return res;
        }
        Polynomial<T> temp(1);
        res += temp * coeffs[0];
        if (rhs.coeffs.size() == 0) {
            return res;
        }
        for (size_t i = 1; i < coeffs.size(); ++i) {
            temp *= rhs;
            res += temp * coeffs[i];
        }
        return res;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Polynomial<U>& f);
};

template <typename T>
bool operator==(const T& left, const Polynomial<T>& rhs) {
    Polynomial<T> lhs(left);
    return lhs == rhs;
}

template <typename T>
bool operator!=(const T& left, const Polynomial<T>& rhs) {
    Polynomial<T> lhs(left);
    return !(lhs == rhs);
}

template <typename T>
Polynomial<T> operator+(const T& left, const Polynomial<T>& rhs) {
    Polynomial<T> lhs(left);
    return lhs + rhs;
}

template <typename T>
Polynomial<T> operator-(const T& left, const Polynomial<T>& rhs) {
    Polynomial<T> lhs(left);
    return lhs - rhs;
}

template <typename T>
Polynomial<T> operator*(const T& left, const Polynomial<T>& rhs) {
    Polynomial<T> lhs(left);
    return lhs * rhs;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& f) {
    T minus = T();
    --minus;
    T one = T();
    ++one;
    if (f.Degree() == static_cast<ssize_t>(-1)) {
        out << T();
        return out;
    }
    if (f.Degree() == static_cast<ssize_t>(0)) {
        out << f.coeffs[0];
        return out;
    }
    if (f.Degree() == static_cast<ssize_t>(1)) {
        if (f.coeffs[1] == minus) {
            out << "-x";
        } else if (f.coeffs[1] == one) {
            out << "x";
        } else {
            out << f.coeffs[1] << "*x";
        }
        if (f.coeffs[0] != T()) {
            if (f.coeffs[0] < T()) {
                out << f.coeffs[0];
            } else {
                out << '+' << f.coeffs[0];
            }
        }
        return out;
    }
    ssize_t f_size = static_cast<ssize_t>(f.coeffs.size());
    for (ssize_t i = f_size - 1; i >= 0; --i) {
        if (f.coeffs[i] != T()) {
            if (i == f_size - 1) {
                if (f.coeffs[i] == minus) {
                    out << "-x^" << i;
                } else if (f.coeffs[i] == one) {
                    out << "x^" << i;
                } else {
                    out << f.coeffs[i] << "*x^" << i;
                }
            } else if (i == 1) {
                if (f.coeffs[1] == minus) {
                    out << "-x";
                } else if (f.coeffs[1] == one) {
                    out << "+x";
                } else {
                    if (f.coeffs[1] < T()) {
                        out << f.coeffs[1] << "*x";
                    } else {
                        out << '+' << f.coeffs[1] << "*x";
                    }
                }
            } else if (i == 0) {
                if (f.coeffs[0] < T()) {
                    out << f.coeffs[0];
                } else {
                    out << '+' << f.coeffs[0];
                }
            } else {
                if (f.coeffs[i] == minus) {
                    out << "-x^" << i;
                } else if (f.coeffs[i] == one) {
                    out << "+x^" << i;
                } else {
                    if (f.coeffs[i] < T()) {
                        out << f.coeffs[i] << "*x^" << i;
                    } else {
                        out << '+' << f.coeffs[i] << "*x^" << i;
                    }
                }
            }
        }
    }
    return out;
}