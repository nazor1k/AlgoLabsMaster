#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class HashTable {
private:
    int capacity;
    vector<vector<int>> buckets;

    int hashFunction(int key) {
        return abs(key) % capacity;
    }

public:
    HashTable(int size) : capacity(size) {
        buckets.resize(capacity);
    }

    void insert(int key) {
        int index = hashFunction(key);
        for (int x : buckets[index]) {
            if (x == key) return;
        }
        buckets[index].push_back(key);
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (int x : buckets[index]) {
            if (x == key) return true;
        }
        return false;
    }

    void print() {
        if (capacity > 20) return;
        for (int i = 0; i < capacity; i++) {
            if (buckets[i].empty()) continue;
            cout << "[" << i << "]: ";
            for (int x : buckets[i]) cout << x << " ";
            cout << endl;
        }
    }
};

int main() {
    srand(time(0));

    cout << "=== Hash Table Demo ===\n";
    HashTable demoTable(10);
    vector<int> demoData = { 12, 22, 32, 45, 67, 89 };
    for (int x : demoData) demoTable.insert(x);
    demoTable.print();
    cout << "Search 45: " << (demoTable.search(45) ? "Found" : "Not Found") << "\n\n";

    int N = 50000;
    int target = -1;
    cout << "=== Performance Comparison (N=" << N << ") ===\n";
    cout << "Format: Preparation (ms) + Search (ms) = Total (ms)\n";

    vector<int> data(N);
    for (int i = 0; i < N; i++) data[i] = rand() % 1000000;

    auto s1 = chrono::high_resolution_clock::now();
    sort(data.begin(), data.end());
    auto s2 = chrono::high_resolution_clock::now();
    binary_search(data.begin(), data.end(), target);
    auto s3 = chrono::high_resolution_clock::now();

    double sortTime = chrono::duration<double, milli>(s2 - s1).count();
    double binSearchTime = chrono::duration<double, milli>(s3 - s2).count();
    cout << "Binary Search: " << sortTime << " + " << binSearchTime << " = " << sortTime + binSearchTime << " ms\n";

    auto h1 = chrono::high_resolution_clock::now();
    HashTable ht(N);
    for (int x : data) ht.insert(x);
    auto h2 = chrono::high_resolution_clock::now();
    ht.search(target);
    auto h3 = chrono::high_resolution_clock::now();

    double buildTime = chrono::duration<double, milli>(h2 - h1).count();
    double hashSearchTime = chrono::duration<double, milli>(h3 - h2).count();
    cout << "Hash Table:    " << buildTime << " + " << hashSearchTime << " = " << buildTime + hashSearchTime << " ms\n";

    return 0;
}
