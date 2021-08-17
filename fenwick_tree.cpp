//can update elements one by one
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <climits>
#include <cmath>

using namespace std;

int64_t maxx = 1000000007;

int64_t pref(int ind, vector<int64_t>& t) {
    int64_t sum = 0;
    while (ind >= 0) {
        sum += t[ind];
        ind = (ind & (ind + 1)) - 1;
    }
    return sum;
}

int64_t range_sum(int64_t lt, int64_t rt, vector<int64_t>& t) {
    return pref(rt, t) - pref(lt - 1, t);
}

void change(int ind, int64_t by, vector<int64_t>& t, int n) {
    while (ind < n) {
        t[ind] += by;
        ind = (ind | (ind + 1));
    }
}

int main() {
    int64_t n = 0;
    cin >> n;
    vector<int64_t> t(n, 0);
    vector<int64_t> a;
    for (int64_t i = 0; i < n; ++i) {
        int64_t k;
        cin >> k;
        a.push_back(k);
        change(i, k, t, n);
    }
    int64_t q;
    cin >> q;
    for (int64_t i = 0; i < q; ++i) {
        int64_t tj, left, right, ind, next;
        cin >> tj;
        if (tj == 1) {
            cin >> left >> right;
            cout << range_sum(left, right, t) << '\n';
        } else {
            cin >> ind >> next;
            change(ind, next - a[ind], t, n);
            a[ind] = next;
        }
    }
}