// Lab13/main.cpp
// Лабораторна робота №13. Обхід графів: DFS та BFS.

#include <iostream>
#include <windows.h>

using namespace std;

#define MAX_V 10

// Граф зберігаємо як список суміжності
struct GNode {
    int vertex;
    GNode* next;
};

GNode* adj[MAX_V];
int numVertices;

void addEdge(int u, int v) {
    GNode* n1 = new GNode{ v, adj[u] };
    adj[u] = n1;
    GNode* n2 = new GNode{ u, adj[v] };
    adj[v] = n2;
}

// ====== DFS (рекурсивний) ======

void dfsHelper(int v, bool visited[]) {
    visited[v] = true;
    cout << v << " ";
    for (GNode* cur = adj[v]; cur; cur = cur->next) {
        if (!visited[cur->vertex])
            dfsHelper(cur->vertex, visited);
    }
}

void dfs(int start) {
    bool visited[MAX_V] = {};
    dfsHelper(start, visited);
    cout << "\n";
}

// ====== BFS (через чергу-масив) ======

void bfs(int start) {
    bool visited[MAX_V] = {};
    int queue[MAX_V];
    int front = 0, back = 0;

    visited[start] = true;
    queue[back++] = start;

    while (front < back) {
        int v = queue[front++];
        cout << v << " ";
        for (GNode* cur = adj[v]; cur; cur = cur->next) {
            if (!visited[cur->vertex]) {
                visited[cur->vertex] = true;
                queue[back++] = cur->vertex;
            }
        }
    }
    cout << "\n";
}

// Перевірка наявності циклу через DFS
bool hasCycleHelper(int v, bool visited[], int parent) {
    visited[v] = true;
    for (GNode* cur = adj[v]; cur; cur = cur->next) {
        int u = cur->vertex;
        if (!visited[u]) {
            if (hasCycleHelper(u, visited, v)) return true;
        }
        else if (u != parent) {
            return true;
        }
    }
    return false;
}

bool hasCycle() {
    bool visited[MAX_V] = {};
    for (int i = 0; i < numVertices; i++)
        if (!visited[i])
            if (hasCycleHelper(i, visited, -1)) return true;
    return false;
}

void freeGraph() {
    for (int i = 0; i < numVertices; i++) {
        GNode* cur = adj[i];
        while (cur) {
            GNode* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        adj[i] = nullptr;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    numVertices = 6;
    for (int i = 0; i < numVertices; i++) adj[i] = nullptr;

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(3, 5);
    addEdge(4, 5);

    cout << "=== Граф: 6 вершин ===\n";
    cout << "Ребра: 0-1, 0-2, 1-3, 2-4, 3-5, 4-5\n\n";

    cout << "DFS з вершини 0: ";
    dfs(0);

    cout << "BFS з вершини 0: ";
    bfs(0);

    cout << "Є цикл: " << (hasCycle() ? "так" : "ні") << "\n";

    freeGraph();
    return 0;
}
