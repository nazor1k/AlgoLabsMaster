// Lab12/main.cpp
// Лабораторна робота №12. Подання графів: матриця суміжності та список суміжності.

#include <iostream>
#include <windows.h>

using namespace std;

#define MAX_V 10

// ====== Матриця суміжності ======

struct AdjMatrix {
    int matrix[MAX_V][MAX_V];
    int n;

    AdjMatrix(int vertices) : n(vertices) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                matrix[i][j] = 0;
    }

    void addEdge(int u, int v) {
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    void removeEdge(int u, int v) {
        matrix[u][v] = 0;
        matrix[v][u] = 0;
    }

    bool hasEdge(int u, int v) {
        return matrix[u][v] == 1;
    }

    void print() {
        cout << "  ";
        for (int i = 0; i < n; i++) cout << i << " ";
        cout << "\n";
        for (int i = 0; i < n; i++) {
            cout << i << " ";
            for (int j = 0; j < n; j++)
                cout << matrix[i][j] << " ";
            cout << "\n";
        }
    }
};

// ====== Список суміжності ======

struct AdjNode {
    int vertex;
    AdjNode* next;
};

struct AdjList {
    AdjNode* heads[MAX_V];
    int n;

    AdjList(int vertices) : n(vertices) {
        for (int i = 0; i < n; i++) heads[i] = nullptr;
    }

    void addEdge(int u, int v) {
        AdjNode* node1 = new AdjNode{ v, heads[u] };
        heads[u] = node1;
        AdjNode* node2 = new AdjNode{ u, heads[v] };
        heads[v] = node2;
    }

    void removeEdge(int u, int v) {
        // Видалення з heads[u]
        AdjNode** cur = &heads[u];
        while (*cur) {
            if ((*cur)->vertex == v) {
                AdjNode* tmp = *cur;
                *cur = (*cur)->next;
                delete tmp;
                break;
            }
            cur = &(*cur)->next;
        }
        // Видалення з heads[v]
        cur = &heads[v];
        while (*cur) {
            if ((*cur)->vertex == u) {
                AdjNode* tmp = *cur;
                *cur = (*cur)->next;
                delete tmp;
                break;
            }
            cur = &(*cur)->next;
        }
    }

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            AdjNode* cur = heads[i];
            while (cur) {
                cout << cur->vertex;
                if (cur->next) cout << " -> ";
                cur = cur->next;
            }
            cout << "\n";
        }
    }

    ~AdjList() {
        for (int i = 0; i < n; i++) {
            AdjNode* cur = heads[i];
            while (cur) {
                AdjNode* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int V = 5;

    cout << "=== Матриця суміжності ===\n";
    AdjMatrix m(V);
    m.addEdge(0, 1);
    m.addEdge(0, 2);
    m.addEdge(1, 3);
    m.addEdge(2, 4);
    m.addEdge(3, 4);
    m.print();
    cout << "Ребро (0,1): " << (m.hasEdge(0, 1) ? "є" : "немає") << "\n";
    cout << "Ребро (0,3): " << (m.hasEdge(0, 3) ? "є" : "немає") << "\n";
    m.removeEdge(0, 1);
    cout << "Після видалення (0,1):\n";
    m.print();

    cout << "\n=== Список суміжності ===\n";
    AdjList l(V);
    l.addEdge(0, 1);
    l.addEdge(0, 2);
    l.addEdge(1, 3);
    l.addEdge(2, 4);
    l.addEdge(3, 4);
    l.print();
    l.removeEdge(0, 1);
    cout << "Після видалення (0,1):\n";
    l.print();

    return 0;
}
