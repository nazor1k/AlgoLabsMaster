#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class HashTable {
private:
    int capacity;
    vector<vector<int>> buckets;
    int itemsCount;

    int hashFunction(int key) {
        return abs(key) % capacity;
    }

public:
    HashTable(int size) : capacity(size), itemsCount(0) {
        buckets.resize(capacity);
    }

    void insert(int key) {
        int index = hashFunction(key);
        for (int x : buckets[index]) {
            if (x == key) return;
        }
        buckets[index].push_back(key);
        itemsCount++;
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (int x : buckets[index]) {
            if (x == key) return true;
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        auto& bucket = buckets[index];
        auto it = find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end()) {
            bucket.erase(it);
            itemsCount--;
        }
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            if (buckets[i].empty()) continue;
            cout << "Bucket [" << i << "]: ";
            for (int x : buckets[i]) {
                cout << x << " ";
            }
            cout << endl;
        }
    }

    int size() { return itemsCount; }
};

void runBenchmark(int n) {
    HashTable ht(1007);
    
    auto s1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) ht.insert(rand());
    auto e1 = chrono::high_resolution_clock::now();
    double tIns = chrono::duration<double, milli>(e1 - s1).count();

    auto s2 = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) ht.search(rand());
    auto e2 = chrono::high_resolution_clock::now();
    double tSrch = chrono::duration<double, milli>(e2 - s2).count();

    cout << "N = " << n << "\tInsert: " << tIns << " ms\tSearch: " << tSrch << " ms\n";
}

int main() {
    srand(time(0));

    cout << "=== Hash Table Demo ===\n";
    HashTable ht(10);
    int demoData[] = { 10, 25, 30, 45, 12, 67, 30 };
    for (int x : demoData) ht.insert(x);

    cout << "Table state:\n";
    ht.print();

    cout << "\nSearch 45: " << (ht.search(45) ? "Found" : "Not Found") << endl;
    cout << "Search 99: " << (ht.search(99) ? "Found" : "Not Found") << endl;

    cout << "\nRemoving 25...\n";
    ht.remove(25);
    ht.print();

    cout << "\n=== Performance Benchmark ===\n";
    runBenchmark(1000);
    runBenchmark(10000);
    runBenchmark(100000);

    return 0;
}
