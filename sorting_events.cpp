#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <numeric>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <climits>
#include <set>
#include <tuple>

using namespace std;
int inf = INT_MAX;

struct event {
public:
    int time;
    int type;
    bool operator<(const event& other) const {
        return tie(time, type) < tie(other.time, other.type);
    }
};

struct point {
public:
    int time;
    int number;
    bool operator<(const point& other) const {
        return tie(time, number) < tie(other.time, other.number);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    int left, right;
    vector<event> events;
    vector<point> points;
    vector<int> res(m, 0);
    unordered_map<int, vector<int>> dots;
    for (int i = 0; i < n; ++i) {
        cin >> left >> right;
        events.push_back({min(left, right), 0});
        events.push_back({max(left, right), 2});
    }
    for (int i = 0; i < m; ++i) {
        cin >> left;
        points.push_back({left, i});
    }
    sort(events.begin(), events.end());
    sort(points.begin(), points.end());
    int p = 0;
    int e = 0;
    int balance = 0;
    while (p < m) {
        while (true) {
            if (e == n * 2 || (events[e].time == points[p].time && events[e].type == 2) ||
                    events[e].time > points[p].time) {
                break;
            }
            if (events[e].type == 0) {
                ++balance;
            } else {
                --balance;
            }
            ++e;
        }
        res[points[p].number] = balance;
        ++p;
    }
    for (auto r : res) {
        cout << r << ' ';
    }
    cout << '\n';
}