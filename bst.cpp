#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int val) {
    Node* newnode = new Node();
    newnode->data = val;
    newnode->left = newnode->right = NULL;
    return newnode;
}

Node* insert(Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }

    if (root->data < val) {
        root->right = insert(root->right, val);
    }
    else if (root->data > val) {
        root->left = insert(root->left, val);
    }
    else {
        cout << "Duplicate value not allowed!\n";
    }
    return root;
}

int height(Node* root) {
    if (root == NULL)
        return 0;

    int leftheight = height(root->left);
    int rightheight = height(root->right);

    return max(leftheight, rightheight) + 1;
}

int findMin(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty.\n";
        return -1;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root->data;
}

bool search(Node* root, int key) {
    if (root == NULL)
        return false;

    if (root->data == key)
        return true;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// FIXED descending order function
void desc(Node* root) {
    if (root != NULL) {
        desc(root->right);  // visit right first
        cout << root->data << " ";
        desc(root->left);   // then left
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    cout << "=== Binary Search Tree Operations ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert new node\n";
        cout << "2. Find number of nodes in longest path from root\n";
        cout << "3. Find minimum data value in tree\n";
        cout << "4. Search a value\n";
        cout << "5. Print values in ascending order\n";
        cout << "6. Print values in descending order\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            root = insert(root, value);
            break;

        case 2:
            cout << "Number of nodes in longest path: " << height(root) << endl;
            break;

        case 3:
            cout << "Minimum data value in tree: " << findMin(root) << endl;
            break;

        case 4:
            cout << "Enter value to search: ";
            cin >> value;
            if (search(root, value))
                cout << "Value found in BST.\n";
            else
                cout << "Value not found in BST.\n";
            break;

        case 5:
            cout << "Values in ascending order: ";
            inorder(root);
            cout << endl;
            break;

        case 6:
            cout << "Values in descending order: ";
            desc(root);
            cout << endl;
            break;

        case 7:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}