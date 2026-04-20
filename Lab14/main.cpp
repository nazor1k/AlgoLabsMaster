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

    cout << "Size\tAlgorithm (Status)\tComparisons\tTime (ms) [Sort + Search = Total]\n";
    cout << "----------------------------------------------------------------------------------\n";

    for (int n : sizes) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;
        int targetFound = arr[n / 2];
        int targetNotFound = -1;
        long long cmp;

        auto s1 = chrono::high_resolution_clock::now();
        linearSearch(arr, targetNotFound, cmp);
        auto e1 = chrono::high_resolution_clock::now();
        double tL1 = chrono::duration<double, milli>(e1 - s1).count();
        cout << n << "\tLinear (Not Found)\t" << cmp << "\t\t0.00 + " << tL1 << " = " << tL1 << "\n";

        auto s2 = chrono::high_resolution_clock::now();
        linearSearch(arr, targetFound, cmp);
        auto e2 = chrono::high_resolution_clock::now();
        double tL2 = chrono::duration<double, milli>(e2 - s2).count();
        cout << "\tLinear (Found)\t\t" << cmp << "\t\t0.00 + " << tL2 << " = " << tL2 << "\n";

        auto ss = chrono::high_resolution_clock::now();
        sort(arr.begin(), arr.end());
        auto es = chrono::high_resolution_clock::now();
        double tSort = chrono::duration<double, milli>(es - ss).count();

        auto s3 = chrono::high_resolution_clock::now();
        binarySearch(arr, targetNotFound, cmp);
        auto e3 = chrono::high_resolution_clock::now();
        double tB1 = chrono::duration<double, milli>(e3 - s3).count();
        cout << "\tBinary (Not Found)\t" << cmp << "\t\t" << tSort << " + " << tB1 << " = " << (tSort + tB1) << "\n";

        auto s4 = chrono::high_resolution_clock::now();
        binarySearch(arr, targetFound, cmp);
        auto e4 = chrono::high_resolution_clock::now();
        double tB2 = chrono::duration<double, milli>(e4 - s4).count();
        cout << "\tBinary (Found)\t\t" << cmp << "\t\t" << tSort << " + " << tB2 << " = " << (tSort + tB2) << "\n";
        cout << "----------------------------------------------------------------------------------\n";
    }

    return 0;
}
