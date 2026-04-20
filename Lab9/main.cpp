#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

struct ArrayStack {
    vector<int> data;

    bool isEmpty() { return data.empty(); }

    void push(int val) {
        data.push_back(val);
    }

    int pop() {
        if (isEmpty()) return -1;
        int val = data.back();
        data.pop_back();
        return val;
    }

    int peek() {
        if (isEmpty()) return -1;
        return data.back();
    }
};

struct SNode {
    int data;
    SNode* next;
};

struct LinkedStack {
    SNode* topNode;
    LinkedStack() : topNode(nullptr) {}

    bool isEmpty() { return topNode == nullptr; }

    void push(int val) {
        SNode* node = new SNode{ val, topNode };
        topNode = node;
    }

    int pop() {
        if (isEmpty()) return -1;
        int val = topNode->data;
        SNode* tmp = topNode;
        topNode = topNode->next;
        delete tmp;
        return val;
    }

    int peek() {
        if (isEmpty()) return -1;
        return topNode->data;
    }

    ~LinkedStack() {
        while (!isEmpty()) pop();
    }
};

int main() {
    int N = 50000;

    cout << "=== Stack on Vector ===\n";
    {
        ArrayStack s;
        s.push(10); s.push(20); s.push(30);
        cout << "peek: " << s.peek() << "\n";
        cout << "pop: " << s.pop() << "\n";
        cout << "pop: " << s.pop() << "\n";
        cout << "isEmpty: " << (s.isEmpty() ? "Yes" : "No") << "\n";
    }

    cout << "\n=== Stack on Linked List ===\n";
    {
        LinkedStack s;
        s.push(10); s.push(20); s.push(30);
        cout << "peek: " << s.peek() << "\n";
        cout << "pop: " << s.pop() << "\n";
        cout << "pop: " << s.pop() << "\n";
        cout << "isEmpty: " << (s.isEmpty() ? "Yes" : "No") << "\n";
    }

    cout << "\n=== Performance (N=" << N << ") ===\n";

    {
        ArrayStack s;
        auto t1 = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) s.push(i);
        for (int i = 0; i < N; i++) s.pop();
        auto t2 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t2 - t1).count();
        cout << "Vector:\t\t" << ms << " ms\n";
    }

    {
        LinkedStack s;
        auto t1 = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) s.push(i);
        for (int i = 0; i < N; i++) s.pop();
        auto t2 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t2 - t1).count();
        cout << "Linked List:\t" << ms << " ms\n";
    }

    return 0;
}
