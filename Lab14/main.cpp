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
    vector<int> sizes = { 100, 1000, 10000, 100000 };

    cout << "Size\tAlgorithm\tComparisons\tTime (ms)\n";
    cout << "--------------------------------------------------\n";

    for (int n : sizes) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;

        int target = -1;
        long long cmp;

        auto start = chrono::high_resolution_clock::now();
        linearSearch(arr, target, cmp);
        auto end = chrono::high_resolution_clock::now();
        double linearTime = chrono::duration<double, milli>(end - start).count();
        cout << n << "\tLinear\t\t" << cmp << "\t\t" << linearTime << "\n";

        sort(arr.begin(), arr.end());

        start = chrono::high_resolution_clock::now();
        binarySearch(arr, target, cmp);
        end = chrono::high_resolution_clock::now();
        double binaryTime = chrono::duration<double, milli>(end - start).count();
        cout << "\tBinary\t\t" << cmp << "\t\t" << binaryTime << "\n";
        cout << "--------------------------------------------------\n";
    }

    return 0;
}
