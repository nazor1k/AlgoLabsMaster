// Lab5/main.cpp
// Лабораторна робота №5. Сортування бульбашкою та сортування вставкою.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <windows.h>

using namespace std;

void bubbleSort(int arr[], int n, long long& comparisons, long long& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void insertionSort(int arr[], int n, long long& comparisons, long long& shifts) {
    comparisons = 0;
    shifts = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                shifts++;
                j--;
            }
            else break;
        }
        arr[j + 1] = key;
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

    cout << "Лабораторна №5. Порівняння сортувань\n";
    cout << "===========================================\n";
    cout << "Розмір\tАлгоритм\tПорівн.\tОбміни\tЧас(мс)\n";
    cout << "-------------------------------------------\n";

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        int* original = new int[n];
        int* arr = new int[n];
        fillRandom(original, n);

        long long cmp, swp;

        // Бульбашка
        copyArray(original, arr, n);
        auto t1 = chrono::high_resolution_clock::now();
        bubbleSort(arr, n, cmp, swp);
        auto t2 = chrono::high_resolution_clock::now();
        double ms1 = chrono::duration<double, milli>(t2 - t1).count();
        cout << n << "\tБульбашка\t" << cmp << "\t" << swp << "\t" << ms1 << "\n";

        // Вставка
        copyArray(original, arr, n);
        auto t3 = chrono::high_resolution_clock::now();
        insertionSort(arr, n, cmp, swp);
        auto t4 = chrono::high_resolution_clock::now();
        double ms2 = chrono::duration<double, milli>(t4 - t3).count();
        cout << "\tВставка\t\t" << cmp << "\t" << swp << "\t" << ms2 << "\n";

        cout << "-------------------------------------------\n";

        delete[] original;
        delete[] arr;
    }

    return 0;
}
