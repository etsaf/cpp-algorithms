#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using namespace std;

vector<vector<int64_t>> up;
vector<int64_t> tin, tout;
int64_t deg;
int64_t cnt = 0;

bool parent(int64_t u, int64_t v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

void dfs(int64_t now, vector<vector<int64_t>>& graph) {
    tin[now] = cnt;
    ++cnt;
    for (int64_t i = 1; i < deg; ++i)
        up[now][i] = up[up[now][i - 1]][i - 1];
    for (auto neig : graph[now]) {
        up[neig][0] = now;
        dfs(neig, graph);
    }
    tout[now] = cnt;
    ++cnt;
}

int64_t least_ancestor(int64_t u, int64_t v) {
    if (parent(u, v)) {
        return u;
    }
    if (parent(v, u)) {
        return v;
    }
    for (int64_t p = deg - 1; p > -1; --p) {
        if (!parent(up[u][p], v))
            u = up[u][p];
    }
    return up[u][0];
}

int64_t recursive_log(int64_t elem) {
    if (elem == 1)
        return 0;
    if (elem % 2 == 0)
        return recursive_log(elem / 2) + 1;
    else
        return recursive_log(elem / 2 + 1) + 1;
}

int main() {
    int64_t n;
    cin >> n;
    int64_t m;
    cin >> m;
    vector<vector<int64_t>> graph(n, vector<int64_t>());
    for (int64_t i = 1; i < n; ++i) {
        int64_t e;
        cin >> e;
        graph[e].push_back(i);
    }
    tin = vector<int64_t>(n, 0);
    tout = vector<int64_t>(n, 0);
    deg = recursive_log(n);
    up = vector<vector<int64_t>>(n, vector<int64_t>(deg, 0));
    dfs(0, graph);
    int64_t res = 0;
    int64_t a1, a2;
    cin >> a1 >> a2;
    int64_t x, y, z;
    cin >> x >> y >> z;
    int64_t lca = 0;
    for (int64_t i = 0; i < m; ++i) {
        lca = least_ancestor((a1 + lca) % n, a2);
        res += lca;
        int64_t next1, next2;
        next1 = (x * a1 + y * a2 + z) % n;
        next2 = (x * a2 + y * next1 + z) % n;
        a1 = next1;
        a2 = next2;
    }
    cout << res << '\n';
}