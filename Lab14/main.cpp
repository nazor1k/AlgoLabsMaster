#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;

int linearSearch(const vector<int>& arr, int target, long long& comparisons) {
    comparisons = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] == target) return (int)i;
    }
    return -1;
}

int binarySearch(const vector<int>& arr, int target, long long& comparisons) {
    comparisons = 0;
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    srand(time(0));

    cout << "=== Demo with existing target ===\n";
    vector<int> demoArr = { 15, 42, 8, 91, 23, 67, 34, 55 };
    int demoTarget = 67;
    long long demoCmp;
    
    cout << "Array: 15 42 8 91 23 67 34 55\n";
    cout << "Searching for: " << demoTarget << "\n";
    
    int lIdx = linearSearch(demoArr, demoTarget, demoCmp);
    cout << "Linear: found at index " << lIdx << " with " << demoCmp << " checks\n";
    
    sort(demoArr.begin(), demoArr.end());
    int bIdx = binarySearch(demoArr, demoTarget, demoCmp);
    cout << "Binary: found at index " << bIdx << " with " << demoCmp << " checks (after sort)\n\n";

    cout << "Size\tAlgorithm\tComparisons\tTime (ms)\n";
    cout << "--------------------------------------------------\n";

    vector<int> sizes = { 100, 1000, 10000, 100000 };
    for (int n : sizes) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;
        int target = -1;
        long long cmp;

        auto s1 = chrono::high_resolution_clock::now();
        linearSearch(arr, target, cmp);
        auto e1 = chrono::high_resolution_clock::now();
        cout << n << "\tLinear\t\t" << cmp << "\t\t" << chrono::duration<double, milli>(e1 - s1).count() << "\n";

        auto s2 = chrono::high_resolution_clock::now();
        sort(arr.begin(), arr.end());
        binarySearch(arr, target, cmp);
        auto e2 = chrono::high_resolution_clock::now();
        cout << "\tBinary+Sort\t" << cmp << "\t\t" << chrono::duration<double, milli>(e2 - s2).count() << "\n";
        cout << "--------------------------------------------------\n";
    }

    return 0;
}
