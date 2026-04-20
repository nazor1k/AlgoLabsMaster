#include <iostream>
#include <vector>
#include <algorithm>

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

    void print() {
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

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            for (size_t j = 0; j < adj[i].size(); j++) {
                cout << adj[i][j] << (j == adj[i].size() - 1 ? "" : " -> ");
            }
            cout << "\n";
        }
    }
};

int main() {
    int V = 5;

    cout << "=== Adjacency Matrix ===\n";
    AdjacencyMatrix matrix(V);
    matrix.addEdge(0, 1); matrix.addEdge(0, 2); matrix.addEdge(1, 3); matrix.addEdge(2, 4);
    matrix.print();

    cout << "\n=== Adjacency List ===\n";
    AdjacencyList list(V);
    list.addEdge(0, 1); list.addEdge(0, 2); list.addEdge(1, 3); list.addEdge(2, 4);
    list.print();

    cout << "\nRemoving edge (0,1)...\n";
    matrix.removeEdge(0, 1);
    list.removeEdge(0, 1);

    cout << "\nMatrix after removal:\n"; matrix.print();
    cout << "\nList after removal:\n";   list.print();

    return 0;
}
