#include <iostream>
#include <chrono>

using namespace std;

struct Queue {
    static const int MAX_SIZE = 100000;
    int data[MAX_SIZE];
    int count;

    Queue() : count(0) {}

    bool isEmpty() { return count == 0; }
    bool isFull()  { return count == MAX_SIZE; }
    int  size()    { return count; }

    void enqueue(int val) {
        if (!isFull()) {
            for (int i = count; i > 0; i--) {
                data[i] = data[i - 1];
            }
            data[0] = val;
            count++;
        }
    }

    int dequeue() {
        if (isEmpty()) return -1;
        return data[--count];
    }

    int peek() {
        if (isEmpty()) return -1;
        return data[count - 1];
    }
};

struct Node {
    int data;
    Node* next;
};

struct LinkedListQueue {
    Node* head;
    Node* tail;
    int count;

    LinkedListQueue() : head(nullptr), tail(nullptr), count(0) {}

    bool isEmpty() { return count == 0; }
    int  size()    { return count; }

    void enqueue(int val) {
        Node* newNode = new Node{ val, nullptr };
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    int dequeue() {
        if (isEmpty()) return -1;
        int val = head->data;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        count--;
        return val;
    }

    int peek() {
        if (isEmpty()) return -1;
        return head->data;
    }

    ~LinkedListQueue() {
        while (!isEmpty()) dequeue();
    }
};

int main() {
    int N = 10000;

    cout << "=== Array Queue ===\n";
    Queue q;
    q.enqueue(10); q.enqueue(20); q.enqueue(30);
    cout << "peek: " << q.peek() << "\n";
    cout << "size before: " << q.size() << "\n";
    cout << "dequeue all: ";
    while (!q.isEmpty()) {
        cout << q.dequeue() << " ";
    }
    cout << "\nsize after: " << q.size() << "\n";

    cout << "\n=== LinkedList Queue ===\n";
    LinkedListQueue lq;
    lq.enqueue(10); lq.enqueue(20); lq.enqueue(30);
    cout << "peek: " << lq.peek() << "\n";
    cout << "size before: " << lq.size() << "\n";
    cout << "dequeue all: ";
    while (!lq.isEmpty()) {
        cout << lq.dequeue() << " ";
    }
    cout << "\nsize after: " << lq.size() << "\n";

    cout << "\n=== Performance Comparison (N=" << N << ") ===\n";

    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) q.enqueue(i);
    for (int i = 0; i < N; i++) q.dequeue();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Array Queue:  " << chrono::duration<double, milli>(t2 - t1).count() << " ms\n";

    auto t3 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) lq.enqueue(i);
    for (int i = 0; i < N; i++) lq.dequeue();
    auto t4 = chrono::high_resolution_clock::now();
    cout << "Linked Queue: " << chrono::duration<double, milli>(t4 - t3).count() << " ms\n";

    return 0;
}
