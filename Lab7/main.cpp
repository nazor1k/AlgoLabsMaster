// Lab7/main.cpp

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int MAX_VAL = 9999;
const int BUCKETS_COUNT = 10;

void countingSort(vector<int>& arr, int maxVal, long long& checks, long long& changes) {
    if (arr.empty()) return;
    vector<int> countArr(maxVal + 1, 0);
    for (int x : arr) {
        countArr[x]++;
    }
    int index = 0;
    for (int v = 0; v <= maxVal; v++) {
        while (countArr[v] > 0) {
            arr[index++] = v;
            countArr[v]--;
            changes++;
        }
    }
}

void insertionSort(vector<int>& arr, long long& checks, long long& changes) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int element = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > element) {
            checks++;
            arr[j + 1] = arr[j];
            changes++;
            j--;
        }
        if (j >= 0) checks++; // Last check that failed the while condition
        arr[j + 1] = element;
    }
}

void bucketSort(vector<int>& arr, int maxVal, int bucketCount, long long& checks, long long& changes) {
    if (arr.empty()) return;
    int bucketSize = (maxVal / bucketCount) + 1;
    vector<vector<int>> buckets(bucketCount);

    // Distribution
    for (int x : arr) {
        int k = x / bucketSize;
        if (k >= bucketCount) k = bucketCount - 1;
        buckets[k].push_back(x);
    }

    // Sort each bucket and merge
    arr.clear();
    for (int k = 0; k < bucketCount; k++) {
        if (!buckets[k].empty()) {
            insertionSort(buckets[k], checks, changes);
            for (int x : buckets[k]) {
                arr.push_back(x);
                changes++;
            }
        }
    }
}

vector<int> generateArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (MAX_VAL + 1);
    return arr;
}

int main() {
    srand((unsigned)time(0));
    vector<int> rozmiry = { 100, 1000, 10000 };

    cout << "Lab 7. Counting sort vs Bucket sort (Vector implementation)\n\n";
    
    auto printSeparator = []() {
        for (int i = 0; i < 75; i++) cout << "-";
        cout << "\n";
    };

    printSeparator();
    cout << "Size\t| Algorithm\t| Checks\t| Changes\t| Time(ns)\n";
    printSeparator();

    for (int n : rozmiry) {
        vector<int> original = generateArray(n);

        // Counting Sort
        vector<int> v1 = original;
        long long checks1 = 0;
        long long changes1 = 0;
        auto t1 = high_resolution_clock::now();
        countingSort(v1, MAX_VAL, checks1, changes1);
        auto t2 = high_resolution_clock::now();
        long long ns1 = duration_cast<nanoseconds>(t2 - t1).count();
        
        cout << n << "\t| Counting\t| " << checks1 << "\t\t| " << changes1 << "\t\t| " << ns1 << "\n";

        // Bucket Sort
        vector<int> v2 = original;
        long long checks2 = 0;
        long long changes2 = 0;
        auto t3 = high_resolution_clock::now();
        bucketSort(v2, MAX_VAL, BUCKETS_COUNT, checks2, changes2);
        auto t4 = high_resolution_clock::now();
        long long ns2 = duration_cast<nanoseconds>(t4 - t3).count();
        
        cout << "\t| Bucket\t| " << checks2 << "\t\t| " << changes2 << "\t\t| " << ns2 << "\n";
             
        printSeparator();
    }

    return 0;
}
