#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


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

    int height(node* n) {
        if (n == nullptr) {
            return 0;
        }
        int left_hight = height(n->left);
        int right_hight = height(n->right);
        if (left_hight > right_hight) {
            return (left_hight + 1);
        } else {
            return (right_hight + 1);
        }
    }

    void secondmax(node* n, int& step) {
        if (step >= 2 || n == nullptr) {
            return;
        }
        secondmax(n->right, step);
        ++step;
        if (step == 2) {
            cout << n->data << '\n';
            return;
        }
        secondmax(n->left, step);
    }

    void inorder(node* n) {
        if (n == nullptr) {
            return;
        }
        inorder(n->left);
        cout << n->data << '\n';
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

    int height() {
        return height(root);
    }

    void secondmax() {
        int step = 0;
        secondmax(root, step);
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
    tree.secondmax();
}