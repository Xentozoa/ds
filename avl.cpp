#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Node structure for AVL tree
struct Node {
    string key;   // Dictionary key
    string value; // Associated value
    Node *left, *right;
    int height;
};

// Function to get height of node
int height(Node *N) {
    return (N == nullptr) ? 0 : N->height;
}

// Function to get balance factor
int getBalance(Node *N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Create new node
Node* createNode(string key, string value) {
    Node* node = new Node();
    node->key = key;
    node->value = value;
    node->left = node->right = nullptr;
    node->height = 1;
    return node;
}

// Right rotate
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Insert (key, value) in AVL Tree
Node* insert(Node* node, string key, string value) {
    if (node == nullptr)
        return createNode(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else {
        cout << "Duplicate key not allowed!\n";
        return node;
    }

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Check balance factor
    int balance = getBalance(node);

    // Balancing Cases
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find minimum node (used in deletion)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Delete a key
Node* deleteNode(Node* root, string key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with one or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Balancing after deletion
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find key in AVL Tree
bool find(Node* root, string key, int &comparisons) {
    if (root == nullptr)
        return false;

    comparisons++;
    if (key == root->key)
        return true;
    else if (key < root->key)
        return find(root->left, key, comparisons);
    else
        return find(root->right, key, comparisons);
}

// Display ascending order
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " : " << root->value << endl;
        inorder(root->right);
    }
}

// Display descending order
void descending(Node* root) {
    if (root != nullptr) {
        descending(root->right);
        cout << root->key << " : " << root->value << endl;
        descending(root->left);
    }
}

// Menu-driven main function
int main() {
    Node* root = nullptr;
    int choice;
    string key, value;

    do {
        cout << "\n=== DICTIONARY USING AVL TREE ===";
        cout << "\n1. Insert (key, value)";
        cout << "\n2. Delete a key";
        cout << "\n3. Find a key";
        cout << "\n4. Display Ascending Order";
        cout << "\n5. Display Descending Order";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            root = insert(root, key, value);
            break;

        case 2:
            cout << "Enter key to delete: ";
            cin >> key;
            root = deleteNode(root, key);
            break;

        case 3: {
            cout << "Enter key to find: ";
            cin >> key;
            int comparisons = 0;
            bool found = find(root, key, comparisons);
            if (found)
                cout << "Key found! (" << comparisons << " comparisons)\n";
            else
                cout << "Key not found! (" << comparisons << " comparisons)\n";
            cout << "Max possible comparisons (O(log n)) for n nodes: ≈ log2(n)\n";
            break;
        }

        case 4:
            cout << "\nAscending Order (Key : Value)\n";
            inorder(root);
            break;

        case 5:
            cout << "\nDescending Order (Key : Value)\n";
            descending(root);
            break;

        case 6:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}