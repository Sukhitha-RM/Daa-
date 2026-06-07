#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to find the minimum value in a subtree (used for deletion)
Node* findMin(Node* root) {
    while (root && root->left != nullptr) 
        root = root->left;
    return root;
}

// 1. Insertion: Always inserts at a leaf position
Node* insert(Node* root, int key) {
    if (root == nullptr) return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);

    return root;
}

// 2. Deletion: Handles three cases (0, 1, or 2 children)
Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return root;

    // Search for the node to be deleted
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Case 1 & 2: Node with 0 or 1 child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Node with 2 children
        // Get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(root->right);
        root->data = temp->data;
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    int values[] = {50, 30, 20, 40, 70, 60, 80};
    for (int val : values) root = insert(root, val);

    cout << "Original BST: ";
    inorder(root); // Output: 20 30 40 50 60 70 80

    cout << "\nDeleting 20 (leaf): ";
    root = deleteNode(root, 20);
    inorder(root);

    cout << "\nDeleting 30 (one child): ";
    root = deleteNode(root, 30);
    inorder(root);

    cout << "\nDeleting 50 (two children): ";
    root = deleteNode(root, 50);
    inorder(root);
return 0;
}
