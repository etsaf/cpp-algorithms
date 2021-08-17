//find two elements with minimul difference in two sorted arrays

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <numeric>
#include <stack>
#include <algorithm>
#include <map>
#include <cmath>
#include <climits>

using namespace std;
int inf = INT_MAX;


int main() {
    int n;
    cin >> n;
    vector<int> first;
    vector<int> second;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        first.push_back(x);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> x;
        second.push_back(x);
    }
    int ptr1 = 0;
    int ptr2 = 0;
    int min_diff = inf;
    int min1;
    int min2;
    while (ptr1 < n && ptr2 < m) {
        if (abs(first[ptr1] - second[ptr2]) < min_diff) {
            min_diff = abs(first[ptr1] - second[ptr2]);
            min1 = first[ptr1];
            min2 = second[ptr2];
        }
        if (first[ptr1] < second[ptr2])
            ++ptr1;
        else
            ++ptr2;
    }
    cout << min1 << ' ' << min2 << '\n';
}