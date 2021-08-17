//finds all articulation points
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

void dfs(int now, vector<vector<int>>& g, int prev, vector<bool>& v, int& t, vector<int>& times,
         vector<int>& least, set<int>& points) {
    v[now] = true;
    ++t;
    times[now] = t;
    least[now] = t;
    int branches = 0;
    for (int neig : g[now]) {
        if (neig == prev) {
            continue;
        }
        if (v[neig]) {
            least[now] = min(times[neig], least[now]);
        } else {
            dfs(neig, g, now, v, t, times, least, points);
            ++branches;
            least[now] = min(least[neig], least[now]);
            if (prev != -1 && least[neig] >= times[now]) {
                points.insert(now);
            }
        }
    }
    if (prev == -1) {
        if (branches > 1) {
            points.insert(now);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>());
    int x, y;
    for (int i = 1; i < m + 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        if (x != y) {
            graph[y].push_back(x);
        }
    }
    vector<bool> visited(n + 1, false);
    set<int> points;
    int timer = 0;
    vector<int> times(n + 1, -1);
    vector<int> least(n + 1, -1);
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i]) {
            dfs(i, graph, -1, visited, timer, times, least, points);
        }
    }
    cout << points.size() << '\n';
    for (auto elem : points) {
        cout << elem << '\n';
    }
}