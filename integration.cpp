#include <cmath>
#include <iostream>
#include <memory>
#include <string>

template <typename F>
class IntegrationMethod {
public:
    virtual ~IntegrationMethod() {}
    virtual double Integrate(const F& f, double left,
                             double right, int n) const = 0;
};

template <typename F>
class RectangleRule : public IntegrationMethod<F> {
public:
    ~RectangleRule() {}
    double Integrate(const F& f, double left,
                     double right, int n) const override {
        double res = 0;
        double x_1 = left;
        double diff = (right - left) / n;
        for (int i = 0; i <= n - 1; ++i) {
            double x_2 = x_1 + diff;
            res += (f((x_1 + x_2) / 2) * diff);
            x_1 = x_2;
        }
        return res;
    }
};

template <typename F>
class TrapezoidalRule : public IntegrationMethod<F> {
public:
    ~TrapezoidalRule() {}
    double Integrate(const F& f, double left,
                     double right, int n) const override {
        double res = 0;
        double x_1 = left;
        double diff = (right - left) / n;
        for (int i = 0; i <= n - 1; ++i) {
            double x_2 = x_1 + diff;
            res += (((f(x_1) + f(x_2)) / 2) * diff);
            x_1 = x_2;
        }
        return res;
    }
};

/* Usage example
 * 
int main() {
    using F = decltype(func);

    std::string input;
    std::cin >> input;
    std::unique_ptr<IntegrationMethod<F>> method;
    if (input == "rectangle")
        method.reset(new RectangleRule<F>);
    else
        method.reset(new TrapezoidalRule<F>);

    double x;
    double y;
    std::cin >> x >> y;

    int n;
    std::cin >> n;

    std::cout << method->Integrate(cos, x, y, n) << "\n";
    std::cout << method->Integrate(sin, x, y, n) << "\n";
}
*/