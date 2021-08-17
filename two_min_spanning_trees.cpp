//find weights of two minum spanning trees
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;
const int64_t inf = numeric_limits<int64_t>::max();
vector<int> prevs;
vector<int> ranks;

struct edge {
public:
    int from, to, l;
    bool operator<(edge rhs) const {
        return tuple(l, from, to) < tuple(rhs.l, rhs.from, rhs.to);
    }
};

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

int64_t kruskal(set<edge>& g, int n) {
    prevs.clear();
    ranks.clear();
    for (int i = 0; i < n; ++i) {
        prevs.push_back(i);
        ranks.push_back(0);
    }
    int64_t res = 0;
    int number = 0;
    for (auto e : g) {
        if (find(e.from) != find(e.to)) {
            res += e.l;
            unite(e.from, e.to);
            ++number;
        }
    }
    if (number != n - 1) {
        return inf;
    }
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    set<edge> graph;
    for (int i = 0; i < m; ++i) {
        int from, to, l;
        cin >> from >> to >> l;
        --from;
        --to;
        graph.insert({from, to, l});
    }
    for (int i = 0; i < n; ++i) {
        prevs.push_back(i);
        ranks.push_back(0);
    }
    vector<edge> added;
    int64_t res = 0;
    for (auto e : graph) {
        if (find(e.from) != find(e.to)) {
            res += e.l;
            unite(e.from, e.to);
            added.push_back(e);
        }
    }
    int64_t next = inf;
    for (auto e : added) {
        graph.erase(e);
        int64_t curr = kruskal(graph, n);
        next = min(next, curr);
        graph.insert(e);
    }
    cout << res << ' ' << next << '\n';
}