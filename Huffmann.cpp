#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

// Node structure for Huffman Tree
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    
    // Destructor to prevent memory leaks
    ~Node() {
        delete left;
        delete right;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string code, unordered_map<char, string>& huffCodes) {
    if (!root) return;
    
    // Leaf node: contains a character
    if (!root->left && !root->right) {
        huffCodes[root->ch] = (code.empty() ? "0" : code); // Handle single character case
    }
    
    generateCodes(root->left, code + "0", huffCodes);
    generateCodes(root->right, code + "1", huffCodes);
}

int main() {
    string text;
    cout << "Enter text: ";
    if (!getline(cin, text) || text.empty()) return 0;

    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto const& [ch, f] : freq) {
        pq.push(new Node(ch, f));
    }

    // Build the tree
    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node* root = pq.top();
    unordered_map<char, string> huffCodes;
    generateCodes(root, "", huffCodes);

    cout << "\nHuffman Codes:\n";
    for (auto const& [ch, code] : huffCodes) {
        cout << "'" << ch << "': " << code << "\n";
    }

    string encoded = "";
    for (char c : text) encoded += huffCodes[c];
    cout << "\nEncoded string: " << encoded << "\n";

    // Clean up memory
    delete root; 
    return 0;
}
