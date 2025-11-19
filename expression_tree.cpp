#include <iostream>
#include <stack>
using namespace std;

struct Node {
    char data;
    Node *left, *right;
    Node(char val) {
        data = val;
        left = right = NULL;
    }
};

// Check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to build expression tree from prefix expression
Node* buildTree(const char prefix[], int &index) {
    char c = prefix[index];
    index++;

    Node* newNode = new Node(c);

    if (isOperator(c)) {
        newNode->left = buildTree(prefix, index);
        newNode->right = buildTree(prefix, index);
    }
    return newNode;
}

// ---------- Recursive Traversals ----------
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data;
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (root == NULL) return;
    if (isOperator(root->data)) cout << "(";
    inorder(root->left);
    cout << root->data;
    inorder(root->right);
    if (isOperator(root->data)) cout << ")";
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data;
}

// ---------- Non-Recursive Traversals ----------
void preorderIter(Node* root) {
    if (root == NULL) return;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* curr = st.top(); st.pop();
        cout << curr->data;
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
}

void inorderIter(Node* root) {
    stack<Node*> st;
    Node* curr = root;
    while (curr != NULL || !st.empty()) {
        while (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        cout << curr->data;
        curr = curr->right;
    }
}

void postorderIter(Node* root) {
    if (root == NULL) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);
        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->data;
        s2.pop();
    }
}

// ---------- Mirror Tree ----------
void mirror(Node* root) {
    if (root == NULL) return;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}

// Free memory
void deleteTree(Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Menu display
void showMenu() {
    cout << "\n===== Expression Tree Menu =====\n";
    cout << "1. Build tree from PREFIX expression\n";
    cout << "2. Display Recursive Traversals\n";
    cout << "3. Display Non-Recursive Traversals\n";
    cout << "4. Mirror Tree (swap left and right)\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Node* root = NULL;
    char prefix[100];
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter prefix expression (e.g. +--a*bc/def): ";
            cin >> prefix;
            int index = 0;
            deleteTree(root); // delete old tree if any
            root = buildTree(prefix, index);
            cout << "Tree built successfully.\n";
            break;
        }

        case 2:
            if (root == NULL) {
                cout << "Please build the tree first.\n";
            } else {
                cout << "Preorder  (Recursive): ";
                preorder(root);
                cout << "\nInorder   (Recursive): ";
                inorder(root);
                cout << "\nPostorder (Recursive): ";
                postorder(root);
                cout << endl;
            }
            break;

        case 3:
            if (root == NULL)
                cout << "Please build the tree first.\n";
            else {
                cout << "Preorder  (Iterative): ";
                preorderIter(root);
                cout << "\nInorder   (Iterative): ";
                inorderIter(root);
                cout << "\nPostorder (Iterative): ";
                postorderIter(root);
                cout << endl;
            }
            break;

        case 4:
            if (root == NULL)
                cout << "Please build the tree first.\n";
            else {
                mirror(root);
                cout << "Tree mirrored successfully.\n";
            }
            break;

        case 5:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    deleteTree(root);
    return 0;
}