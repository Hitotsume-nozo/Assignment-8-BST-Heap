#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool isBSTUtil(Node* root, long minVal, long maxVal) {
    if (root == nullptr) return true;
    if (root->data <= minVal || root->data >= maxVal) return false;
    return isBSTUtil(root->left, minVal, root->data) && 
           isBSTUtil(root->right, root->data, maxVal);
}

bool isBST(Node* root) {
    return isBSTUtil(root, LONG_MIN, LONG_MAX);
}

int main() {
    Node* root1 = new Node(50);
    root1->left = new Node(30);
    root1->right = new Node(70);
    root1->left->left = new Node(20);
    root1->left->right = new Node(40);
    
    cout << "Tree 1 is BST: " << (isBST(root1) ? "Yes" : "No") << endl;
    
    Node* root2 = new Node(50);
    root2->left = new Node(30);
    root2->right = new Node(70);
    root2->left->left = new Node(20);
    root2->left->right = new Node(60);
    
    cout << "Tree 2 is BST: " << (isBST(root2) ? "Yes" : "No") << endl;
    
    return 0;
}