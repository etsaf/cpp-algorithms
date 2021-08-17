#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void prime(int64_t n) {
    while (!(n % 2)) {
        cout << 2 << ' ';
        n = n / 2;
    }
    for (int64_t i = 3; i * i <= n; i = i + 2) {
        while (!(n % i)) {
            cout << i << ' ';
            n = n / i;
        }
    }
    if (n > 2)
        cout << n;
}

int main() {
    int64_t n;
    cin >> n;
    prime(n);
    cout << '\n';
}
