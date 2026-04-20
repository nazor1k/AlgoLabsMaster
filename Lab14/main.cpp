#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;

void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    int pivot = arr[left + (right - left) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

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

void printTable(const vector<int>& sizes, bool itemExists) {
    if (itemExists) cout << "\n--- TEST 1: Searching for EXISTING item ---\n";
    else cout << "\n--- TEST 2: Searching for NON-EXISTING item (-1) ---\n";

    cout << "Size\tAlgorithm\tComparisons\tTime (ms) [Sort + Search = Total]\n";
    cout << "--------------------------------------------------------------------------\n";

    for (int n : sizes) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;
        int target = itemExists ? arr[n / 2] : -1;
        long long cmp;

        auto s1 = chrono::high_resolution_clock::now();
        linearSearch(arr, target, cmp);
        auto e1 = chrono::high_resolution_clock::now();
        double tLin = chrono::duration<double, milli>(e1 - s1).count();
        cout << n << "\tLinear\t\t" << cmp << "\t\t0.00 + " << tLin << " = " << tLin << "\n";

        auto s_sort = chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1);
        auto e_sort = chrono::high_resolution_clock::now();
        double tSort = chrono::duration<double, milli>(e_sort - s_sort).count();

        auto s_bin = chrono::high_resolution_clock::now();
        binarySearch(arr, target, cmp);
        auto e_bin = chrono::high_resolution_clock::now();
        double tBin = chrono::duration<double, milli>(e_bin - s_bin).count();

        cout << "\tBinary\t\t" << cmp << "\t\t" << tSort << " + " << tBin << " = " << (tSort + tBin) << "\n";
        cout << "--------------------------------------------------------------------------\n";
    }
}

int main() {
    srand(time(0));
    vector<int> sizes = { 100, 1000, 10000, 100000 };
    printTable(sizes, true);
    printTable(sizes, false);
    return 0;
}
