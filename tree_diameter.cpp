#include <iostream>
#include <vector>

using namespace std;

void dfs(int now, vector<vector<int>>& g, vector<bool>& v,
         int path_len, int& max_len, int& max_vert) {
    v[now] = true;
    if (max_len < path_len) {
        max_len = path_len;
        max_vert = now;
    }
    for (int neig : g[now]) {
        if (!v[neig]) {
            dfs(neig, g, v, path_len + 1, max_len, max_vert);
        }
    }
}

int main() {
    int n;
    cin >> n;
    int m = n - 1;
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
    int max_len, max_vert;
    max_len = -1;
    max_vert = -1;
    dfs(1, graph, visited, 0, max_len, max_vert);
    max_len = -1;
    for (int i = 1; i < n + 1; ++i) {
        visited[i] = 0;
    }
    dfs(max_vert, graph, visited, 0, max_len, max_vert);
    cout << max_len << '\n';
}