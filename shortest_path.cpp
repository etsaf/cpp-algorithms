#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1, vector<int>());
    int x;
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            cin >> x;
            if (x) {
                graph[i].push_back(j);
            }
        }
    }
    int start, finish;
    cin >> start >> finish;
    deque<int> next;
    vector<bool> visited(n + 1, false);
    vector<int> prev(n + 1, 0);
    vector<int> path(n + 1, 0);
    visited[start] = true;
    prev[start] = -1;
    next.push_back(start);
    while (!next.empty()) {
        int a = next.front();
        next.pop_front();
        for (auto neig : graph[a]) {
            if (!visited[neig]) {
                visited[neig] = true;
                prev[neig] = a;
                next.push_back(neig);
                path[neig] = path[a] + 1;
            }
        }
    }
    if (!visited[finish]) {
        cout << "-1" << '\n';
    } else if (path[finish] == 0){
        cout << path[finish] << '\n';
    } else {
        vector<int> result;
        cout << path[finish] << '\n';
        int curr = finish;
        while (curr != -1) {
            result.push_back(curr);
            curr = prev[curr];
        }
        reverse(result.begin(), result.end());
        for (auto elem : result) {
            cout << elem << ' ';
        }
        cout << '\n';
    }
}