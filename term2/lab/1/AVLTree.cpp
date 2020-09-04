//
// Created by covariance on 15.02.2020.
//
#include <bits/stdc++.h>

#pragma GCC optimize("-O3")

using namespace std;

typedef struct AVLNode {
    int key;
    int height;
    AVLNode *left;
    AVLNode *right;

    explicit AVLNode(int key) {
        this->key = key;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }

    AVLNode *rightRotate();

    AVLNode *leftRotate();

    AVLNode *rlRotate();

    AVLNode *lrRotate();

    void updateHeight();

    static int getHeight(AVLNode *v);

    int getBalance();
} node;

class AVLTree {
 public:
    node *head;

    explicit AVLTree() {
        this->head = nullptr;
    }

    void print();

    static void print(node *root, int tabs);

    void insert(int key);

    static node *insert(node *root, int key);

    void remove(int key);

    static node *remove(node *root, int key);

    bool exists(int key);

    static bool exists(node *root, int key);

    string next(int key);

    node *next(node *root, int key);

    string prev(int key);

    node *prev(node *root, int key);

    static int min(node *v);
};

int AVLNode::getHeight(node *v) {
    return (v == nullptr) ? 0 : v->height;
}

void AVLNode::updateHeight() {
    this->height = 1 + max(getHeight(this->left), getHeight(this->right));
}

int AVLNode::getBalance() {
    return getHeight(this->left) - getHeight(this->right);
}

/*                 Right rotate
 *
 *          <root>                <tmp>
 *          /    \                /   \
 *       <tmp>   T3    ------>   T1 <root>
 *        / \                        /  \
 *       T1 T2                      T2  T3
 */

node *AVLNode::rightRotate() {
    node *tmp = this->left;
    this->left = tmp->right;
    tmp->right = this;
    this->updateHeight();
    tmp->updateHeight();
    return tmp;
}

/*                  Left rotate
 *
 *          <root>                  <tmp>
 *          /    \                  /   \
 *         T1   <tmp>   ------>  <root> T3
 *               / \              /  \
 *              T2 T3            T1  T2
 */

node *AVLNode::leftRotate() {
    node *tmp = this->right;
    this->right = tmp->left;
    tmp->left = this;
    this->updateHeight();
    tmp->updateHeight();
    return tmp;
}

node *AVLNode::rlRotate() {
    this->right = this->right->rightRotate();
    return this->leftRotate();
}

node *AVLNode::lrRotate() {
    this->left = this->left->leftRotate();
    return this->rightRotate();
}

int AVLTree::min(node *v) {
    while (v->left != nullptr) {
        v = v->left;
    }
    return v->key;
}

void AVLTree::print() {
    print(this->head, 0);
}

void AVLTree::print(node *root, int tabs) {
    cout << string(tabs, '\t') << root->key << endl;
    if (root->left != nullptr) {
        cout << string(tabs, '\t') << "left:" << endl;
        print(root->left, tabs + 1);
    }
    if (root->right != nullptr) {
        cout << string(tabs, '\t') << "right:" << endl;
        print(root->right, tabs + 1);
    }
}

void AVLTree::insert(int key) {
    this->head = insert(this->head, key);
}

node *AVLTree::insert(node *root, int key) {
    if (root == nullptr) {
        return (new node(key));
    }

    if (key == root->key) {
        return root;
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    root->updateHeight();
    int balance = root->getBalance();

    // left-left
    if (balance > 1 && key < root->left->key) {
        return root->rightRotate();
    }
    // right-right
    if (balance < -1 && key > root->right->key) {
        return root->leftRotate();
    }
    // left-right
    if (balance > 1 && key > root->left->key) {
        return root->lrRotate();
    }
    // right-left
    if (balance < -1 && key < root->right->key) {
        return root->rlRotate();
    }
    return root;
}

void AVLTree::remove(int key) {
    this->head = remove(this->head, key);
}

node *AVLTree::remove(node *root, int key) {
    if (root == nullptr) {
        return nullptr;
    }
    if (key < root->key) {
        root->left = remove(root->left, key);
    } else if (key > root->key) {
        root->right = remove(root->right, key);
    } else {
        int switcher = (root->left == nullptr) + (root->right == nullptr);
        node *deleted;
        switch (switcher) {
            case 2:
                // no children
                deleted = root;
                root = nullptr;
                free(deleted);
                break;
            case 1:
                // only one child
                deleted = root;
                root = (root->left == nullptr) ? root->right : root->left;
                free(deleted);
                break;
            case 0:
                // both children exist
                root->right = remove(root->right, (root->key = min(root->right)));
                break;
        }
    }

    if (root == nullptr) {
        return root;
    }

    root->height = 1 + max(AVLNode::getHeight(root->left),
                           AVLNode::getHeight(root->right));
    int balance = root->getBalance();

    // left-left
    if (balance > 1 && root->left->getBalance() >= 0) {
        return root->rightRotate();
    }
    // left-right
    if (balance > 1 && root->left->getBalance() < 0) {
        return root->lrRotate();
    }
    // right-right
    if (balance < -1 && root->right->getBalance() <= 0)
        return root->leftRotate();
    // right-left
    if (balance < -1 && root->right->getBalance() > 0) {
        return root->rlRotate();
    }
    return root;
}

bool AVLTree::exists(int key) {
    return exists(this->head, key);
}

bool AVLTree::exists(node *root, int key) {
    while (root != nullptr && root->key != key) {
        root = (root->key > key) ? root->left : root->right;
    }
    return (root != nullptr);
}

string AVLTree::next(int key) {
    node *tmp = next(this->head, key);
    return (tmp == nullptr) ? "none" : to_string(tmp->key);
}

node *AVLTree::next(node *root, int key) {
    if (root == nullptr) {
        return nullptr;
    }
    node *tmp = next((root->key > key) ? root->left : root->right, key);
    return (tmp == nullptr) ? ((root->key > key) ? root : nullptr) : tmp;
}

string AVLTree::prev(int key) {
    node *tmp = prev(this->head, key);
    return (tmp == nullptr) ? "none" : to_string(tmp->key);
}

node *AVLTree::prev(node *root, int key) {
    if (root == nullptr) {
        return nullptr;
    }
    node *tmp = prev((root->key < key) ? root->right : root->left, key);
    return (tmp == nullptr) ? ((root->key < key) ? root : nullptr) : tmp;
}

int main() {
    string s;
    int v;
    AVLTree a;
    while (cin >> s) {
        switch (s[0]) {
            case 'i':
                cin >> v;
                a.insert(v);
                break;
            case 'd':
                cin >> v;
                a.remove(v);
                break;
            case 'e':
                cin >> v;
                cout << (a.exists(v) ? "true" : "false") << endl;
                break;
            case 'p':
                cin >> v;
                cout << a.prev(v) << endl;
                break;
            case 'n':
                cin >> v;
                cout << a.next(v) << endl;
                break;
            case 'a':
                a.print();
                break;
            default:
                cout << "poof" << endl;
                break;
        }
    }
    return 0;
}
