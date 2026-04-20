#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int vertex;
    Node* next;
};

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
    vector<Node*> heads;
    int n;

public:
    AdjacencyList(int vertices) : n(vertices) {
        heads.resize(n, nullptr);
    }

    void addEdge(int u, int v) {
        if (u < n && v < n) {
            heads[u] = new Node{v, heads[u]};
            heads[v] = new Node{u, heads[v]};
        }
    }

    void removeEdge(int u, int v) {
        if (u >= n || v >= n) return;
        
        auto removeFunc = [](Node** head, int target) {
            while (*head) {
                if ((*head)->vertex == target) {
                    Node* temp = *head;
                    *head = (*head)->next;
                    delete temp;
                    return;
                }
                head = &((*head)->next);
            }
        };

        removeFunc(&heads[u], v);
        removeFunc(&heads[v], u);
    }

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            Node* cur = heads[i];
            while (cur) {
                cout << cur->vertex;
                if (cur->next) cout << " -> ";
                cur = cur->next;
            }
            cout << "\n";
        }
    }

    ~AdjacencyList() {
        for (int i = 0; i < n; i++) {
            Node* cur = heads[i];
            while (cur) {
                Node* temp = cur;
                cur = cur->next;
                delete temp;
            }
        }
    }
};

int main() {
    int V = 5;

    cout << "=== Adjacency Matrix ===\n";
    AdjacencyMatrix matrix(V);
    matrix.addEdge(0, 1);
    matrix.addEdge(0, 2);
    matrix.addEdge(1, 3);
    matrix.addEdge(2, 4);
    matrix.print();

    cout << "\n=== Adjacency List ===\n";
    AdjacencyList list(V);
    list.addEdge(0, 1);
    list.addEdge(0, 2);
    list.addEdge(1, 3);
    list.addEdge(2, 4);
    list.print();

    cout << "\nRemoving edge (0,1)...\n";
    matrix.removeEdge(0, 1);
    list.removeEdge(0, 1);

    cout << "\nMatrix after removal:\n";
    matrix.print();
    cout << "\nList after removal:\n";
    list.print();

    return 0;
}
