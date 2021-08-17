// prints weight of minimum spanning tree
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


using namespace std;
const int inf = numeric_limits<int>::max();
vector<int> prevs;
vector<int> ranks;

struct edge {
public:
    int from, to, l;
    bool operator<(edge rhs) const {
        return this->l < rhs.l;
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

int main() {
    int n, m;
    cin >> n >> m;
    vector<edge> graph;
    for (int i = 0; i < m; ++i) {
        int from, to, l;
        cin >> from >> to >> l;
        --from;
        --to;
        graph.push_back({from, to, l});
    }
    sort(graph.begin(), graph.end());
    for (int i = 0; i < n; ++i) {
        prevs.push_back(i);
        ranks.push_back(0);
    }
    int64_t res = 0;
    for (auto e : graph) {
        if (find(e.from) != find(e.to)) {
            res += e.l;
            unite(e.from, e.to);
        }
    }
    cout << res << '\n';
}