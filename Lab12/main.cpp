#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class AdjacencyMatrix {
private:
    vector<vector<int>> matrix;
    int size;

public:
    AdjacencyMatrix(int n) : size(n) {
        matrix.resize(size, vector<int>(size, 0));
    }

    void addEdge(int start, int end) {
        if (start < size && end < size) {
            matrix[start][end] = 1;
            matrix[end][start] = 1;
        }
    }

    void removeEdge(int start, int end) {
        if (start < size && end < size) {
            matrix[start][end] = 0;
            matrix[end][start] = 0;
        }
    }

    bool hasEdge(int start, int end) {
        if (start < size && end < size) return matrix[start][end] == 1;
        return false;
    }

    void print() {
        if (size > 10) return;
        cout << "  ";
        for (int i = 0; i < size; i++) cout << i << " ";
        cout << "\n";
        for (int i = 0; i < size; i++) {
            cout << i << " ";
            for (int j = 0; j < size; j++) cout << matrix[i][j] << " ";
            cout << "\n";
        }
    }
};

class AdjacencyList {
private:
    vector<vector<int>> list;
    int size;

public:
    AdjacencyList(int n) : size(n) {
        list.resize(size);
    }

    void addEdge(int start, int end) {
        if (start < size && end < size) {
            list[start].push_back(end);
            list[end].push_back(start);
        }
    }

    void removeEdge(int start, int end) {
        if (start >= size || end >= size) return;
        
        auto& v1 = list[start];
        v1.erase(remove(v1.begin(), v1.end(), end), v1.end());
        
        auto& v2 = list[end];
        v2.erase(remove(v2.begin(), v2.end(), start), v2.end());
    }

    bool hasEdge(int start, int end) {
        if (start >= size) return false;
        return find(list[start].begin(), list[start].end(), end) != list[start].end();
    }

    void print() {
        if (size > 10) return;
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            for (size_t j = 0; j < list[i].size(); j++) {
                cout << list[i][j] << (j == list[i].size() - 1 ? "" : " -> ");
            }
            cout << "\n";
        }
    }
};

void runTest(int numVertices, int numEdges, string label) {
    cout << "\n--- Testing " << label << " Graph (Nodes: " << numVertices << ", Edges: " << numEdges << ") ---\n";

    AdjacencyMatrix mat(numVertices);
    AdjacencyList lst(numVertices);

    auto start_time = chrono::high_resolution_clock::now();
    for (int i = 0; i < numEdges; i++) {
        mat.addEdge(i % numVertices, (i + 1) % numVertices);
    }
    auto end_time = chrono::high_resolution_clock::now();
    cout << "Matrix add: " << chrono::duration<double, milli>(end_time - start_time).count() << " ms\n";

    start_time = chrono::high_resolution_clock::now();
    for (int i = 0; i < numEdges; i++) {
        lst.addEdge(i % numVertices, (i + 1) % numVertices);
    }
    end_time = chrono::high_resolution_clock::now();
    cout << "List add:   " << chrono::duration<double, milli>(end_time - start_time).count() << " ms\n";

    start_time = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) mat.hasEdge(1, 2);
    end_time = chrono::high_resolution_clock::now();
    cout << "Matrix search: " << chrono::duration<double, milli>(end_time - start_time).count() << " ms\n";

    start_time = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) lst.hasEdge(1, 2);
    end_time = chrono::high_resolution_clock::now();
    cout << "List search:   " << chrono::duration<double, milli>(end_time - start_time).count() << " ms\n";
}

int main() {
    int small_size = 5;
    cout << "=== Demo ===\n";
    AdjacencyMatrix mat(small_size);
    AdjacencyList lst(small_size);
    
    mat.addEdge(0, 1); lst.addEdge(0, 1);
    mat.addEdge(2, 3); lst.addEdge(2, 3);
    
    cout << "Matrix output:\n"; mat.print();
    cout << "\nList output:\n";  lst.print();

    runTest(1000, 2000, "Sparse");
    runTest(1000, 50000, "Dense");

    return 0;
}
