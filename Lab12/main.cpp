#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class AdjacencyMatrix {
private:
    vector<vector<int>> matrix;
    int n;

public:
    AdjacencyMatrix(int vertices) : n(vertices) {
        matrix.resize(n, vector<int>(n, 0));
    }

    void addEdge(int u, int v) {
        if (u < n && v < n) {
            matrix[u][v] = 1;
            matrix[v][u] = 1;
        }
    }

    void removeEdge(int u, int v) {
        if (u < n && v < n) {
            matrix[u][v] = 0;
            matrix[v][u] = 0;
        }
    }

    bool hasEdge(int u, int v) {
        if (u < n && v < n) return matrix[u][v] == 1;
        return false;
    }

    void print() {
        if (n > 10) return;
        cout << "  ";
        for (int i = 0; i < n; i++) cout << i << " ";
        cout << "\n";
        for (int i = 0; i < n; i++) {
            cout << i << " ";
            for (int j = 0; j < n; j++) cout << matrix[i][j] << " ";
            cout << "\n";
        }
    }
};

class AdjacencyList {
private:
    vector<vector<int>> adj;
    int n;

public:
    AdjacencyList(int vertices) : n(vertices) {
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        if (u < n && v < n) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void removeEdge(int u, int v) {
        if (u >= n || v >= n) return;
        auto& v1 = adj[u];
        v1.erase(remove(v1.begin(), v1.end(), v), v1.end());
        auto& v2 = adj[v];
        v2.erase(remove(v2.begin(), v2.end(), u), v2.end());
    }

    bool hasEdge(int u, int v) {
        if (u >= n) return false;
        return find(adj[u].begin(), adj[u].end(), v) != adj[u].end();
    }

    void print() {
        if (n > 10) return;
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            for (size_t j = 0; j < adj[i].size(); j++) {
                cout << adj[i][j] << (j == adj[i].size() - 1 ? "" : " -> ");
            }
            cout << "\n";
        }
    }
};

void runBenchmark(int V, int E_count, string type) {
    cout << "\n--- Testing " << type << " Graph (V=" << V << ", E=" << E_count << ") ---\n";

    AdjacencyMatrix m(V);
    AdjacencyList l(V);

    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < E_count; i++) {
        m.addEdge(i % V, (i + 1) % V);
    }
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Matrix addEdge: " << chrono::duration<double, milli>(t2 - t1).count() << " ms\n";

    auto t3 = chrono::high_resolution_clock::now();
    for (int i = 0; i < E_count; i++) {
        l.addEdge(i % V, (i + 1) % V);
    }
    auto t4 = chrono::high_resolution_clock::now();
    cout << "List addEdge:   " << chrono::duration<double, milli>(t4 - t3).count() << " ms\n";

    auto t5 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) m.hasEdge(1, 2);
    auto t6 = chrono::high_resolution_clock::now();
    cout << "Matrix search:  " << chrono::duration<double, milli>(t6 - t5).count() << " ms\n";

    auto t7 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) l.hasEdge(1, 2);
    auto t8 = chrono::high_resolution_clock::now();
    cout << "List search:    " << chrono::duration<double, milli>(t8 - t7).count() << " ms\n";
}

int main() {
    int V_small = 5;
    cout << "=== Demo Mode ===\n";
    AdjacencyMatrix m(V_small);
    AdjacencyList l(V_small);
    m.addEdge(0, 1); l.addEdge(0, 1);
    m.addEdge(2, 3); l.addEdge(2, 3);
    
    cout << "Matrix:\n"; m.print();
    cout << "\nList:\n";   l.print();

    runBenchmark(1000, 2000, "Sparse");
    runBenchmark(1000, 100000, "Dense");

    return 0;
}
