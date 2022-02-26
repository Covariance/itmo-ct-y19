//
// Created by covariance on 27.02.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef struct CartesianNode {
    int key, prior;
    long long sum;
    CartesianNode *left, *right;

    explicit CartesianNode(int key) {
        this->key = key;
        this->prior = rand();
        this->sum = key;
        this->left = this->right = nullptr;
    }

    static long long getSum(CartesianNode *root) {
        return (root == nullptr) ? 0LL : root->sum;
    }

    static void updateSum(CartesianNode *root) {
        if (root == nullptr) {
            return;
        }
        root->sum = root->key + getSum(root->left) + getSum(root->right);
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

    static bool found(CartesianNode *root, int key) {
        if (root == nullptr) {
            return false;
        }
        if (root->key == key) {
            return true;
        }
        return (root->key > key) ? found(root->left, key) : found(root->right, key);
    }

    static pair<CartesianNode *, CartesianNode *> split(CartesianNode *root, int key) {
        if (root == nullptr) {
            return make_pair(nullptr, nullptr);
        }
        if (root->key < key) {
            pair<CartesianNode *, CartesianNode *> tmp = split(root->right, key);
            root->right = tmp.first;
            tmp.first = root;

            updateSum(tmp.second);
            updateSum(root);

            return tmp;
        } else {
            pair<CartesianNode *, CartesianNode *> tmp = split(root->left, key);
            root->left = tmp.second;
            tmp.second = root;

            updateSum(tmp.first);
            updateSum(root);

            return tmp;
        }
    }

    static CartesianNode *merge(CartesianNode *left, CartesianNode *right) {
        if (right == nullptr) {
            updateSum(left);
            return left;
        }
        if (left == nullptr) {
            updateSum(right);
            return right;
        }
        if (left->prior > right->prior) {
            left->right = merge(left->right, right);

            updateSum(left);

            return left;
        }
        right->left = merge(left, right->left);

        updateSum(right);

        return right;
    }

    static long long segmentSum(CartesianNode *root, int l, int r) {
        pair<CartesianNode *, CartesianNode *> tmp = split(root, l);
        long long res = getSum(tmp.first);
        merge(tmp.first, tmp.second);
        tmp = split(root, r + 1);
        res = getSum(tmp.first) - res;
        merge(tmp.first, tmp.second);
        return res;
    }

    static CartesianNode *insert(CartesianNode *root, CartesianNode *newNode) {
        pair<CartesianNode *, CartesianNode *> tmp = split(root, newNode->key);
        return merge(merge(tmp.first, newNode), tmp.second);
    }
} node;

int main() {
    int n;
    cin >> n;
    node *root = nullptr;
    bool lastQ = false;
    long long lastRes = 0;
    while (n--) {
        char t;
        cin >> t;
        if (t == '+') {
            int a;
            cin >> a;
            if (lastQ) {
                a = (a + (int)(lastRes % 1000000000)) % 1000000000;
            }
            if (!CartesianNode::found(root, a)) {
                root = CartesianNode::insert(root, new node(a));
            }
            lastQ = false;
        }
        if (t == '?') {
            int l, r;
            cin >> l >> r;
            lastRes = CartesianNode::segmentSum(root, l, r);
            cout << lastRes << endl;
            lastQ = true;
        }
        // root->print();
        // cout << endl;
    }
    return 0;
}
