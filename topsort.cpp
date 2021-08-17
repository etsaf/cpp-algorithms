#include <iostream>
#include <vector>

using namespace std;

bool dfs(int now, vector<vector<int>>& g, vector<int>& v, vector<int>& res) {
    v[now] = 1;
    for (int neig : g[now]) {
        if (v[neig] == 1) {
            return true;
        }
        if (!v[neig] && dfs(neig, g, v, res)) {
            return true;
        }
    }
    v[now] = 2;
    res.push_back(now);
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>());
    int x, y;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
    }
    vector<int> result;
    bool has_cycle = false;
    vector<int> visited(n + 1, 0);
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i]) {
            if (dfs(i, graph, visited, result)) {
                has_cycle = true;
                break;
            }
        }
    }
    if (has_cycle) {
        cout << "-1" << '\n';
    } else {
        for (auto i = result.rbegin(); i != result.rend(); ++i) {
            cout << *i << ' ';
        }
        cout << '\n';
    }
}