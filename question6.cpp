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