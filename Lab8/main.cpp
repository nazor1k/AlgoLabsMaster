// Lab8/main.cpp
// Лабораторна робота №8. Односпрямований і двоспрямований зв'язні списки.

#include <iostream>
#include <windows.h>

using namespace std;

// ====== Односпрямований список ======

struct SNode {
    int data;
    SNode* next;
};

struct SinglyList {
    SNode* head;
    SinglyList() : head(nullptr) {}

    void pushFront(int val) {
        SNode* node = new SNode{ val, head };
        head = node;
    }

    void pushBack(int val) {
        SNode* node = new SNode{ val, nullptr };
        if (!head) { head = node; return; }
        SNode* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }

    void remove(int val) {
        if (!head) return;
        if (head->data == val) {
            SNode* tmp = head;
            head = head->next;
            delete tmp;
            return;
        }
        SNode* cur = head;
        while (cur->next && cur->next->data != val)
            cur = cur->next;
        if (cur->next) {
            SNode* tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
        }
    }

    void print() {
        SNode* cur = head;
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "\n";
    }

    ~SinglyList() {
        while (head) {
            SNode* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};

// ====== Двоспрямований список ======

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
};

struct DoublyList {
    DNode* head;
    DNode* tail;
    DoublyList() : head(nullptr), tail(nullptr) {}

    void pushFront(int val) {
        DNode* node = new DNode{ val, head, nullptr };
        if (head) head->prev = node;
        else tail = node;
        head = node;
    }

    void pushBack(int val) {
        DNode* node = new DNode{ val, nullptr, tail };
        if (tail) tail->next = node;
        else head = node;
        tail = node;
    }

    void remove(int val) {
        DNode* cur = head;
        while (cur && cur->data != val) cur = cur->next;
        if (!cur) return;
        if (cur->prev) cur->prev->next = cur->next;
        else head = cur->next;
        if (cur->next) cur->next->prev = cur->prev;
        else tail = cur->prev;
        delete cur;
    }

    void printForward() {
        DNode* cur = head;
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " <-> ";
            cur = cur->next;
        }
        cout << "\n";
    }

    void printBackward() {
        DNode* cur = tail;
        while (cur) {
            cout << cur->data;
            if (cur->prev) cout << " <-> ";
            cur = cur->prev;
        }
        cout << "\n";
    }

    ~DoublyList() {
        while (head) {
            DNode* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "=== Односпрямований список ===\n";
    SinglyList sl;
    sl.pushBack(10);
    sl.pushBack(20);
    sl.pushBack(30);
    sl.pushFront(5);
    cout << "Після pushBack(10,20,30), pushFront(5):\n";
    sl.print();
    sl.remove(20);
    cout << "Після видалення 20:\n";
    sl.print();

    cout << "\n=== Двоспрямований список ===\n";
    DoublyList dl;
    dl.pushBack(10);
    dl.pushBack(20);
    dl.pushBack(30);
    dl.pushFront(5);
    cout << "Прямий обхід:\n";
    dl.printForward();
    cout << "Зворотній обхід:\n";
    dl.printBackward();
    dl.remove(20);
    cout << "Після видалення 20:\n";
    dl.printForward();

    return 0;
}
