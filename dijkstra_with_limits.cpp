/* a truck needs to carry max number of items from point 0 to point (n - 1)
on road map in under 24 hours. Each road takes some amount of time in minutes and
has a limit on weight of the truck. The truck weights 3000 kg, each item weights 100 g
Find max number of items */

#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <climits>
#include <algorithm>
#include <tuple>


using namespace std;

const int64_t inf = numeric_limits<int64_t>::max();
int n, m;

int64_t djikstra(vector<vector<tuple<int, int64_t, int64_t>>>& graph, int weight) {
    int start = 0;
    int finish = n - 1;
    vector<int64_t> dist(n, inf);
    set<pair<int64_t, int>> next;
    dist[start] = 0;
    next.insert({0, start});
    while (!next.empty()) {
        auto it = next.begin();
        int curr = it->second;
        next.erase(it);
        for (auto [to, time, max] : graph[curr]) {
            if (weight > max) {
                continue;
            }
            int64_t better = dist[curr] + time;
            if (better < dist[to]) {
                auto ptr = next.find({dist[to], to});
                if (ptr != next.end()) {
                    next.erase(ptr);
                }
                dist[to] = better;
                next.insert({dist[to], to});
            }
        }
    }
    return dist[finish];
}

int main() {
    cin >> n >> m;
    vector<vector<tuple<int, int64_t, int64_t>>> graph(n, vector<tuple<int, int64_t, int64_t>>());
    for (int i = 0; i < m; ++i) {
        int from, to;
        int64_t time, weight;
        cin >> from >> to >> time >> weight;
        --from;
        --to;
        graph[from].push_back({to, time, weight});
        graph[to].push_back({from, time, weight});
    }
    int64_t lower = 3000000;
    int64_t upper = 1000000000 + lower + 1;
    int64_t mid;
    int64_t time;
    while (lower < upper - 1) {
        mid = (upper + lower) / 2;
        time = djikstra(graph, mid);
        if (time > 1440) {
            upper = mid;
        } else {
            lower = mid;
        }
    }
    cout << (lower - 3000000) / 100 << '\n';
}