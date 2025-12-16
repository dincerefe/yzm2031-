/**
 * Problem 1: The Emergency Room Triage
 */

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;


class MinHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i-1)/2; }
    int left(int i) { return i*2+1; }
    int right(int i) { return i*2+2; }

    void heapify(int i) {
        // Implement this
        if (heap.empty()) return;
        for (int i = heap.size() - 1; i >= 0; i--) {
            if(heap[i] < heap[parent(i)]) {
                int temp = heap[i];
                heap[i] = heap[parent(i)];
                heap[parent(i)] = temp;
                heapify(parent(i));
            }
        }
    }

public:
    void insert(int val) {
        // Implement this
        heap.push_back(val);
        heapify(heap.size() - 1);
    }

    int extractMin() {
        // Implement this
        if (heap.empty()) return -1;
        int min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return min;
    }

    int getMin() {
        // Implement this
        return heap[0];
    }

    bool isEmpty() {
        return heap.empty();
    }
    
    void printHeap() {
        for (int i : heap) cout << i << " ";
        cout << endl;
    }
};

int main() {
    MinHeap h;
    
    cout << "=== Emergency Room Triage System ===" << endl;
    cout << "Inserting patients with severity scores: 10, 5, 30, 2, 8" << endl;
    
    h.insert(10);
    h.insert(5);
    h.insert(30);
    h.insert(2);
    h.insert(8);
    
    cout << "Heap state: ";
    h.printHeap();
    
    cout << "Most critical patient (Min): " << h.getMin() << endl;
    
    cout << "Treating patient: " << h.extractMin() << endl;
    cout << "Heap after extraction: ";
    h.printHeap();
    
    cout << "Treating next patient: " << h.extractMin() << endl;
    cout << "Heap after extraction: ";
    h.printHeap();
    
    return 0;
}
