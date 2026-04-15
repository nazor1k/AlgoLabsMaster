// Lab9/main.cpp
// Лабораторна робота №9. Стек: реалізація на масиві та зв'язному списку.

#include <iostream>
#include <chrono>
#include <windows.h>

using namespace std;

// ====== Стек на масиві ======

#define MAX_SIZE 100000

struct ArrayStack {
    int data[MAX_SIZE];
    int top;
    ArrayStack() : top(-1) {}

    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == MAX_SIZE - 1; }

    void push(int val) {
        if (!isFull()) data[++top] = val;
    }

    int pop() {
        if (!isEmpty()) return data[top--];
        return -1;
    }

    int peek() {
        if (!isEmpty()) return data[top];
        return -1;
    }
};

// ====== Стек на зв'язному списку ======

struct SNode {
    int data;
    SNode* next;
};

struct LinkedStack {
    SNode* top;
    LinkedStack() : top(nullptr) {}

    bool isEmpty() { return top == nullptr; }

    void push(int val) {
        SNode* node = new SNode{ val, top };
        top = node;
    }

    int pop() {
        if (!isEmpty()) {
            int val = top->data;
            SNode* tmp = top;
            top = top->next;
            delete tmp;
            return val;
        }
        return -1;
    }

    int peek() {
        if (!isEmpty()) return top->data;
        return -1;
    }

    ~LinkedStack() {
        while (!isEmpty()) pop();
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int N = 50000;

    cout << "=== Стек на масиві ===\n";
    {
        ArrayStack s;
        s.push(10); s.push(20); s.push(30);
        cout << "peek: " << s.peek() << "\n";
        cout << "pop: " << s.pop() << "\n";
        cout << "pop: " << s.pop() << "\n";
        cout << "isEmpty: " << (s.isEmpty() ? "так" : "ні") << "\n";
    }

    cout << "\n=== Стек на зв'язному списку ===\n";
    {
        LinkedStack s;
        s.push(10); s.push(20); s.push(30);
        cout << "peek: " << s.peek() << "\n";
        cout << "pop: " << s.pop() << "\n";
        cout << "pop: " << s.pop() << "\n";
        cout << "isEmpty: " << (s.isEmpty() ? "так" : "ні") << "\n";
    }

    cout << "\n=== Порівняння продуктивності (N=" << N << " операцій) ===\n";

    {
        ArrayStack s;
        auto t1 = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) s.push(i);
        for (int i = 0; i < N; i++) s.pop();
        auto t2 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t2 - t1).count();
        cout << "Масив:\t\t" << ms << " мс\n";
    }

    {
        LinkedStack s;
        auto t1 = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) s.push(i);
        for (int i = 0; i < N; i++) s.pop();
        auto t2 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t2 - t1).count();
        cout << "Зв'язний список: " << ms << " мс\n";
    }

    return 0;
}
