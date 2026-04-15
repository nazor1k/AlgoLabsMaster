// Lab10/main.cpp
// Лабораторна робота №10. Черга: реалізація на масиві та зв'язному списку.

#include <iostream>
#include <chrono>
#include <windows.h>

using namespace std;

// ====== Черга на масиві (циклічний буфер) ======

#define MAX_SIZE 100000

struct ArrayQueue {
    int data[MAX_SIZE];
    int front, back, count;
    ArrayQueue() : front(0), back(0), count(0) {}

    bool isEmpty() { return count == 0; }
    bool isFull()  { return count == MAX_SIZE; }
    int  size()    { return count; }

    void enqueue(int val) {
        if (!isFull()) {
            data[back] = val;
            back = (back + 1) % MAX_SIZE;
            count++;
        }
    }

    int dequeue() {
        if (!isEmpty()) {
            int val = data[front];
            front = (front + 1) % MAX_SIZE;
            count--;
            return val;
        }
        return -1;
    }

    int peek() {
        if (!isEmpty()) return data[front];
        return -1;
    }
};

// ====== Черга на зв'язному списку ======

struct QNode {
    int data;
    QNode* next;
};

struct LinkedQueue {
    QNode* front;
    QNode* back;
    int count;
    LinkedQueue() : front(nullptr), back(nullptr), count(0) {}

    bool isEmpty() { return count == 0; }
    int  size()    { return count; }

    void enqueue(int val) {
        QNode* node = new QNode{ val, nullptr };
        if (!back) { front = back = node; }
        else { back->next = node; back = node; }
        count++;
    }

    int dequeue() {
        if (!isEmpty()) {
            int val = front->data;
            QNode* tmp = front;
            front = front->next;
            if (!front) back = nullptr;
            delete tmp;
            count--;
            return val;
        }
        return -1;
    }

    int peek() {
        if (!isEmpty()) return front->data;
        return -1;
    }

    ~LinkedQueue() {
        while (!isEmpty()) dequeue();
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int N = 50000;

    cout << "=== Черга на масиві ===\n";
    {
        ArrayQueue q;
        q.enqueue(10); q.enqueue(20); q.enqueue(30);
        cout << "peek: " << q.peek() << "\n";
        cout << "dequeue: " << q.dequeue() << "\n";
        cout << "dequeue: " << q.dequeue() << "\n";
        cout << "size: " << q.size() << "\n";
        cout << "isEmpty: " << (q.isEmpty() ? "так" : "ні") << "\n";
    }

    cout << "\n=== Черга на зв'язному списку ===\n";
    {
        LinkedQueue q;
        q.enqueue(10); q.enqueue(20); q.enqueue(30);
        cout << "peek: " << q.peek() << "\n";
        cout << "dequeue: " << q.dequeue() << "\n";
        cout << "dequeue: " << q.dequeue() << "\n";
        cout << "size: " << q.size() << "\n";
        cout << "isEmpty: " << (q.isEmpty() ? "так" : "ні") << "\n";
    }

    cout << "\n=== Порівняння продуктивності (N=" << N << " операцій) ===\n";

    {
        ArrayQueue q;
        auto t1 = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) q.enqueue(i);
        for (int i = 0; i < N; i++) q.dequeue();
        auto t2 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t2 - t1).count();
        cout << "Масив:\t\t" << ms << " мс\n";
    }

    {
        LinkedQueue q;
        auto t1 = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) q.enqueue(i);
        for (int i = 0; i < N; i++) q.dequeue();
        auto t2 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t2 - t1).count();
        cout << "Зв'язний список: " << ms << " мс\n";
    }

    return 0;
}
