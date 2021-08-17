#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <climits>

using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;
    char color;
};

class part {
public:
    int data;
    int left;
    int right;
    char color;
};

map<int, part> parts;
bool red_black = true;

class bst {
    node* root;

    node* build (int num, node* to) {
        to = new node;
        int data, left, right;
        char color;
        data = parts[num].data;
        left = parts[num].left;
        right = parts[num].right;
        color = parts[num].color;
        to->data = data;
        to->left = nullptr;
        to->right = nullptr;
        to->color = color;
        if (left != -1) {
            to->left = build(left, to->left);
        }
        if (right != -1) {
            to->right = build(right, to->right);
        }
        return to;
    }

    node* clear(node* n) {
        if (n == nullptr) {
            return nullptr;
        }
        clear(n->left);
        clear(n->right);
        delete n;
        return nullptr;
    }

    void inorder(node* n) {
        if (n == nullptr) {
            return;
        }
        inorder(n->left);
        cout << n->data << '\n';
        inorder(n->right);
    }

    int black_height(node* n) {
        if (n == nullptr) {
            return 0;
        }
        if (n->left != nullptr) {
            if (n->left->data >= n->data)
                red_black = false;
            if (n->color == 'R' && n->left->color == 'R')
                red_black = false;
        }
        if (n->right != nullptr) {
            if (n->right->data <= n->data)
                red_black = false;
            if (n->color == 'R' && n->right->color == 'R')
                red_black = false;
        }
        int left_b = black_height(n->left);
        int right_b = black_height(n->right);
        if (left_b != right_b) {
            red_black = false;
        }
        if (n->color == 'B') {
            return left_b + 1;
        } else {
            return left_b;
        }
    }

    bool is_bst(node* n, int min, int max) {
        if (n == nullptr) {
            return true;
        }
        if (n->data < min || n->data > max)
            return false;
        return (is_bst(n->left, min, n->data - 1) &&
                is_bst(n->right, n->data + 1, max));
    }

public:
    bst() {
        root = nullptr;
    }

    ~bst() {
        root = clear(root);
    }

    void build(int num) {
        root = build(num, root);
    }

    void inorder() {
        inorder(root);
    }

    bool is_bst() {
        return is_bst(root, INT_MIN, INT_MAX);
    }

    void black_height() {
        black_height(root);
    }
};


int main() {
    bst tree;
    // tree size
    int n;
    cin >> n;
    if (!n) {
        cout << "YES\n";
        return 0;
    }
    int root;
    cin >> root;
    // vertex descriptions: Number Key Left Right Color
    for (int i = 0; i < n; ++i) {
        int num, key, left, right;
        char color;
        string sleft;
        string sright;
        cin >> num >> key >> sleft >> sright >> color;
        if (sleft == "null")
            left = -1;
        else
            left = stoi(sleft);
        if (sright == "null")
            right = -1;
        else
            right = stoi(sright);
        parts[num] = {key, left, right, color};
        if (num == root && color != 'B') {
            cout << "NO\n";
            return 0;
        }
    }
    tree.build(root);
    if (!tree.is_bst()) {
        cout << "NO\n";
        return 0;
    }
    tree.black_height();
    if (!red_black)
        cout << "NO\n";
    else
        cout << "YES\n";
}