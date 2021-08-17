/* two queries: 1. in range [L, R] find smallest element larger than given
2. change one element */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <climits>
#include <cmath>
#include <set>
#include <map>
#include <iterator>

using namespace std;

int maxx = INT_MAX;

vector<map<int, int>> tree;
vector<int> a;


void construct(vector<int>& a, int left, int right, int ind) {
    if (left > right)
        return;
    if (left == right) {
        ++tree[ind][a[left]];
        return;
    }
    int mid = (left + right) / 2;
    construct(a, left, mid, ind * 2 + 1);
    construct(a, mid + 1, right, ind * 2 + 2);
    for (auto it = tree[ind * 2 + 1].begin(); it != tree[ind * 2 + 1].end(); ++it) {
        tree[ind][it->first] += it->second;
    }
    for (auto it = tree[ind * 2 + 2].begin(); it != tree[ind * 2 + 2].end(); ++it) {
        tree[ind][it->first] += it->second;
    }
}

void construct_from_vec(vector<int>& a, int n) {
    int p = (int)(ceil(log2(n)));
    int tree_size = 2 * (int)pow(2, p) - 1;
    tree.resize(tree_size, map<int, int>());
    construct(a, 0, n - 1, 0);
}

void update(int ind, int tree_l, int tree_r, int asked, int new_elem) {
    while (true) {
        --tree[ind][a[asked]];
        if (!tree[ind][a[asked]])
            tree[ind].erase(a[asked]);
        ++tree[ind][new_elem];
        if (tree_l == tree_r) {
            a[asked] = new_elem;
            return;
        }
        int mid = (tree_l + tree_r) / 2;
        if (asked <= mid) {
            ind = ind * 2 + 1;
            tree_r = mid;
        } else {
            ind = ind * 2 + 2;
            tree_l = mid + 1;
        }
    }
}

void update_vec(int n, int asked, int new_elem) {
    update(0, 0, n - 1, asked, new_elem);
}

int elem(int x, int tree_l, int tree_r, int asked_l, int asked_r, int ind) {
    if (tree_l > tree_r || tree_l > asked_r || tree_r < asked_l)
        return maxx;
    if (tree_l >= asked_l && tree_r <= asked_r) {
        auto ptr = tree[ind].upper_bound(x);
        if (ptr == tree[ind].end())
            return maxx;
        return ptr->first;
    }
    int mid = (tree_l + tree_r) / 2;
    return min(elem(x, tree_l, mid, asked_l, asked_r, 2 * ind + 1),
               elem(x, mid + 1, tree_r, asked_l, asked_r, 2 * ind + 2));
}

int get_elem(int n, int asked_l, int asked_r, int x) {
    return elem(x, 0, n - 1, asked_l, asked_r, 0);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int e;
        cin >> e;
        a.push_back(e);
    }
    int q;
    cin >> q;
    construct_from_vec(a, n);
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int left, right, x;
            cin >> left >> right >> x;
            int ans = get_elem(n, left, right, x);
            if (ans == maxx)
                cout << "NONE\n";
            else
                cout << ans << '\n';
        } else {
            int ind, value;
            cin >> ind >> value;
            update_vec(n, ind, value);
        }

    }
}