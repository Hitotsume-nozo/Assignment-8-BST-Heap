# Assignment 8: BST & Heap

Lab Assignment 8: Binary Search Trees and Heap

---

## Question 1: Binary Tree Traversals

**Explanation:** This program implements three types of recursive tree traversals: preorder (root-left-right), inorder (left-root-right), and postorder (left-right-root).

**Code:**
```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void preorder(Node* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (root == nullptr) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    
    cout << "Preorder: ";
    preorder(root);
    cout << endl;
    
    cout << "Inorder: ";
    inorder(root);
    cout << endl;
    
    cout << "Postorder: ";
    postorder(root);
    cout << endl;
    
    return 0;
}
```

**Output:**
```
Preorder: 1 2 4 5 3 
Inorder: 4 2 5 1 3 
Postorder: 4 5 2 3 1 
```

---

## Question 2: BST Functions

**Explanation:** This program implements various BST operations including recursive and non-recursive search, finding maximum and minimum elements, and finding inorder successor and predecessor of a given node.

**Code:**
```cpp
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
```

**Output:**
```
Search 40 (Recursive): Found
Search 40 (Non-Recursive): Found
Maximum: 80
Minimum: 20
Inorder Successor of 40: 50
Inorder Predecessor of 40: 30
```

---

## Question 3: BST Insert, Delete, and Depth

**Explanation:** This program implements BST operations including insertion of elements (no duplicates), deletion of existing elements, and calculation of maximum and minimum depth of the tree.

**Code:**
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int key) {
    if (root == nullptr) return new Node(key);
    if (key < root->data) root->left = insert(root->left, key);
    else if (key > root->data) root->right = insert(root->right, key);
    return root;
}

Node* findMin(Node* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return root;
    
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int maxDepth(Node* root) {
    if (root == nullptr) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

int minDepth(Node* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    if (root->left == nullptr) return 1 + minDepth(root->right);
    if (root->right == nullptr) return 1 + minDepth(root->left);
    return 1 + min(minDepth(root->left), minDepth(root->right));
}

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    cout << "Inorder: ";
    inorder(root);
    cout << endl;
    
    cout << "Maximum Depth: " << maxDepth(root) << endl;
    cout << "Minimum Depth: " << minDepth(root) << endl;
    
    root = deleteNode(root, 20);
    cout << "After deleting 20: ";
    inorder(root);
    cout << endl;
    
    return 0;
}
```

**Output:**
```
Inorder: 20 30 40 50 60 70 80 
Maximum Depth: 3
Minimum Depth: 3
After deleting 20: 30 40 50 60 70 80 
```

---

## Question 4: Validate BST

**Explanation:** This program determines whether a given binary tree is a valid Binary Search Tree by checking if all nodes satisfy the BST property (left subtree < node < right subtree).

**Code:**
```cpp
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
```

**Output:**
```
Tree 1 is BST: Yes
Tree 2 is BST: No
```

---

## Question 5: Heapsort

**Explanation:** This program implements the Heapsort algorithm to sort an array in increasing order by building a max heap and repeatedly extracting the maximum element.

**Code:**
```cpp
#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Original array: ";
    printArray(arr, n);
    
    heapSort(arr, n);
    
    cout << "Sorted array (Increasing): ";
    printArray(arr, n);
    
    return 0;
}
```

**Output:**
```
Original array: 12 11 13 5 6 7 
Sorted array (Increasing): 5 6 7 11 12 13 
```

---

## Question 6: Priority Queue using Heap

**Explanation:** This program implements a priority queue using a max heap data structure with operations like insert, extract maximum, peek, and checking if the queue is empty.

**Code:**
```cpp
#include <iostream>
using namespace std;

class PriorityQueue {
private:
    int heap[100];
    int size;
    
    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (heap[parent] < heap[index]) {
            swap(heap[parent], heap[index]);
            heapifyUp(parent);
        }
    }
    
    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < size && heap[left] > heap[largest])
            largest = left;
        
        if (right < size && heap[right] > heap[largest])
            largest = right;
        
        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }
    
public:
    PriorityQueue() : size(0) {}
    
    void insert(int value) {
        heap[size] = value;
        heapifyUp(size);
        size++;
    }
    
    int extractMax() {
        if (size == 0) return -1;
        int maxVal = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return maxVal;
    }
    
    int peek() {
        if (size == 0) return -1;
        return heap[0];
    }
    
    bool isEmpty() {
        return size == 0;
    }
};

int main() {
    PriorityQueue pq;
    
    pq.insert(10);
    pq.insert(30);
    pq.insert(20);
    pq.insert(5);
    pq.insert(50);
    
    cout << "Priority Queue (Max Heap):" << endl;
    cout << "Peek: " << pq.peek() << endl;
    
    cout << "Extracting elements: ";
    while (!pq.isEmpty()) {
        cout << pq.extractMax() << " ";
    }
    cout << endl;
    
    return 0;
}
```

**Output:**
```
Priority Queue (Max Heap):
Peek: 50
Extracting elements: 50 30 20 10 5 
```

---

## Conclusion

This assignment covered fundamental data structures and algorithms related to Binary Search Trees and Heaps. Through implementing tree traversals, BST operations, validation, and heap-based algorithms, we gained practical experience with hierarchical data structures. The BST operations demonstrated efficient searching, insertion, and deletion with logarithmic time complexity for balanced trees. Heapsort and priority queues showcased the power of the heap data structure for sorting and priority-based processing. These concepts form the foundation for more advanced data structures and algorithms used in real-world applications.