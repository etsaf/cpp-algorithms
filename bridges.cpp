#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;
set<pair<int, int>> doubled;

void dfs(int now, vector<vector<int>>& g, int prev, vector<bool>& v, int& t, vector<int>& times,
         vector<int>& least, set<int>& bridges, map<pair<int, int>, int>& edges) {
    v[now] = true;
    ++t;
    times[now] = t;
    least[now] = t;
    for (int neig : g[now]) {
        if (neig == prev) {
            continue;
        }
        if (v[neig]) {
            least[now] = min(least[now], times[neig]);
        } else {
            dfs(neig, g, now, v, t, times, least, bridges, edges);
            least[now] = min(least[now], least[neig]);
            if (least[neig] > times[now]) {
                if (doubled.find({now, neig}) == doubled.end()) {
                    bridges.insert(edges[{now, neig}]);
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    map<pair<int, int>, int> edges;
    vector<vector<int>> graph(n + 1, vector<int>());
    int x, y;
    for (int i = 1; i < m + 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        if (x != y) {
            graph[y].push_back(x);
        }
        if (edges.find({x, y}) != edges.end()) {
            doubled.insert({x, y});
            doubled.insert({y, x});
        }
        edges[{x, y}] = i;
        edges[{y, x}] = i;
    }
    vector<bool> visited(n + 1, false);
    set<int> bridges;
    int timer = 0;
    vector<int> times(n + 1, -1);
    vector<int> least(n + 1, -1);
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i]) {
            dfs(i, graph, -1, visited, timer, times, least, bridges, edges);
        }
    }
    cout << bridges.size() << '\n';
    for (auto elem : bridges) {
        cout << elem << ' ';
    }
    cout << '\n';
}