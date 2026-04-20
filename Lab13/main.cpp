#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
public:
    int n;
    vector<int> adj[100];
    bool visited[100];

    Graph(int vertices) {
        n = vertices;
        reset();
    }

    void reset() {
        for (int i = 0; i < 100; i++) visited[i] = false;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v) {
        visited[v] = true;
        cout << v << " ";
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    }

    void bfs(int start) {
        bool seen[100] = {false};
        queue<int> q;
        seen[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";
            for (int neighbor : adj[v]) {
                if (!seen[neighbor]) {
                    seen[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    bool hasCycle(int v, int parent) {
        visited[v] = true;
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (hasCycle(neighbor, v)) return true;
            } else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }

    bool findPath(int current, int target) {
        if (current == target) return true;
        visited[current] = true;
        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                if (findPath(neighbor, target)) return true;
            }
        }
        return false;
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "DFS traversal: ";
    g.dfs(0);
    cout << endl;

    cout << "BFS traversal: ";
    g.bfs(0);
    cout << endl;

    g.reset();
    cout << "Cycle detection: " << (g.hasCycle(0, -1) ? "Cycle found" : "No cycle") << endl;

    g.reset();
    cout << "Path from 0 to 5: " << (g.findPath(0, 5) ? "Path exists" : "No path") << endl;

    return 0;
}
