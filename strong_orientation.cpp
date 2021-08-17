//prints orientation of each edge from input list
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <map>
#include <set>

using namespace std;
map<pair<int, int>, int> doubled;

void dfs(int now, vector<vector<pair<int, int>>>& g, int prev, vector<bool>& v, int& t, vector<int>& times,
         vector<int>& least, int& bridges, vector<pair<int, int>>& result) {
    v[now] = true;
    ++t;
    times[now] = t;
    least[now] = t;
    for (auto [neig, num] : g[now]) {
        if (neig == prev) {
            continue;
        }
        if (v[neig]) {
            least[now] = min(least[now], times[neig]);
            result[num] = {neig, now};
        } else {
            if (doubled.find({now, neig}) != doubled.end()) {
                if (doubled[{now, neig}] == 0) {
                    result[num] = {now, neig};
                    doubled[{now, neig}] = 1;
                } else {
                    result[num] = {neig, now};
                }
            } else {
                result[num] = {now, neig};
            }
            dfs(neig, g, now, v, t, times, least, bridges, result);
            least[now] = min(least[now], least[neig]);
            if (least[neig] > times[now]) {
                if (doubled.find({now, neig}) == doubled.end()) {
                    ++bridges;
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    map<pair<int, int>, int> edges;
    vector<vector<pair<int, int>>> graph(n + 1, vector<pair<int, int>>());
    vector<pair<int, int>> result(m + 1, {-1, -1});
    int x, y;
    for (int i = 1; i < m + 1; ++i) {
        cin >> x >> y;
        graph[x].push_back({y, i});
        if (x != y) {
            graph[y].push_back({x, i});
        }
        if (edges.find({x, y}) != edges.end()) {
            doubled[{x, y}] = 0;
            doubled[{y, x}] = 0;
        }
        edges[{x, y}] = i;
        edges[{y, x}] = i;
    }
    vector<bool> visited(n + 1, false);
    int bridges = 0;
    int timer = 0;
    vector<int> times(n + 1, -1);
    vector<int> least(n + 1, -1);
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i]) {
            dfs(i, graph, -1, visited, timer, times, least, bridges, result);
        }
    }
    if (bridges) {
        cout << '0' << '\n';
    } else {
        for (int i = 1; i < result.size(); ++i) {
            auto [x, y] = result[i];
            cout << x << ' ' << y << '\n';
        }
    }
}