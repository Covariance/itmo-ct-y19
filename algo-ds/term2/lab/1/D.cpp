//
// Created by covariance on 27.02.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef struct CartesianNode {
    int key, prior, size;
    CartesianNode *left, *right;

    explicit CartesianNode(int key) {
        this->key = key;
        this->prior = rand();
        this->size = 1;
        this->left = this->right = nullptr;
    }

    static int getSize(CartesianNode *root) {
        return (root == nullptr) ? 0 : root->size;
    }

    static void updateSize(CartesianNode *root) {
        if (root == nullptr) {
            return;
        }
        root->size = 1 + getSize(root->left) + getSize(root->right);
    }

    void print() {
        if (this->left != nullptr) {
            this->left->print();
        }
        cout << this->key << ' ';
        if (this->right != nullptr) {
            this->right->print();
        }
    }

    int kthStat(int k) {
        if (k == getSize(this->left)) {
            return this->key;
        }
        return (k < getSize(this->left)) ?
               this->left->kthStat(k) : this->right->kthStat(k - getSize(this->left) - 1);
    }

    static pair<CartesianNode *, CartesianNode *> split(CartesianNode *root, int key) {
        if (root == nullptr) {
            return make_pair(nullptr, nullptr);
        }
        if (root->key < key) {
            pair<CartesianNode *, CartesianNode *> tmp = split(root->right, key);
            root->right = tmp.first;
            tmp.first = root;

            updateSize(tmp.second);
            updateSize(root);

            return tmp;
        } else {
            pair<CartesianNode *, CartesianNode *> tmp = split(root->left, key);
            root->left = tmp.second;
            tmp.second = root;

            updateSize(tmp.first);
            updateSize(root);

            return tmp;
        }
    }

    static CartesianNode *merge(CartesianNode *left, CartesianNode *right) {
        if (right == nullptr) {
            updateSize(left);
            return left;
        }
        if (left == nullptr) {
            updateSize(right);
            return right;
        }
        if (left->prior > right->prior) {
            left->right = merge(left->right, right);

            updateSize(left);

            return left;
        }
        right->left = merge(left, right->left);

        updateSize(right);

        return right;
    }

    static CartesianNode *insert(CartesianNode *root, CartesianNode *newNode) {
        pair<CartesianNode *, CartesianNode *> tmp = split(root, newNode->key);
        return merge(merge(tmp.first, newNode), tmp.second);
    }

    static CartesianNode *remove(CartesianNode *root, int key) {
        pair<CartesianNode *, CartesianNode *> tmp1 = split(root, key);
        pair<CartesianNode *, CartesianNode *> tmp2 = split(tmp1.second, key + 1);
        return merge(tmp1.first, tmp2.second);
    }

    static CartesianNode *mtf(CartesianNode *root, int l, int r) {
        pair<CartesianNode *, CartesianNode *> tmp1 = split(root, r);
        pair<CartesianNode *, CartesianNode *> tmp2 = split(tmp1.first, l - 1);
        return merge(tmp2.second, merge(tmp2.first, tmp1.second));
    }
} node;

int main() {
    int n, tmp, size = 0;
    string type;
    cin >> n;
    node* root = nullptr;
    while (n--) {
        cin >> type;
        switch (type[0]) {
            case '1':
            case '+':
                cin >> tmp;
                root = CartesianNode::insert(root, new node(tmp));
                size++;
                break;
            case '-':
                cin >> tmp;
                root = CartesianNode::remove(root, tmp);
                size--;
                break;
            default:
                cin >> tmp;
                cout << root->kthStat(size - tmp) << endl;
                break;
        }
    }
}
