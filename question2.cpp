#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool searchRecursive(Node* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;
    if (key < root->data) return searchRecursive(root->left, key);
    return searchRecursive(root->right, key);
}

bool searchNonRecursive(Node* root, int key) {
    while (root != nullptr) {
        if (root->data == key) return true;
        if (key < root->data) root = root->left;
        else root = root->right;
    }
    return false;
}

int findMax(Node* root) {
    if (root == nullptr) return -1;
    while (root->right != nullptr) {
        root = root->right;
    }
    return root->data;
}

int findMin(Node* root) {
    if (root == nullptr) return -1;
    while (root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

Node* findNode(Node* root, int key) {
    if (root == nullptr || root->data == key) return root;
    if (key < root->data) return findNode(root->left, key);
    return findNode(root->right, key);
}

Node* inorderSuccessor(Node* root, int key) {
    Node* node = findNode(root, key);
    if (node == nullptr) return nullptr;
    
    if (node->right != nullptr) {
        node = node->right;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    Node* successor = nullptr;
    Node* current = root;
    while (current != nullptr) {
        if (key < current->data) {
            successor = current;
            current = current->left;
        } else if (key > current->data) {
            current = current->right;
        } else {
            break;
        }
    }
    return successor;
}

Node* inorderPredecessor(Node* root, int key) {
    Node* node = findNode(root, key);
    if (node == nullptr) return nullptr;
    
    if (node->left != nullptr) {
        node = node->left;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
    
    Node* predecessor = nullptr;
    Node* current = root;
    while (current != nullptr) {
        if (key > current->data) {
            predecessor = current;
            current = current->right;
        } else if (key < current->data) {
            current = current->left;
        } else {
            break;
        }
    }
    return predecessor;
}

int main() {
    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    root->right->left = new Node(60);
    root->right->right = new Node(80);
    
    cout << "Search 40 (Recursive): " << (searchRecursive(root, 40) ? "Found" : "Not Found") << endl;
    cout << "Search 40 (Non-Recursive): " << (searchNonRecursive(root, 40) ? "Found" : "Not Found") << endl;
    cout << "Maximum: " << findMax(root) << endl;
    cout << "Minimum: " << findMin(root) << endl;
    
    Node* succ = inorderSuccessor(root, 40);
    cout << "Inorder Successor of 40: " << (succ ? to_string(succ->data) : "NULL") << endl;
    
    Node* pred = inorderPredecessor(root, 40);
    cout << "Inorder Predecessor of 40: " << (pred ? to_string(pred->data) : "NULL") << endl;
    
    return 0;
}