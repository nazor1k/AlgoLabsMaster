// Lab14/main.cpp
// Лабораторна робота №14. Алгоритми пошуку: лінійний та бінарний.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <windows.h>

using namespace std;

// Лінійний пошук — повертає індекс або -1
int linearSearch(int arr[], int n, int target, long long& comparisons) {
    comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i] == target) return i;
    }
    return -1;
}

// Бінарний пошук (масив має бути відсортований)
int binarySearch(int arr[], int n, int target, long long& comparisons) {
    comparisons = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Сортування вставкою для підготовки масиву до бінарного пошуку
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand((unsigned)time(0));

    int sizes[] = { 100, 1000, 10000, 100000 };

    cout << "Лабораторна №14. Лінійний пошук vs Бінарний пошук\n";
    cout << "===========================================\n";
    cout << "Розмір\tАлгоритм\tПорівн.\tЧас(мс)\n";
    cout << "-------------------------------------------\n";

    for (int s = 0; s < 4; s++) {
        int n = sizes[s];
        int* arr = new int[n];
        fillRandom(arr, n);

        // Ціль — елемент якого немає (найгірший випадок для лінійного)
        int target = -1;
        long long cmp;

        // Лінійний пошук
        auto t1 = chrono::high_resolution_clock::now();
        int res1 = linearSearch(arr, n, target, cmp);
        auto t2 = chrono::high_resolution_clock::now();
        double ms1 = chrono::duration<double, milli>(t2 - t1).count();
        cout << n << "\tЛінійний\t" << cmp << "\t" << ms1 << "\n";

        // Сортуємо для бінарного
        insertionSort(arr, n);

        // Бінарний пошук
        auto t3 = chrono::high_resolution_clock::now();
        int res2 = binarySearch(arr, n, target, cmp);
        auto t4 = chrono::high_resolution_clock::now();
        double ms2 = chrono::duration<double, milli>(t4 - t3).count();
        cout << "\tБінарний\t" << cmp << "\t" << ms2 << "\n";
        cout << "-------------------------------------------\n";

        delete[] arr;
    }

    // Демонстрація коректності
    cout << "\n=== Демонстрація ===\n";
    int demo[] = { 5, 3, 8, 1, 9, 2, 7, 4, 6 };
    int demoN = 9;
    long long cmp;

    cout << "Масив: 5 3 8 1 9 2 7 4 6\n";
    int idx = linearSearch(demo, demoN, 7, cmp);
    cout << "Лінійний пошук 7: індекс=" << idx << " порівнянь=" << cmp << "\n";

    insertionSort(demo, demoN);
    cout << "Відсортований: ";
    for (int i = 0; i < demoN; i++) cout << demo[i] << " ";
    cout << "\n";
    idx = binarySearch(demo, demoN, 7, cmp);
    cout << "Бінарний пошук 7: індекс=" << idx << " порівнянь=" << cmp << "\n";

    return 0;
}
