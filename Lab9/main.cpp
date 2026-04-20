#include <iostream>
#include <chrono>

using namespace std;

struct ArrayStack {
    static const int MAX_SIZE = 100000;
    int data[MAX_SIZE];
    int topIndex;

    ArrayStack() : topIndex(-1) {}

    bool isEmpty() { return topIndex == -1; }

    void push(int val) {
        if (topIndex < MAX_SIZE - 1) {
            data[++topIndex] = val;
        }
    }

    int pop() {
        if (isEmpty()) return -1;
        return data[topIndex--];
    }

    int peek() {
        if (isEmpty()) return -1;
        return data[topIndex];
    }
};

struct Node {
    int data;
    Node* next;
};

struct LinkedListStack {
    Node* topNode;
    LinkedListStack() : topNode(nullptr) {}

    bool isEmpty() { return topNode == nullptr; }

    void push(int val) {
        Node* newNode = new Node{ val, topNode };
        topNode = newNode;
    }

    int pop() {
        if (isEmpty()) return -1;
        int val = topNode->data;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    int peek() {
        if (isEmpty()) return -1;
        return topNode->data;
    }

    ~LinkedListStack() {
        while (!isEmpty()) pop();
    }
};

int main() {
    int N = 50000;

    cout << "=== Array Stack ===\n";
    ArrayStack as;
    as.push(10); as.push(20); as.push(30);
    cout << "peek: " << as.peek() << "\n";
    cout << "pop: " << as.pop() << "\n";
    cout << "pop: " << as.pop() << "\n";
    cout << "isEmpty: " << (as.isEmpty() ? "Yes" : "No") << "\n";

    cout << "\n=== Linked List Stack ===\n";
    LinkedListStack ls;
    ls.push(10); ls.push(20); ls.push(30);
    cout << "peek: " << ls.peek() << "\n";
    cout << "pop: " << ls.pop() << "\n";
    cout << "pop: " << ls.pop() << "\n";
    cout << "isEmpty: " << (ls.isEmpty() ? "Yes" : "No") << "\n";

    cout << "\n=== Performance Comparison (N=" << N << ") ===\n";

    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) as.push(i);
    for (int i = 0; i < N; i++) as.pop();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Array Stack:  " << chrono::duration<double, milli>(t2 - t1).count() << " ms\n";

    auto t3 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) ls.push(i);
    for (int i = 0; i < N; i++) ls.pop();
    auto t4 = chrono::high_resolution_clock::now();
    cout << "Linked Stack: " << chrono::duration<double, milli>(t4 - t3).count() << " ms\n";

    return 0;
}
