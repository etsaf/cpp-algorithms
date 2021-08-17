#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;
};

class bst {
    node* root;

    node* insert (int x, node* to) {
        if (to == nullptr) {
            to = new node;
            to->data = x;
            to->left = nullptr;
            to->right = nullptr;
        } else if (x < to->data) {
            to->left = insert(x, to->left);
        } else if (x > to->data) {
            to->right = insert(x, to->right);
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

    int is_balanced(node* n, bool& balanced) {
        if (n == nullptr) {
            return 0;
        }
        int left_h = is_balanced(n->left, balanced);
        int right_h = is_balanced(n->right, balanced);
        if (abs(left_h - right_h) > 1) {
            balanced = false;
        }
        if (left_h > right_h) {
            return (left_h + 1);
        } else {
            return (right_h + 1);
        }
    }

    void inorder(node* n) {
        if (n == nullptr) {
            return;
        }
        inorder(n->left);
        int children = 0;
        if (n->left != nullptr)
            ++children;
        if (n->right != nullptr)
            ++children;
        if (children == 1) {
            cout << n->data << '\n';
        }
        inorder(n->right);
    }

public:
    bst() {
        root = nullptr;
    }

    ~bst() {
        root = clear(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void is_balanced() {
        bool balanced = true;
        is_balanced(root, balanced);
        if (balanced)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    void inorder() {
        inorder(root);
    }
};


int main() {
    bst tree;
    int elem;
    cin >> elem;
    while (elem != 0) {
        tree.insert(elem);
        cin >> elem;
    }
    tree.is_balanced();
}