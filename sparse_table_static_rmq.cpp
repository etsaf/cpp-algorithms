#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <climits>
#include <cmath>

using namespace std;

int64_t maxx = 1000000007;
vector<int> logs;

int64_t range_max(int64_t lt, int64_t rt, const vector<vector<int64_t>>& table) {
    int ind = logs[rt - lt + 1];
    return max(table[ind][lt], table[ind][rt - (1 << ind) + 1]);
}

int main() {
    int64_t n;
    cin >> n;
    logs.push_back(0);
    logs.push_back(0);
    for (int i = 2; i < n + 2; ++i) {
        logs.push_back(logs[i / 2] + 1);
    }
    vector<vector<int64_t>> table(logs[n] + 1, vector<int64_t>(n, 0));
    for (int64_t i = 0; i < n; ++i) {
        int64_t k;
        cin >> k;
        table[0][i] = k;
    }
    for (int64_t i = 1; (1 << i) <= n; ++i) {
        for (int64_t j = 0; (j + (1 << i) - 1) < n; ++j) {
            table[i][j] = max(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
        }
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
        res_sum += (range_max(left, right, table) % maxx);
        res_sum %= maxx;
        x0 = (11173 * x1 + 1) % maxx;
        x1 = (11173 * x0 + 1) % maxx;
    }
    cout << res_sum % maxx << '\n';
}