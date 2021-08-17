#include <iostream>
#include <vector>

using namespace std;

void dfs(int comp, int now, vector<vector<int>>& g, vector<int>& v) {
    v[now] = comp;
    for (int neig : g[now]) {
        if (!v[neig]) {
            dfs(comp, neig, g, v);
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
    int curr = 0;
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i]) {
            ++curr;
            dfs(curr, i, graph, visited);
        }
    }
    cout << curr << '\n';
    vector<vector<int>> component(curr + 1, vector<int>());
    for (int i = 1; i < n + 1; ++i) {
        if (visited[i]) {
            component[visited[i]].push_back(i);
        }
    }
    for (auto elem : component) {
        auto s = elem.size();
        if (s) {
            cout << s << '\n';
            for (auto x : elem) {
                cout << x << ' ';
            }
            cout << '\n';
        }
    }
}