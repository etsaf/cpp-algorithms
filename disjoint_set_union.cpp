// unite set of points on a plane adding edges with least length sum
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;
const int inf = numeric_limits<int>::max();
vector<int> prevs;
vector<int> ranks;

struct edge {
public:
    int from, to;
    double l;
    bool operator<(edge rhs) const {
        return this->l < rhs.l;
    }
};

struct point {
public:
    int x, y;
};

double dist(point a, point b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int find(int x) {
    if (x == prevs[x]) {
        return x;
    }
    return prevs[x] = find(prevs[x]);
}

void unite(int lhs, int rhs) {
    int lr = find(lhs);
    int rr = find(rhs);
    if (lr != rr) {
        if (ranks[lr] >= ranks[rr]) {
            prevs[rr] = lr;
        } else {
            prevs[lr] = rr;
        }
        if (ranks[lr] == ranks[rr]) {
            ++ranks[lr];
        }
    }
}

int main() {
    int n, m;
    cin >> n;
    vector<edge> graph;
    vector<vector<double>> g(n, vector<double>(n, inf));
    vector<point> points;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        points.push_back({x, y});
        for (int j = 0; j < points.size(); ++j) {
            g[i][j] = dist(points[i], points[j]);
            g[j][i] = dist(points[i], points[j]);
        }
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        --from;
        --to;
        g[from][to] = 0;
        g[to][from] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            graph.push_back({i, j, g[i][j]});
        }
    }
    sort(graph.begin(), graph.end());
    for (int i = 0; i < graph.size(); ++i) {
        prevs.push_back(i);
        ranks.push_back(0);
    }
    double res = 0.0;
    for (auto e : graph) {
        if (find(e.from) != find(e.to)) {
            res += e.l;
            unite(e.from, e.to);
        }
    }
    cout << setprecision(7) << res << '\n';
}