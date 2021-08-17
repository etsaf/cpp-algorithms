#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        a = a % b;
        swap(a, b);
    }
    return a;
}

int main() {
    int64_t a, b;
    cin >> a >> b;
    cout << gcd(a, b) << '\n';
}