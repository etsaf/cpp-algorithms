#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <climits>
#include <cmath>

using namespace std;

int64_t maxx = 1000000007;

int64_t range_sum(int64_t i, int64_t j, const vector<int64_t>& pref) {
    if (!i)
        return pref[j];
    return pref[j] - pref[i - 1];
}

int main() {
    int64_t n;
    cin >> n;
    vector<int64_t> a;
    vector<int64_t> pref;
    for (int64_t i = 0; i < n; ++i) {
        int64_t k;
        cin >> k;
        a.push_back(k);
        if (!i)
            pref.push_back(k);
        else
            pref.push_back(pref[i - 1] + k);
    }
    int64_t q;
    cin >> q;
    int64_t x0;
    cin >> x0;
    int64_t res_sum = 0;
    int64_t x1 = (11173 * x0 + 1) % maxx;
    for (int64_t i = 0; i < q; ++i) {
        int64_t left, right;
        left = min(x0 % n, x1 % n);
        right = max(x0 % n, x1 % n);
        res_sum += (range_sum(left, right, pref) % maxx);
        res_sum %= maxx;
        x0 = (11173 * x1 + 1) % maxx;
        x1 = (11173 * x0 + 1) % maxx;
    }
    cout << res_sum % maxx << '\n';
}