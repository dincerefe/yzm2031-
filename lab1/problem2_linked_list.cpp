/**
 * YZM2031 - Lab Assignment 1
 * Problem 2: Singly Linked List Implementation
 * 
 * Student Name: Dinçer Efe Bolut
 * Student ID: 24018036
 * 
 * Instructions: Implement the TODO sections below
 */

#include <iostream>
using namespace std;

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    // Constructor
    LinkedList() : head(nullptr), size(0) {}

    // Destructor
    ~LinkedList() {
        // TODO: Free all nodes
        // 1. Traverse the list
        // 2. Delete each node
        // Hint: Save the next pointer before deleting current node
        Node* now, *temp;
        now = head;
        while (now != nullptr) {
            temp = now;
            now = now->next;
            delete temp;
        }
        
    }

    // Insert at beginning
    void insertFront(int value) {
        // TODO: Implement insertFront
        // 1. Create a new node
        // 2. Set new node's next to current head
        // 3. Update head to new node
        // 4. Increment sizen
        Node* newnode;
        newnode = new Node(value);
        newnode->next = head;
        head = newnode;
        size++;
    }

    // Insert at end
    void insertBack(int value) {
        // TODO: Implement insertBack
        // 1. Create a new node
        // 2. If list is empty, set head to new node
        // 3. Otherwise, traverse to the last node
        // 4. Set last node's next to new node
        // 5. Increment size
        Node* newnode, *now;
        newnode = new Node(value);
        if (head == nullptr) {
            head = newnode;
        } else {
            now = head;
            while (now->next !=nullptr) {
                now = now->next;
            }
            now->next =newnode;
        } size++;
    }

    // Insert at specific position
    void insertAt(int index, int value) {
        // TODO: Implement insertAt
        // 1. Validate index (0 <= index <= size)
        // 2. If index is 0, call insertFront
        // 3. Otherwise, traverse to node at index-1
        // 4. Create new node
        // 5. Link new node between current node and next node
        // 6. Increment size
        Node* newnode, *now;
        int i;
        if (index >= 0 && index <= size) {
            if (index == 0) {
                insertFront(value);
            } else {
                newnode = new Node(value);
                now = head;
                for (i = 0; i<index-1; i++) {
                    now = now->next;
                } 
                newnode->next = now->next;
                now->next = newnode;
                size++;
            }
        }
        
    }

    // Delete first element
    void deleteFront() {
        // TODO: Implement deleteFront
        // 1. Check if list is empty
        // 2. Save head pointer
        // 3. Move head to next node
        // 4. Delete old head
        // 5. Decrement size
        Node* tmp;
        if (head == nullptr) {
            cout << "this list is empty." << endl;
        } else {
            tmp = head;
            head = head->next;
            delete tmp;
            size--;
        }
    }

    // Delete last element
    void deleteBack() {
        // TODO: Implement deleteBack
        // 1. Check if list is empty
        // 2. If only one node, delete it and set head to nullptr
        // 3. Otherwise, traverse to second-to-last node
        // 4. Delete last node
        // 5. Set second-to-last node's next to nullptr
        // 6. Decrement size
        Node* now;
         if (head == nullptr) {
            cout << "this list is empty." << endl;
        } else if (size == 1) {
            delete head;
            head = nullptr;
            size--;
        } else {
            now = head;
            while (now->next->next != nullptr) {
                now = now->next;
            }
            delete now->next;
            now->next = nullptr;
            size--;
        }
        
    }

    // Search for value and return index (-1 if not found)
    int search(int value) {
        // TODO: Implement search
        // 1. Traverse the list
        // 2. Keep track of index
        // 3. If value found, return index
        // 4. If not found, return -1
        Node *now;
        int index;
        index = 0;
        now = head;
        while (now != nullptr) {
            if (now->data == value) {
                return index;
            }
            now=now->next;
            index++;
        }
        return -1;  // Placeholder
    }

    // Reverse the list
    void reverse() {
        // TODO: Implement reverse
        // 1. Use three pointers: prev, current, next
        // 2. Initialize prev = nullptr, current = head
        // 3. Traverse the list:
        //    - Save next node
        //    - Reverse current node's pointer
        //    - Move prev and current forward
        // 4. Update head to prev
        Node* prev, *current, *next;
        prev = nullptr;
        current = head;
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    // Print all elements
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " → ";
            }
            current = current->next;
        }
        cout << " → nullptr" << endl;
    }

    // Return size
    int getSize() const {
        return size;
    }
};

// Test cases
int main() {
    cout << "=== Testing Linked List ===" << endl << endl;

    LinkedList list;

    // Test 1: Insert operations
    cout << "Test 1: Insert operations" << endl;
    list.insertFront(10);
    list.insertFront(5);
    list.insertBack(20);
    list.insertBack(25);
    cout << "List: ";
    list.print();  // Expected: 5 → 10 → 20 → 25 → nullptr
    cout << "Size: " << list.getSize() << endl;
    cout << endl;

    // Test 2: Insert at position
    cout << "Test 2: Insert 15 at index 2" << endl;
    list.insertAt(2, 15);
    cout << "List: ";
    list.print();  // Expected: 5 → 10 → 15 → 20 → 25 → nullptr
    cout << endl;

    // Test 3: Search
    cout << "Test 3: Search operations" << endl;
    cout << "Index of 15: " << list.search(15) << endl;  // Expected: 2
    cout << "Index of 100: " << list.search(100) << endl;  // Expected: -1
    cout << endl;

    // Test 4: Delete operations
    cout << "Test 4: Delete front" << endl;
    list.deleteFront();
    cout << "List: ";
    list.print();  // Expected: 10 → 15 → 20 → 25 → nullptr
    cout << endl;

    cout << "Test 5: Delete back" << endl;
    list.deleteBack();
    cout << "List: ";
    list.print();  // Expected: 10 → 15 → 20 → nullptr
    cout << endl;

    // Test 6: Reverse
    cout << "Test 6: Reverse list" << endl;
    list.reverse();
    cout << "List: ";
    list.print();  // Expected: 20 → 15 → 10 → nullptr
    cout << endl;

    cout << "=== All tests completed ===" << endl;

    return 0;
}