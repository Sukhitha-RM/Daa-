#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node*& x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node*& y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node*& k) {
        while (k != root && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                Node* u = k->parent->parent->right; // uncle
                if (u && u->color == RED) { // Case 1: Uncle is Red
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) { // Case 2: Uncle is Black, k is right child
                        k = k->parent;
                        rotateLeft(k);
                    }
                    // Case 3: Uncle is Black, k is left child
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateRight(k->parent->parent);
                }
            } else { // Mirror case (parent is right child)
                Node* u = k->parent->parent->left;
                if (u && u->color == RED) {
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rotateRight(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateLeft(k->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        Node* z = new Node(data);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->data < x->data) x = x->left;
            else x = x->right;
        }

        z->parent = y;
        if (y == nullptr) root = z;
        else if (z->data < y->data) y->left = z;
        else y->right = z;

        fixInsert(z);
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorder(node->right);
    }

    Node* getRoot() { return root; }
};

int main() {
    RedBlackTree rbt;
    int arr[] = {10, 20, 30, 15};
    for (int x : arr) rbt.insert(x);

    std::cout << "Inorder Traversal: ";
    rbt.inorder(rbt.getRoot());
    return 0;
}
