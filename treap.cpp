/* treap (cartesian tree) that can reverse range [L, R] in the array
and find minimum in range [L, R] */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <climits>
#include <cmath>

using namespace std;

int maxx = INT_MAX;

int generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);
    return distrib(gen);
}

class node {
public:
    int subtree, y, data, least;
    bool invert = false;
    node* left;
    node* right;
};

node* clear(node* n) {
    if (n == nullptr) {
        return nullptr;
    }
    clear(n->left);
    clear(n->right);
    delete n;
    return nullptr;
}

void push(node* at) {
    if (at && at->invert) {
        at->invert = false;
        swap(at->left, at->right);
        if (at->left) {
            at->left->invert ^= 1;
        }
        if (at->right) {
            at->right->invert ^= 1;
        }
    }
}

void inorder(node* n) {
    if (n == nullptr) {
        return;
    }
    inorder(n->left);
    cout << n->data << ' ';
    inorder(n->right);
}

int subtree(node* at) {
    if (at == nullptr) {
        return 0;
    } else {
        return at->subtree;
    }
}

int least(node* at) {
    if (at == nullptr) {
        return maxx;
    } else {
        return at->least;
    }
}

void new_values(node* at) {
    if (at) {
        at->subtree = subtree(at->left) + subtree(at->right) + 1;
        at->least = min(at->data, least(at->left));
        at->least = min(at->least, least(at->right));
    }
}

pair<node*, node*> split(int x, node* at) {
    if (at == nullptr) {
        return {nullptr, nullptr};
    }
    push(at);
    if (x > subtree(at->left)) {
        auto [L, R] = split(x - subtree(at->left) - 1, at->right);
        at->right = L;
        new_values(at);
        return {at, R};
    } else {
        auto [L, R] = split(x, at->left);
        at->left = R;
        new_values(at);
        return {L, at};
    }
}

node* merge(node* L, node* R) {
    push(L);
    push(R);
    if (L == nullptr) {
        return R;
    }
    if (R == nullptr) {
        return L;
    }
    if (L->y > R->y) {
        L->right = merge(L->right, R);
        new_values(L);
        return L;
    }
    else {
        R->left = merge(L, R->left);
        new_values(R);
        return R;
    }
}

node* reverse(node* root, int left, int right) {
    auto [L1, R] = split(right + 1, root);
    auto [L, M] = split(left, L1);
    M->invert = true;
    return merge(L, merge(M, R));
}

node* find_min(node* root, int left, int right) {
    auto [L1, R] = split(right + 1, root);
    auto [L, M] = split(left, L1);
    cout << M->least << '\n';
    return merge(merge(L, M), R);
}

int main() {
    int n, m;
    cin >> n >> m;
    node* treap = nullptr;
    for (int i = 1; i < n + 1; ++i) {
        int v;
        cin >> v;
        node* add = new node;
        add->subtree = 1;
        add->y = rand();
        add->data = v;
        add->left = nullptr;
        add->right = nullptr;
        add->least = v;
        treap = merge(treap, add);
    }
    for (int i = 0; i < m; ++i) {
        int num;
        int left, right;
        cin >> num >> left >> right;
        --left;
        --right;
        if (num == 1)
            treap = reverse(treap, left, right);
        else
            treap = find_min(treap, left, right);
    }
}