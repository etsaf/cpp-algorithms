/* two types of queries: 1. sum of elements in range [L, R]
2. adding number X to each element in range [L, R] */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <climits>
#include <cmath>

using namespace std;

int maxx = INT_MAX;

vector<int64_t> tree;
vector<int64_t> update;


void construct(vector<int64_t>& a, int64_t left, int64_t right, int64_t ind) {
    if (left > right)
        return;
    if (left == right) {
        tree[ind] = a[left];
        return;
    }
    int64_t mid = (left + right) / 2;
    construct(a, left, mid, ind * 2 + 1);
    construct(a, mid + 1, right, ind * 2 + 2);
    tree[ind] = tree[ind * 2 + 1] + tree[ind * 2 + 2];
}

void construct_from_vec(vector<int64_t>& a, int64_t n) {
    int64_t p = (int64_t)(ceil(log2(n)));
    int64_t tree_size = 2 * (int64_t)pow(2, p) - 1;
    tree.resize(tree_size, 0);
    update.resize(tree_size, 0);
    construct(a, 0, n - 1, 0);
}


void update_range(int64_t ind, int64_t tree_l, int64_t tree_r, int64_t asked_l,
                  int64_t asked_r, int64_t diff) {
    if (update[ind] != 0) {
        tree[ind] += (tree_r - tree_l + 1) * update[ind];
        if (tree_l != tree_r) {
            update[ind * 2 + 1] += update[ind];
            update[ind * 2 + 2] += update[ind];
        }
        update[ind] = 0;
    }
    if (tree_l > tree_r || tree_l > asked_r || tree_r < asked_l)
        return;
    if (tree_l >= asked_l && tree_r <= asked_r) {
        tree[ind] += (tree_r - tree_l + 1) * diff;
        if (tree_l != tree_r) {
            update[ind * 2 + 1] += diff;
            update[ind * 2 + 2] += diff;
        }
        return;
    }
    int64_t mid = (tree_l + tree_r) / 2;
    update_range(ind * 2 + 1, tree_l, mid, asked_l, asked_r, diff);
    update_range(ind * 2 + 2, mid + 1, tree_r, asked_l, asked_r, diff);
    tree[ind] = tree[ind * 2 + 1] + tree[ind * 2 + 2];
}

void update_vec(int64_t n, int64_t asked_l, int64_t asked_r, int64_t diff) {
    update_range(0, 0, n - 1, asked_l, asked_r, diff);
}


int64_t summ(int64_t tree_l, int64_t tree_r, int64_t asked_l, int64_t asked_r, int64_t ind) {
    if (update[ind] != 0) {
        tree[ind] += (tree_r - tree_l + 1) * update[ind];
        if (tree_l != tree_r) {
            update[ind * 2 + 1] += update[ind];
            update[ind * 2 + 2] += update[ind];
        }
        update[ind] = 0;
    }
    if (tree_l > tree_r || tree_l > asked_r || tree_r < asked_l)
        return 0;
    if (tree_l >= asked_l && tree_r <= asked_r)
        return tree[ind];
    int64_t mid = (tree_l + tree_r) / 2;
    return summ(tree_l, mid, asked_l, asked_r, 2 * ind + 1) +
           summ(mid + 1, tree_r, asked_l, asked_r, 2 * ind + 2);
}

int64_t get_sum(int64_t n, int64_t asked_l, int64_t asked_r) {
    return summ(0, n - 1, asked_l, asked_r, 0);
}


int main() {
    vector<int64_t> a;
    int64_t n;
    cin >> n;
    for (int64_t i = 0; i < n; ++i) {
        int64_t e;
        cin >> e;
        a.push_back(e);
    }
    int64_t q;
    cin >> q;
    construct_from_vec(a, n);
    for (int64_t i = 0; i < q; ++i) {
        int64_t t, left, right, x;
        cin >> t >> left >> right;
        if (t == 1) {
            cout << get_sum(n, left, right) << '\n';
        } else {
            cin >> x;
            update_vec(n, left, right, x);
        }
    }
}