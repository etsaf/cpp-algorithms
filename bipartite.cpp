#include <iostream>
#include <vector>

using namespace std;

void dfs(int color, int now, vector<vector<int>>& g,
         vector<int>& v, bool& can_color) {
    v[now] = color;
    for (int neig : g[now]) {
        if (!v[neig]) {
            dfs(3 - color, neig, g, v, can_color);
        } else if (v[neig] == color) {
            can_color = false;
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
    vector<int> visited(n + 1, 0);
    bool can_color = true;
    for (int i = 1; i < n + 1; ++i) {
        if (!can_color) {
            break;
        }
        if (!visited[i]) {
            dfs(1, i, graph, visited, can_color);
        }
    }
    if (can_color) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }
}