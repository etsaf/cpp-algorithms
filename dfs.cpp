//prints component of the first vertex
#include <iostream>
#include <vector>

using namespace std;

void dfs(int now, vector<vector<int>>& g, vector<bool>& v) {
    v[now] = true;
    for (int neig : g[now]) {
        if (!v[neig]) {
            dfs(neig, g, v);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>());
    int x, y;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        if (x != y) {
            graph[y].push_back(x);
        }
    }
    vector<bool> visited(n + 1, 0);
    dfs(1, graph, visited);
    int res = 0;
    vector<int> component;
    for (int i = 0; i < n + 1; ++i) {
        if (visited[i]) {
            ++res;
            component.push_back(i);
        }
    }
    cout << res << '\n';
    for (int i = 0; i < component.size(); ++i) {
        if (i == component.size() - 1) {
            cout << component[i] << '\n';
        } else {
            cout << component[i] << ' ';
        }
    }
}

