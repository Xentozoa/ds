#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

// Huffman Tree Node
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Compare class for priority queue (min-heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Function to generate Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string> &codes) {
    if (!root) return;

    // Leaf node → store the code
    if (!root->left && !root->right) {
        codes[root->ch] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Function to build Huffman Tree
Node* buildHuffmanTree(unordered_map<char, int> &freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto &p : freq) {
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        Node *newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

// Encode the input text
string encode(const string &text, unordered_map<char, string> &codes) {
    string encoded = "";
    for (char ch : text) {
        encoded += codes[ch];
    }
    return encoded;
}

// Decode encoded binary string
string decode(Node *root, const string &encoded) {
    string decoded = "";
    Node *curr = root;

    for (char bit : encoded) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        // Reached leaf → add character
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root;
        }
    }

    return decoded;
}

int main() {
    string text;
    int choice;

    while (true) {
        cout << "\n===== HUFFMAN CODING MENU =====\n";
        cout << "1. Compress Message\n";
        cout << "2. Decompress Message\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter message (alphabets only): ";
            cin >> text;

            unordered_map<char, int> freq;
            for (char ch : text) freq[ch]++;

            Node *root = buildHuffmanTree(freq);

            unordered_map<char, string> codes;
            generateCodes(root, "", codes);

            cout << "\nHuffman Codes:\n";
            for (auto &p : codes) {
                cout << p.first << ": " << p.second << "\n";
            }

            string encoded = encode(text, codes);
            cout << "\nEncoded String: " << encoded << "\n";

        } else if (choice == 2) {
            string encoded;
            cout << "Enter encoded binary string: ";
            cin >> encoded;

            string original;
            cout << "Enter original message to rebuild tree: ";
            cin >> text;  // Required to build correct Huffman tree

            unordered_map<char, int> freq;
            for (char ch : text) freq[ch]++;

            Node *root = buildHuffmanTree(freq);

            string decoded = decode(root, encoded);

            cout << "\nDecoded Message: " << decoded << "\n";

        } else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}