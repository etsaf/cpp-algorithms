#include <iostream>
#include <vector>
#include <map>

using namespace std;
const int64_t inf = numeric_limits<int64_t>::max();

struct edge {
    int from;
    int to;
    int weight;
};

int main() {
    int n;
    cin >> n;
    vector<int64_t> d(n, inf);
    vector<int> prev(n, -1);
    vector<edge> edges;
    d[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w;
            cin >> w;
            if (w != 100000) {
                edges.push_back({i, j, w});
            }
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        for (auto e : edges) {
            if (d[e.from] != inf && d[e.from] + e.weight < d[e.to]) {
                d[e.to] = d[e.from] + e.weight;
                prev[e.to] = e.from;
            }
        }
    }
    bool cycle = false;
    int start;
    for (auto e : edges) {
        if (d[e.from] != inf && d[e.from] + e.weight < d[e.to]) {
            start = e.to;
            cycle = true;
            break;
        }
    }
    if (!cycle) {
        cout << "NO\n";
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        start = prev[start];
    }
    vector<int> res;
    int curr = start;
    while (true) {
        res.push_back(curr);
        if (curr == start && res.size() > 1) {
            break;
        }
        curr = prev[curr];
    }
    reverse(res.begin(), res.end());
    cout << "YES\n";
    cout << res.size() << '\n';
    for (auto elem : res) {
        cout << elem + 1 << ' ';
    }
    cout << '\n';
}