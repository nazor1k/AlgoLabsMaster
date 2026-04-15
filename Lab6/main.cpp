// Lab6/main.cpp
// Лабораторна робота №6. Швидке сортування та сортування Шелла.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <windows.h>

using namespace std;

void quickSort(int arr[], int low, int high, long long& comparisons, long long& swaps) {
    if (low >= high) return;

    // Опорний елемент — середній
    int mid = low + (high - low) / 2;
    int pivot = arr[mid];
    int i = low, j = high;

    while (i <= j) {
        while (++comparisons && arr[i] < pivot) i++;
        while (++comparisons && arr[j] > pivot) j--;
        if (i <= j) {
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            swaps++;
            i++; j--;
        }
    }

    quickSort(arr, low, j, comparisons, swaps);
    quickSort(arr, i, high, comparisons, swaps);
}

void shellSort(int arr[], int n, long long& comparisons, long long& shifts) {
    comparisons = 0;
    shifts = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i;
            while (j >= gap) {
                comparisons++;
                if (arr[j - gap] > key) {
                    arr[j] = arr[j - gap];
                    shifts++;
                    j -= gap;
                }
                else break;
            }
            arr[j] = key;
        }
    }
}

void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand((unsigned)time(0));

    int sizes[] = { 100, 1000, 10000 };

    cout << "Лабораторна №6. Швидке сортування vs Сортування Шелла\n";
    cout << "===========================================\n";
    cout << "Розмір\tАлгоритм\tПорівн.\tОбміни\tЧас(мс)\n";
    cout << "-------------------------------------------\n";

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        int* original = new int[n];
        int* arr = new int[n];
        fillRandom(original, n);

        long long cmp, swp;

        // Швидке сортування
        copyArray(original, arr, n);
        cmp = 0; swp = 0;
        auto t1 = chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1, cmp, swp);
        auto t2 = chrono::high_resolution_clock::now();
        double ms1 = chrono::duration<double, milli>(t2 - t1).count();
        cout << n << "\tШвидке\t\t" << cmp << "\t" << swp << "\t" << ms1 << "\n";

        // Сортування Шелла
        copyArray(original, arr, n);
        auto t3 = chrono::high_resolution_clock::now();
        shellSort(arr, n, cmp, swp);
        auto t4 = chrono::high_resolution_clock::now();
        double ms2 = chrono::duration<double, milli>(t4 - t3).count();
        cout << "\tШелла\t\t" << cmp << "\t" << swp << "\t" << ms2 << "\n";

        cout << "-------------------------------------------\n";

        delete[] original;
        delete[] arr;
    }

    return 0;
}
