//find weight of shortest path from 1 to n

#include <iostream>
#include <vector>
#include <map>

using namespace std;
const int64_t inf = numeric_limits<int64_t>::max();

//weight of each edge is determined by formula
int64_t weight(int from, int to) {
    return (179 * from + 719 * to) % 1000 - 500;
}

int main() {
    int n;
    cin >> n;
    vector<int64_t> d(n + 1, inf);
    d[1] = 0;
    for (int i = 0; i < n - 1; ++i) {
        bool change = false;
        for (int from = 1; from < n + 1; ++from) {
            for (int to = from + 1; to < n + 1; ++to) {
                if (d[from] != inf && d[from] + weight(from, to) < d[to]) {
                    d[to] = d[from] + weight(from, to);
                    change = true;
                }
            }
        }
        if (!change) {
            break;
        }
    }
    cout << d[n] << '\n';
}