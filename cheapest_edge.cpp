// finds the cheapest edge on a path between two vertices of a tree
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int64_t maxx = INT64_MAX;
vector<vector<int64_t>> up;
vector<vector<int64_t>> minn;
vector<int64_t> tin, tout;
int64_t deg;
int64_t cnt = 0;

struct vertex {
    vertex(int64_t d, int64_t e) {
        data = d;
        edge = e;
    }
    int64_t data;
    int64_t edge;
};

bool parent(int64_t u, int64_t v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

void dfs(vertex now, vector<vector<vertex>>& graph) {
    tin[now.data] = cnt;
    ++cnt;
    for (int64_t i = 1; i < deg; ++i) {
        up[now.data][i] = up[up[now.data][i - 1]][i - 1];
        minn[now.data][i] = min(minn[up[now.data][i - 1]][i - 1], minn[now.data][i - 1]);
    }
    for (auto neig : graph[now.data]) {
        up[neig.data][0] = now.data;
        minn[neig.data][0] = neig.edge;
        dfs(neig, graph);
    }
    tout[now.data] = cnt;
    ++cnt;
}

int64_t least_ancestor(int64_t u, int64_t v) {
    int64_t u1 = u;
    int64_t min1 = maxx;
    int64_t min2 = maxx;
    int64_t min3 = minn[u][0];
    int64_t min4 = minn[v][0];
    if (parent(u, v)) {
        for (int64_t p = deg - 1; p > -1; --p) {
            if (!parent(up[v][p], u)) {
                min2 = min(min2, minn[v][p]);
                v = up[v][p];
            }
        }
        min2 = min(min2, min4);
        return min(min2, minn[v][0]);
    }
    if (parent(v, u)) {
        for (int64_t p = deg - 1; p > -1; --p) {
            if (!parent(up[u][p], v)) {
                min2 = min(min2, minn[u][p]);
                u = up[u][p];
            }
        }
        min2 = min(min2, min3);
        return min(min2, minn[u][0]);
    }
    for (int64_t p = deg - 1; p > -1; --p) {
        if (!parent(up[u][p], v)) {
            min1 = min(min1, minn[u][p]);
            u = up[u][p];
        }
    }
    for (int64_t p = deg - 1; p > -1; --p) {
        if (!parent(up[v][p], u1)) {
            min2 = min(min2, minn[v][p]);
            v = up[v][p];
        }
    }
    int64_t least = min(min1, min2);
    least = min(least, minn[v][0]);
    least = min(least, min3);
    least = min(least, min4);
    return min(least, minn[u][0]);
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
    vector<vector<vertex>> graph(n, vector<vertex>());
    for (int64_t i = 1; i < n; ++i) {
        int64_t e, w;
        cin >> e >> w;
        --e;
        graph[e].push_back(vertex(i, w));
    }
    int64_t m;
    cin >> m;
    tin = vector<int64_t>(n, 0);
    tout = vector<int64_t>(n, 0);
    deg = recursive_log(n);
    up = vector<vector<int64_t>>(n, vector<int64_t>(deg, 0));
    minn = vector<vector<int64_t>>(n, vector<int64_t>(deg, maxx));
    dfs(vertex(0, 0), graph);
    int64_t x, y;
    for (int64_t i = 0; i < m; ++i) {
        cin >> x >> y;
        --x;
        --y;
        cout << least_ancestor(x, y) << '\n';
    }
}