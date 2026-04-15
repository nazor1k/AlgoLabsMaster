// Lab6/main.cpp
// Лабораторна робота №6. Швидке сортування та сортування Шелла.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <windows.h>

using namespace std;

#define MAX_SIZE 10001

void quickSort(int arr[], int left, int right, long long& checks, long long& changes) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    int pivot = arr[mid];
    int i = left;
    int j = right;

    while (i <= j) {
        checks++;
        while (arr[i] < pivot) {
            i++;
            checks++;
        }
        checks++;
        while (arr[j] > pivot) {
            j--;
            checks++;
        }
        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            changes++;
            i++;
            j--;
        }
    }

    quickSort(arr, left, j, checks, changes);
    quickSort(arr, i, right, checks, changes);
}

void shellSort(int arr[], int n, long long& checks, long long& moves) {
    checks = 0;
    moves = 0;
    for (int step = n / 2; step > 0; step /= 2) {
        for (int i = step; i < n; i++) {
            int element = arr[i];
            int j = i;
            while (j >= step) {
                checks++;
                if (arr[j - step] > element) {
                    arr[j] = arr[j - step];
                    moves++;
                    j -= step;
                }
                else break;
            }
            arr[j] = element;
        }
    }
}

void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

int original[MAX_SIZE];
int arr[MAX_SIZE];

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand((unsigned)time(0));

    int rozmiry[] = { 100, 1000, 10000 };

    cout << "Лабораторна №6. Швидке сортування vs Сортування Шелла\n";
    cout << "===========================================\n";
    cout << "Розмір\tАлгоритм\tПорівн.\tОбміни\tЧас(мс)\n";
    cout << "-------------------------------------------\n";

    for (int s = 0; s < 3; s++) {
        int n = rozmiry[s];
        generateArray(original, n);

        long long checks, changes;

        // Швидке сортування
        copyArray(original, arr, n);
        checks = 0;
        changes = 0;
        auto t1 = chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1, checks, changes);
        auto t2 = chrono::high_resolution_clock::now();
        double ms1 = chrono::duration<double, milli>(t2 - t1).count();
        cout << n << "\tШвидке\t\t" << checks << "\t" << changes << "\t" << ms1 << "\n";

        // Сортування Шелла
        copyArray(original, arr, n);
        auto t3 = chrono::high_resolution_clock::now();
        shellSort(arr, n, checks, changes);
        auto t4 = chrono::high_resolution_clock::now();
        double ms2 = chrono::duration<double, milli>(t4 - t3).count();
        cout << "\tШелла\t\t" << checks << "\t" << changes << "\t" << ms2 << "\n";

        cout << "-------------------------------------------\n";
    }

    return 0;
}
