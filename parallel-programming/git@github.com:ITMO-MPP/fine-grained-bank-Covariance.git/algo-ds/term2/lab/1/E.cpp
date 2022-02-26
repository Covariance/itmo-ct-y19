//
// Created by covariance on 17.02.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef struct CartesianNode {
    int key, prior, ind;
    CartesianNode *left, *right, *parent;

    explicit CartesianNode(int key, int prior, int ind) {
        this->key = key;
        this->prior = prior;
        this->ind = ind;
        this->left = this->right = this->parent = nullptr;
    }

    void print() {
        cout << getNum(this->parent)
            << " "
            << getNum(this->left)
            << " "
            << getNum(this->right)
            << endl;
    }

    static int getNum(CartesianNode* a) {
        return (a == nullptr) ? 0 : a->ind;
    }

    static bool smaller(CartesianNode *a, CartesianNode *b) {
        return a->key < b->key;
    }

    static bool greater(CartesianNode *a, CartesianNode *b) {
        return a->key > b->key;
    }
} node;


int main() {
    int n;
    cin >> n;
    vector<node*> tree;
    node* tmp;

    for (int i = 0; i < n; i++) {
        int key, prior;
        cin >> key >> prior;
        tree.push_back(new node(key, prior, i + 1));
    }
    sort(tree.begin(), tree.end(), CartesianNode::smaller);

    node *head = tree[0], *cur = tree[0];

    for (int i = 1; i < n; i++) {
        while (cur->prior > tree[i]->prior) {
            if (cur == head) {
                break;
            }
            cur = cur->parent;
        }
        if (cur != head || head->prior <= tree[i]->prior) {
            tmp = cur->right;
            cur->right = tree[i];
            tree[i]->parent = cur;
            cur = tree[i];
            cur->left = tmp;
            if (tmp != nullptr) {
                cur->left->parent = tree[i];
            }
        } else {
            tmp = head;
            head = tree[i];
            cur = head;
            head->left = tmp;
            head->left->parent = head;
        }
    }

    vector<node*> ans;
    vector<bool> used(n, false);
    ans.resize(n);
    queue<node*> bfs;
    bfs.push(tree[0]);
    while (!bfs.empty()) {
        tmp = bfs.front();
        bfs.pop();
        ans[tmp->ind - 1] = tmp;
        used[tmp->ind - 1] = true;
        if (tmp->parent != nullptr && !used[tmp->parent->ind - 1]) {
            bfs.push(tmp->parent);
        }
        if (tmp->left != nullptr && !used[tmp->left->ind - 1]) {
            bfs.push(tmp->left);
        }
        if (tmp->right != nullptr && !used[tmp->right->ind - 1]) {
            bfs.push(tmp->right);
        }
    }

    cout << "YES\n";
    for (node* entry : ans) {
        entry->print();
    }

    return 0;
}
