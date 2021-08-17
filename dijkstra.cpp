#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <climits>
#include <algorithm>
#include <tuple>


using namespace std;

struct edge {
public:
    int to, l;
};

const int64_t inf = numeric_limits<int64_t>::max();

int main() {
    int n, start, finish;
    cin >> n >> start >> finish;
    vector<vector<edge>> graph(n, vector<edge>());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int elem;
            cin >> elem;
            if (elem != -1 && i != j) {
                graph[i].push_back({j, elem});
            }
        }
    }
    vector<int64_t> dist(n, inf);
    vector<int> prev(n, -1);
    set<pair<int64_t, int>> next;
    --start;
    --finish;
    dist[start] = 0;
    next.insert({0, start});
    while (!next.empty()) {
        auto it = next.begin();
        int curr = it->second;
        next.erase(it);
        for (int i = 0; i < graph[curr].size(); ++i) {
            auto to = graph[curr][i].to;
            auto len = graph[curr][i].l;
            int64_t better = dist[curr] + len;
            if (better < dist[to]) {
                auto ptr = next.find({dist[to], to});
                if (ptr != next.end()) {
                    next.erase(ptr);
                }
                prev[to] = curr;
                dist[to] = better;
                next.insert({dist[to], to});
            }
        }
    }
    if (dist[finish] == inf) {
        cout << "-1\n";
    } else {
        vector<int> res;
        int v = finish;
        while (v != -1) {
            res.push_back(v);
            v = prev[v];
        }
        reverse(res.begin(), res.end());
        for (auto elem : res) {
            cout << elem + 1 << ' ';
        }
        cout << '\n';
    }
}