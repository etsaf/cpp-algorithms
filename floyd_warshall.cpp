#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> d(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int elem;
            cin >> elem;
            d[i][j] = elem;
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int from = 0; from < n; ++from) {
            for (int to = 0; to < n; ++to) {
                d[from][to] = min(d[from][to], d[from][k] + d[k][to]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << d[i][j] << ' ';
        }
        cout << '\n';
    }
}