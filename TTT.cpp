#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    vector<int> keys;
    vector<Node*> children;
    bool isLeaf;

    Node(bool leaf = true) : isLeaf(leaf) {}

    bool isFull() const { return keys.size() > 2; }
};

class TwoThreeTree {
    Node* root;

    // Helper to insert a key into a node's keys vector in sorted order
    void insertIntoNode(Node* node, int key, Node* rightChild = nullptr) {
        auto it = lower_bound(node->keys.begin(), node->keys.end(), key);
        int index = distance(node->keys.begin(), it);
        node->keys.insert(it, key);
        if (!node->isLeaf && rightChild) {
            node->children.insert(node->children.begin() + index + 1, rightChild);
        }
    }

    // Recursive helper that returns a pointer to a new node if a split occurred
    Node* insertRecursive(Node* node, int key, int& promotedKey) {
        if (node->isLeaf) {
            insertIntoNode(node, key);
        } else {
            // Determine which child to recurse into
            int i = 0;
            while (i < node->keys.size() && key > node->keys[i]) i++;
            
            int upKey;
            Node* newChild = insertRecursive(node->children[i], key, upKey);
            
            if (newChild) {
                insertIntoNode(node, upKey, newChild);
            }
        }

        // Handle overflow (4-node detection)
        if (node->isFull()) {
            promotedKey = node->keys[1]; // Median key
            Node* rightNode = new Node(node->isLeaf);
            
            // Move the largest key and its corresponding children to the new node
            rightNode->keys.push_back(node->keys[2]);
            if (!node->isLeaf) {
                rightNode->children.push_back(node->children[2]);
                rightNode->children.push_back(node->children[3]);
                node->children.erase(node->children.begin() + 2, node->children.end());
            }
            
            // Clean up original node
            node->keys.erase(node->keys.begin() + 1, node->keys.end());
            return rightNode;
        }
        return nullptr;
    }

public:
    TwoThreeTree() : root(nullptr) {}

    void insert(int key) {
        if (!root) {
            root = new Node();
            root->keys.push_back(key);
            return;
        }

        int promotedKey;
        Node* newChild = insertRecursive(root, key, promotedKey);

        // If the root split, create a new root
        if (newChild) {
            Node* oldRoot = root;
            root = new Node(false);
            root->keys.push_back(promotedKey);
            root->children.push_back(oldRoot);
            root->children.push_back(newChild);
        }
    }

    void printInorder(Node* node) {
        if (!node) return;
        for (int i = 0; i < node->keys.size(); i++) {
            if (!node->isLeaf) printInorder(node->children[i]);
            cout << node->keys[i] << " ";
        }
        if (!node->isLeaf) printInorder(node->children.back());
    }

    void display() {
        printInorder(root);
        cout << endl;
    }
};

int main() {
    TwoThreeTree tree;
    vector<int> vals = {10, 20, 5, 15, 25, 30, 7};
    for (int v : vals) tree.insert(v);
    
    cout << "Inorder traversal of 2-3 Tree: ";
    tree.display(); // Should output: 5 7 10 15 20 25 30 
    return 0;
}
