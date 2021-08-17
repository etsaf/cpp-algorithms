/* Swapper is a structure that can swap x and x + 1, x + 2 and x + 3, etc
in a range of even length [x, y] and find sum of all numbers in a range */

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
    int64_t subtree, y, data;
    int64_t summ;
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

int64_t subtree(node* at) {
    if (at == nullptr) {
        return 0;
    } else {
        return at->subtree;
    }
}

int64_t summ(node* at) {
    if (at == nullptr) {
        return 0;
    } else {
        return at->summ;
    }
}

void new_values(node* at) {
    if (at) {
        at->subtree = subtree(at->left) + subtree(at->right) + 1;
        at->summ = summ(at->left) + at->data + summ(at->right);
    }
}

pair<node*, node*> split(int64_t x, node* at) {
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

pair<node*, node*> swap_node(node* root1, node* root2, int64_t left, int64_t right) {
    int64_t left1 = (left + 1) / 2;
    int64_t right1 = right / 2;
    int64_t left2 = left / 2;
    int64_t right2 = (right + 1) / 2 - 1;
    auto [L0, R1] = split(right1 + 1, root1);
    auto [L1, M1] = split(left1, L0);
    auto [L00, R2] = split(right2 + 1, root2);
    auto [L2, M2] = split(left2, L00);
    return {merge(merge(L1, M2), R1), merge(merge(L2, M1), R2)};
}

pair<node*, node*> find_summ(node* root1, node* root2, int64_t left, int64_t right) {
    if (left == right) {
        if (left % 2 == 0) {
            int64_t left1 = (left + 1) / 2;
            int64_t right1 = right / 2;
            auto [L0, R1] = split(right1 + 1, root1);
            auto [L1, M1] = split(left1, L0);
            cout << M1->summ << '\n';
            return {merge(merge(L1, M1), R1), root2};
        } else {
            int64_t left2 = left / 2;
            int64_t right2 = (right + 1) / 2 - 1;
            auto [L00, R2] = split(right2 + 1, root2);
            auto [L2, M2] = split(left2, L00);
            cout << M2->summ << '\n';
            return {root1, merge(merge(L2, M2), R2)};
        }
    }
    int64_t left1 = (left + 1) / 2;
    int64_t right1 = right / 2;
    int64_t left2 = left / 2;
    int64_t right2 = (right + 1) / 2 - 1;
    int64_t s1, s2, s;
    auto [L0, R1] = split(right1 + 1, root1);
    auto [L1, M1] = split(left1, L0);
    s1 = M1->summ;
    auto [L00, R2] = split(right2 + 1, root2);
    auto [L2, M2] = split(left2, L00);
    s2 = M2->summ;
    s = s1 + s2;
    cout << s << '\n';
    return {merge(merge(L1, M1), R1), merge(merge(L2, M2), R2)};
}

int main() {
    int64_t n, m;
    cin >> n >> m;
    int64_t k = 1;
    while (!(m == 0 && n == 0)) {
        node* treap_even = nullptr;
        node* treap_odd = nullptr;
        for (int64_t i = 1; i < n + 1; ++i) {
            int64_t v;
            cin >> v;
            node* add = new node;
            add->subtree = 1;
            add->y = rand();
            add->data = v;
            add->left = nullptr;
            add->right = nullptr;
            add->summ = v;
            if (i % 2 == 0) {
                treap_even = merge(treap_even, add);
            } else {
                treap_odd = merge(treap_odd, add);
            }
        }
        cout << "Swapper " << k << ":" << '\n';
        for (int64_t i = 0; i < m; ++i) {
            int64_t num;
            int64_t left, right;
            cin >> num >> left >> right;
            --left;
            --right;
            if (num == 1) {
                auto [t1, t2] = swap_node(treap_odd, treap_even,  left, right);
                treap_odd = t1;
                treap_even = t2;
            } else {
                auto [t1, t2] = find_summ(treap_odd, treap_even,  left, right);
                treap_odd = t1;
                treap_even = t2;
            }
        }
        cout << '\n';
        clear(treap_even);
        clear(treap_odd);
        cin >> n >> m;
        ++k;
    }
}