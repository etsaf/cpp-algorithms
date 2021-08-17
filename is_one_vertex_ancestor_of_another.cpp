#include <iostream>
#include <vector>

using namespace std;

void dfs(int now, vector<vector<int>>& g, vector<bool>& v,
         vector<int>& tin, vector<int>& tout, int& c) {
    tin[now] = c;
    ++c;
    v[now] = true;
    for (int neig : g[now]) {
        if (!v[neig]) {
            dfs(neig, g, v, tin, tout, c);
        }
    }
    tout[now] = c;
    ++c;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1, vector<int>());
    int x;
    int root;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        if (!x) {
            root = i;
            continue;
        }
        graph[x].push_back(i);
        if (x != i) {
            graph[i].push_back(x);
        }
    }
    int m;
    cin >> m;
    vector<bool> visited(n + 1, false);
    vector<int> tin(n + 1, 0);
    vector<int> tout(n + 1, 0);
    int count = 0;
    dfs(root, graph, visited, tin, tout, count);
    vector<int> component;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (tin[u] <= tin[v] && tout[v] <= tout[u])
            cout << 1 << '\n';
        else
            cout << 0 << '\n';
    }
}